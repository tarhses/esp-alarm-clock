#include <sys/fcntl.h>
#include <sys/unistd.h>

#include <esp_log.h>
#include <esp_vfs_fat.h>
#include <nvs_flash.h>

#include "storage.h"
#include "config.h"

static const char *TAG = "storage";


/**
 * Initialize the non-volatile storage features.
 */
static void init_nvs(void);

/**
 * Initialize the SDMMC file system.
 */
static void init_sd(void);


void init_storage(void) {
    init_nvs();
    init_sd();
}

void init_nvs(void) {
    esp_err_t error;

    ESP_LOGI(TAG, "initializing non-volatile storage");
    error = nvs_flash_init();

    if (error == ESP_ERR_NVS_NO_FREE_PAGES || error == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_LOGE(TAG, "non-volatile storage initialization failed (%s)", esp_err_to_name(error));
        ESP_LOGI(TAG, "going to erase and retry");
        ESP_ERROR_CHECK(nvs_flash_erase());
        error = nvs_flash_init();
    }

    ESP_ERROR_CHECK(error);
}

void init_sd(void) {
    sdmmc_card_t *card;

    sdmmc_host_t host_config = SDSPI_HOST_DEFAULT();

    spi_bus_config_t bus_config = {
        .mosi_io_num = SD_PIN_MOSI,
        .miso_io_num = SD_PIN_MISO,
        .sclk_io_num = SD_PIN_CLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 4000,
    };

    sdspi_device_config_t slot_config = SDSPI_DEVICE_CONFIG_DEFAULT();
    slot_config.gpio_cs = SD_PIN_CS;
    slot_config.host_id = host_config.slot;

    esp_vfs_fat_mount_config_t mount_config = {
            .max_files = 5,
            .format_if_mount_failed = false,
    };

    ESP_LOGI(TAG, "initializing sd card");
    ESP_ERROR_CHECK(spi_bus_initialize(host_config.slot, &bus_config, SD_DMA_CHAN));
    ESP_ERROR_CHECK(esp_vfs_fat_sdspi_mount(SD_MOUNT_POINT, &host_config, &slot_config, &mount_config, &card));
}

bool open_file(const char* path, file_handle_t* handle) {
    file_handle_t file = open(path, O_RDONLY);
    if (file == -1) {
        ESP_LOGE(TAG, "failed to open \"%s\"", path);
        return false;
    }

    *handle = file;
    return true;
}

bool close_file(file_handle_t handle) {
    return close(handle) == 0;
}

bool read_file_into(file_handle_t handle, uint8_t* buffer, size_t size, size_t* bytes_read) {
    size_t total = 0;
    ssize_t status;

    while ((status = read(handle, &buffer[total], size - total)) > 0) {
        total += status;
    }

    if (status == -1) {
        ESP_LOGE(TAG, "read() failed");
        return false;
    }

    if (bytes_read != NULL) {
        *bytes_read = total;
    }

    return total == size;
}

bool read_file_json(file_handle_t handle, cJSON** json) {
    uint8_t* buffer;
    size_t size;
    bool success = false;

    if (!get_file_size(handle, &size)) {
        return false;
    }

    buffer = malloc(size + 1);
    buffer[size] = '\0';
    if (!read_file_into(handle, buffer, size, NULL)) {
        goto clean;
    }

    *json = cJSON_Parse((char*)buffer);
    if (*json == NULL) {
        goto clean;
    }

    success = true;

clean:
    free(buffer);
    return success;
}

bool get_file_size(file_handle_t handle, size_t* size) {
    struct stat stat;
    if (fstat(handle, &stat) == -1) {
        ESP_LOGE(TAG, "fstat() failed");
        return false;
    }

    *size = stat.st_size;
    return true;
}
