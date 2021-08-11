#pragma once

#include <esp_event.h>

ESP_EVENT_DECLARE_BASE(ALARM_EVENT);

typedef enum {
    ALARM_EVENT_TICK,
    ALARM_EVENT_CHANGED,
    ALARM_EVENT_ENABLED,
    ALARM_EVENT_DISABLED,
    ALARM_EVENT_STARTED,
    ALARM_EVENT_STOPPED,
    ALARM_EVENT_DELAYED,
} alarm_event_t;

typedef struct {
    int hours;
    int minutes;
    int seconds;
} alarm_time_t;

#define MIDNIGHT { 0, 0, 0 }

void init_alarm(void);
void start_alarm(void);
