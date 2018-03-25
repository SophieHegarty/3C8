#include "Scenario.h"

#include <Arduino.h>

Scenario::Scenario(const char *name) : name(name) {
    Serial.print(F("Beginning scenario "));
    Serial.println(name);
}

Scenario::~Scenario() {
    Serial.print(F("Scenario "));
    Serial.print(name);
    Serial.print(F(" completed "));
    Serial.println(isSuccessfull() ? F("successfully") : F("unsuccessfully"));
    Serial.println();
}

bool Scenario::isSuccessfull() const {
    return successful_checks == check_count;
}

void Scenario::sectionHeader(const char *s) const {
    if (check_count != 0) {
        Serial.println();
    }
    Serial.print(F("SECTION "));
    Serial.println(s);
}

void Scenario::interimReport() const {
    if (isSuccessfull()) {
        Serial.print(F("Successful "));
    } else {
        Serial.print(check_count - successful_checks);
        Serial.print(F(" failure"));
        if (check_count - successful_checks > 1) {
            Serial.print(F("s"));
        }
        Serial.print(F(" "));
    }
    Serial.println(F("so far"));
}
