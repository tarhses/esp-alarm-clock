#include <sys/fcntl.h>
#include <sys/unistd.h>

#include <esp_log.h>
#include <esp_vfs_fat.h>
#include <nvs_flash.h>

#include "storage.h"
#include "config.h"

static const char *TAG = "storage";


static void init_nvs(void);
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
        ESP_LOGE(TAG, "non-volatile storage initialization failed: %s", esp_err_to_name(error));
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

bool get_file_size(file_handle_t handle, size_t* size) {
    struct stat stat;
    if (fstat(handle, &stat) == -1) {
        ESP_LOGE(TAG, "fstat() failed");
        return false;
    }

    *size = stat.st_size;
    return true;
}

char* read_file(const char* path) {
    file_handle_t file;
    if (open_file(path, &file)) {
        size_t size;
        if (get_file_size(file, &size)) {
            uint8_t* buffer = malloc(size + 1);
            buffer[size] = '\0';
            if (read_file_into(file, buffer, size, NULL)) {
                return (char*)buffer;
            }
            free(buffer);
        }
        close_file(file);
    }

    return NULL;
}

cJSON* read_json_file(const char* path) {
    char* bytes;
    cJSON* json;

    bytes = read_file(path);
    if (bytes == NULL) {
        return NULL;
    }

    json = cJSON_Parse(bytes);

    free(bytes);
    return json;
}
