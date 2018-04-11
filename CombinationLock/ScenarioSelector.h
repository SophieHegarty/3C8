#ifndef SCENARIOSELECTOR_H_2VPHWELH
#define SCENARIOSELECTOR_H_2VPHWELH

#include <Arduino.h>

/**
 * Class to select which scenario (associated set of tests) to run
 */
class ScenarioSelector {
public:
    ScenarioSelector(byte pin0, byte pin1, byte pin2, byte disable_pin);

    void run();

    typedef void(*scenario_handler)();
    void setScenarioHandler(byte scenario, scenario_handler handler);

    byte readBoardID() const;

private:
    byte pins[3];
    byte disable_pin;

    bool enabled = false;
    unsigned long previous_enable_on = 0;
    unsigned long previous_enable_off = 0;
    static constexpr unsigned long debounce_delay = 500;

    scenario_handler handlers[8] = {};
};

#endif /* end of include guard: SCENARIOSELECTOR_H_2VPHWELH */
