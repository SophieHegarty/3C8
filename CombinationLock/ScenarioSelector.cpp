#include "ScenarioSelector.h"

#include "stl.h"

ScenarioSelector::ScenarioSelector(byte pin0, byte pin1, byte pin2, byte enable_pin)
        : pins{pin0, pin1, pin2},
          enable_pin(enable_pin) {
    for (byte pin : {pin0, pin1, pin2, enable_pin}) {
        pinMode(pin, INPUT);
    }
}

void ScenarioSelector::setScenarioHandler(byte scenario, scenario_handler handler) {
    handlers[scenario] = handler;
}

void ScenarioSelector::run() {
    unsigned long current_time = millis();
    if (digitalRead(enable_pin)) {
        if (!enabled && previous_enable_off + debounce_delay < current_time) {
            enabled = true;
            previous_enable_on = current_time;

            delay(debounce_delay); // Let things to stabilise

            byte enabled_scenario = 0;
            for (byte i = 0; i < 2; i++) {
                enabled_scenario |= (digitalRead(pins[i]) & 1) << i;
            }

            if (handlers[enabled_scenario] != NULL) {
                (*handlers[enabled_scenario])();
            }
        }
    } else {
        if (enabled && previous_enable_on + debounce_delay < current_time) {
            enabled = false;
            previous_enable_off = current_time;
        }
    }
}
