#include "ScenarioSelector.h"

// Include scenarios
#include "TestInput.h"

ScenarioSelector selector(9, 10, 11, 12);

void setup() {
    Serial.begin(9600);
    randomSeed(0);
    selector.setScenarioHandler(0, &scenarios::testInputSection);
}

void loop() {
    selector.run();
}
