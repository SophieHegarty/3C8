#ifndef SCENARIOSELECTOR_H_2VPHWELH
#define SCENARIOSELECTOR_H_2VPHWELH

#include <Arduino.h>

class ScenarioSelector {
public:
    ScenarioSelector(byte pin0, byte pin1, byte pin2, byte enable_pin);

    void run();

    typedef void(*scenario_handler)();
    void setScenarioHandler(byte scenario, scenario_handler handler);

private:
    byte pins[3];
    byte enable_pin;

    bool enabled = false;
    unsigned long previous_enable_on = 0;
    unsigned long previous_enable_off = 0;
    static constexpr unsigned long debounce_delay = 500;

    scenario_handler handlers[8] = {};
};

#endif /* end of include guard: SCENARIOSELECTOR_H_2VPHWELH */
