#include <string.h>

#include <esp_log.h>
#include <esp_sntp.h>
#include <esp_wifi.h>
#include <cJSON.h>

#include "network.h"
#include "storage.h"
#include "config.h"

static const char* TAG = "network";

ESP_EVENT_DEFINE_BASE(NET_EVENT);


/**
 * Network configuration.
 */
typedef struct {
    char* wifi_ssid;
    char* wifi_password;
    char* ntp_server;
    char* ntp_timezone;
} config_t;

/**
 * Load the configuration from `NET_CONFIG_PATH` into the `config` struct.
 *
 * Errors or missing fields are ignored.
 *
 * @param config Struct to fill in
 */
static void load_config(config_t* config);

/**
 * If `source` is a string, allocate a new string in `destination` and copy
 * `source` into it. Do nothing if `source` is NULL or not a string.
 *
 * @param destination String to allocate
 * @param source JSON object to copy
 */
static void copy_if_string(char** destination, const cJSON* source);

/**
 * Initialize the (S)NTP features.
 *
 * @param server NTP server to connect to
 * @param timezone POSIX timezone to use
 */
static void init_sntp(const char* server, const char* timezone);

/**
 * Initialize the WiFi features.
 *
 * @param ssid WiFi SSID to connect to
 * @param password WiFi password
 */
static void init_wifi(const char* ssid, const char* password);

/**
 * Handle a NTP synchronization.
 *
 * @param tv Current time
 */
static void sntp_event_handler(struct timeval* tv);

/**
 * Handle a WiFi event.
 *
 * @param _ Ignored
 * @param base Event base
 * @param id Event id
 * @param data Event data
 */
static void wifi_event_handler(void* _, esp_event_base_t base, int32_t id, void* data);


void init_network(void) {
    config_t config = {
        .wifi_ssid = "",
        .wifi_password = "",
        .ntp_server = "pool.ntp.org",
        .ntp_timezone = "GMT",
    };

    load_config(&config);

    init_sntp(config.ntp_server, config.ntp_timezone);
    init_wifi(config.wifi_ssid, config.wifi_password);
}

void load_config(config_t* config) {
    // cJSON functions ignore any NULL object that we could pass as argument.
    // That allows us to don't care about that.

    file_handle_t file;
    cJSON *root, *item;

    if (open_file(NET_CONFIG_PATH, &file)) {
        if (read_file_json(file, &root)) {
            item = cJSON_GetObjectItem(root, "wifi");
            copy_if_string(&config->wifi_ssid, cJSON_GetObjectItem(item, "ssid"));
            copy_if_string(&config->wifi_password, cJSON_GetObjectItem(item, "password"));

            item = cJSON_GetObjectItem(root, "ntp");
            copy_if_string(&config->ntp_server, cJSON_GetObjectItem(item, "server"));
            copy_if_string(&config->ntp_timezone, cJSON_GetObjectItem(item, "timezone"));

            cJSON_Delete(root);
        }

        close_file(file);
    }
}

void copy_if_string(char** destination, const cJSON* source) {
    if (cJSON_IsString(source)) {
        // The '\0' byte will be copied too
        size_t size = strlen(source->valuestring) + 1;
        *destination = malloc(size);
        memcpy(*destination, source->valuestring, size);
    }
}

void init_sntp(const char* server, const char* timezone) {
    ESP_LOGI(TAG, "initializing sntp (server=\"%s\", timezone=\"%s\")", server, timezone);

    setenv("TZ", timezone, 1);
    tzset();

    sntp_setoperatingmode(SNTP_OPMODE_POLL);
    sntp_set_sync_mode(SNTP_SYNC_MODE_SMOOTH);
    sntp_setservername(0, server);

    sntp_set_time_sync_notification_cb(&sntp_event_handler);
}

void init_wifi(const char* ssid, const char* password) {
    // Don't print the password in logs
    ESP_LOGI(TAG, "initializing wifi (ssid=\"%s\", password=***)", ssid);

    wifi_init_config_t init_config = WIFI_INIT_CONFIG_DEFAULT();
    wifi_config_t wifi_config = {
        .sta = {
            .threshold.authmode = WIFI_AUTH_WPA2_PSK,
            .pmf_cfg = {
                .capable = true,
                .required = false,
            },
        },
    };

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstringop-truncation"
    // GCC will complain about using `strncpy` but we know what we are doing.
    strncpy((char*)wifi_config.sta.ssid, ssid, 32);
    strncpy((char*)wifi_config.sta.password, password, 64);
#pragma GCC diagnostic pop

    esp_netif_init();
    esp_netif_create_default_wifi_sta();
    esp_wifi_init(&init_config);
    esp_wifi_set_mode(WIFI_MODE_STA);
    esp_wifi_set_config(WIFI_IF_STA, &wifi_config);

    esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL, NULL);
    esp_event_handler_instance_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler, NULL, NULL);
}

void start_network(void) {
    esp_wifi_start();
}

void sntp_event_handler(struct timeval* tv) {
    ESP_LOGI(TAG, "sntp synchronization (time=%ld)", tv->tv_sec);
}

void wifi_event_handler(void* _, esp_event_base_t base, int32_t id, void* data) {
    if (base == WIFI_EVENT) {
        if (id == WIFI_EVENT_STA_START) {
            esp_wifi_connect();
        } else if (id == WIFI_EVENT_STA_CONNECTED) {
            wifi_event_sta_connected_t* event = data;
            ESP_LOGI(TAG, "connected to %.*s", event->ssid_len, event->ssid);
        } else if (id == WIFI_EVENT_STA_DISCONNECTED) {
            wifi_event_sta_connected_t* event = data;
            ESP_LOGE(TAG, "disconnected from %.*s", event->ssid_len, event->ssid);
            sntp_stop();
            esp_wifi_connect();
            esp_event_post(NET_EVENT, NET_EVENT_DISCONNECTED, NULL, 0, portMAX_DELAY);
        }
    } else if (base == IP_EVENT) {
        if (id == IP_EVENT_STA_GOT_IP) {
            ip_event_got_ip_t* event = data;
            ESP_LOGI(TAG, "got ip address: " IPSTR, IP2STR(&event->ip_info.ip));
            sntp_init();
            esp_event_post(NET_EVENT, NET_EVENT_CONNECTED, NULL, 0, portMAX_DELAY);
        }
    }
}
