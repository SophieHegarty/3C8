#include "ScenarioSelector.h"

ScenarioSelector selector(9, 10, 11, 12);

void setup() {
    Serial.begin(9600);
}

void loop() {
    selector.run();
}
