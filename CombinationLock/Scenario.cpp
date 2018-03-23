#include "Scenario.h"

#include <Arduino.h>

Scenario::Scenario(const char *name) : name(name) {
    Serial.print("Beginning scenario ");
    Serial.println(name);
}

Scenario::~Scenario() {
    Serial.print("Scenario ");
    Serial.print(name);
    Serial.println(isSuccessfull() ? "successfully" : "unsuccessfully");
    Serial.println();
}

bool Scenario::isSuccessfull() const {
    return successful_checks == check_count;
}
