#include "ScenarioSelector.h"

#include "stl.h"

ScenarioSelector::ScenarioSelector(byte pin0, byte pin1, byte pin2, byte disable_pin)
        : pins{pin0, pin1, pin2},
          disable_pin(disable_pin) {
    for (byte pin : {pin0, pin1, pin2, disable_pin}) {
        pinMode(pin, INPUT_PULLUP);
    }
}

void ScenarioSelector::setScenarioHandler(byte scenario, scenario_handler handler) {
    handlers[scenario] = handler;
}

void ScenarioSelector::run() {
    unsigned long current_time = millis();
    if (!digitalRead(disable_pin)) { // Should enable
        if (!enabled && previous_enable_off + debounce_delay < current_time) {
            enabled = true;
            previous_enable_on = current_time;

            byte enabled_scenario = 0;
            for (byte i = 0; i < 3; i++) {
                enabled_scenario |= (digitalRead(pins[i]) ? 1 : 0) << i;
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
