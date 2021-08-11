#include <esp_event.h>
#include <driver/gpio.h>

#include "storage.h"
#include "network.h"
#include "pot.h"
#include "sound.h"
#include "display.h"
#include "alarm.h"

void app_main(void) {
    gpio_install_isr_service(0);
    esp_event_loop_create_default();

    init_storage();
    init_network();
    init_potentiometers();
    init_sound();
    init_display();
    init_alarm();

    start_network();
    start_potentiometers();
    start_sound();
    start_display();
    start_alarm();

    esp_event_post(ALARM_EVENT, ALARM_EVENT_STARTED, NULL, 0, portMAX_DELAY);
}
