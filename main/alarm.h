#pragma once

#include <esp_event.h>

/**
 * Alarm events base.
 */
ESP_EVENT_DECLARE_BASE(ALARM_EVENT);

/**
 * Alarm events.
 */
typedef enum {
    ALARM_EVENT_TICK, /**< A minute has passed */
    ALARM_EVENT_CHANGED, /**< The alarm's time has changed */
    ALARM_EVENT_ENABLED, /**< The alarm has been enabled */
    ALARM_EVENT_DISABLED, /**< The alarm has been disabled */
    ALARM_EVENT_STARTED, /**< The alarm starts ringing */
    ALARM_EVENT_STOPPED, /**< The alarm stops ringing */
    ALARM_EVENT_DELAYED, /**< The alarm is delayed */
    ALARM_EVENT_CONNECTED, /**< Connected to WiFi, got an IP address */
    ALARM_EVENT_DISCONNECTED, /**< Disconnected from WiFi */
} alarm_event_t;

/**
 * Data sent with `ALARM_EVENT_TICK`, `ALARM_EVENT_CHANGED`, and `ALARM_EVENT_DELAYED`.
 */
typedef struct {
    int hours;
    int minutes;
    int seconds;
} alarm_time_t;

#define MIDNIGHT { 0, 0, 0 }

/**
 * Initialize the alarm.
 */
void init_alarm(void);

/**
 * Start the alarm tasks.
 */
void start_alarm(void);
