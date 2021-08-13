#pragma once

#include <esp_event.h>

/**
 * Network events base.
 */
ESP_EVENT_DECLARE_BASE(NET_EVENT);

/**
 * Network events.
 */
typedef enum {
    NET_EVENT_CONNECTED, /**< Connected to WiFi, got an IP address */
    NET_EVENT_DISCONNECTED, /**< Disconnected from WiFi */
} net_event_t;

/*
 * Initialize the network features.
 *
 * Configuration (WiFi's SSID and password, NTP server, and timezone) will be
 * loaded from `NET_CONFIG_PATH` ('/sdcard/config.json' by default).
 */
void init_network(void);

/*
 * Connect to WiFi and start the NTP task.
 *
 * The WiFi driver will instantly try to reconnect when disconnected.
 *
 * NTP will regularly synchronize time (every hour by default, the
 * `CONFIG_LWIP_SNTP_UPDATE_DELAY` option can be changed in `sdkconfig`). Time
 * will be updated smoothly (see `adjtime`) if there is less than 35 minutes to
 * correct.
 */
void start_network(void);
