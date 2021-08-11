#pragma once

#include <esp_event.h>

ESP_EVENT_DECLARE_BASE(NET_EVENT);

typedef enum {
    NET_EVENT_CONNECTED,
    NET_EVENT_DISCONNECTED,
} net_event_t;

void init_network(void);
void start_network(void);
