#include "Scenario.h"

#include <Arduino.h>

Scenario::Scenario(const char *name) : name(name) {
    std::cout << "Beginning scenario " << name << std::endl;
}

Scenario::~Scenario() {
    std::cout << "Scenario " << name << " finished "
              << (isSuccessfull() ? "successfully" : "unsuccessfully")
              << std::endl << std::endl;
}

bool Scenario::isSuccessfull() const {
    return successful_checks == check_count;
}

bool Scenario::check(bool (*f)(), const char *name, unsigned long timeout) {
    bool result = false;
    const unsigned long beginTime = micros();
    const unsigned long endTime = beginTime + timeout;

    while (!result && micros() < endTime) {
        result = (*f)();
    }

    if (result) {
        std::cout << "Success" << std::endl;
    } else {
        if (name != NULL && strcmp(name, "") != 0) {
            std::cout << name << " ";
        }
        std::cout << "failed after " << timeout << " us" << std::endl;
    }

    return result;
}
