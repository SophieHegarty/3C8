#include "ScenarioSelector.h"

#include "TestScenarios.h"

ScenarioSelector selector(9, 10, 11, 12);

void setup() {
    Serial.begin(9600);
    randomSeed(0);
    selector.setScenarioHandler(0, &scenarios::testInputSection);
    selector.setScenarioHandler(1, &scenarios::testCheckerSection);
    selector.setScenarioHandler(2, &scenarios::testOutputSection);
    selector.setScenarioHandler(4, &scenarios::testOverall);
}

void loop() {
    selector.run();
}
