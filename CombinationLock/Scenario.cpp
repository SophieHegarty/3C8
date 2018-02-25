#include "Scenario.h"

#include <Arduino.h>

class Test {
public:
    Test(bool (*f)(), const std::string &name, unsigned long timeout)
            : f(f), name(name), timeout(timeout) {}
    virtual ~Test() = default;

    bool execute() const;

private:
    bool (* const f)();
    const std::string &name;
    const unsigned long timeout;
};

bool Scenario::run() const {
    std::cout << "Beginning scenario " << name << std::endl;

    bool success = true;
    for (size_t i = 0; i < tests.size(); i++) {
        const Test &test = tests[i];
        std::cout << "Test " << i << ": ";
        success = success && test.execute();
    }

    std::cout << "Scenario finished " << (success ? "successfully" : "unsuccessfully")
              << std::endl << std::endl;
    return success;
}

void Scenario::addTest(bool (*f)(), std::string name, unsigned long timeout) {
    tests.push_back(Test(f, name, timeout));
}

bool Test::execute() const {
    bool result = false;
    const unsigned long beginTime = micros();
    const unsigned long endTime = beginTime + timeout;

    while (!result && micros() < endTime) {
        result = (*f)();
    }

    if (result) {
        std::cout << "Success" << std::endl;
    } else {
        if (name != "") {
            std::cout << name << " ";
        }
        std::cout << "failed after " << timeout << " us" << std::endl;
    }

    return result;
}
