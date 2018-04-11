#include "OutputReader.h"

#include "stl.h"

OutputReader::OutputReader(byte hyphen0,
                           byte hyphen1,
                           byte hyphen2,
                           byte hyphen3,
                           byte standby_pin,
                           byte success_pin,
                           byte failure_pin,
                           byte input_disable_pin)
        : hyphen_pins{hyphen0, hyphen1, hyphen2, hyphen3},
          standby_pin(standby_pin),
          success_pin(success_pin),
          failure_pin(failure_pin),
          input_disable_pin(input_disable_pin) {
    for (byte pin : {hyphen0, hyphen1, hyphen2, hyphen3,
                     standby_pin, success_pin, failure_pin,
                     input_disable_pin}) {
        pinMode(pin, INPUT);
    }
}

byte OutputReader::readHyphenMask() const {
    byte result = 0;;
    for (byte i = 0; i < 4; i++) {
        result |= digitalRead(hyphen_pins[i]) ? 1 << i : 0;
    }
    return result;
}

byte OutputReader::readHyphenPosition() const {
    switch (readHyphenMask()) {
        case B0000:
            return 0;
        case B0001:
            return 1;
        case B0011:
            return 2;
        case B0111:
            return 3;
        case B1111:
            return 4;
        default:
            return BYTE_MAX;
    }
}

bool OutputReader::readStandby() const {
    return digitalRead(standby_pin);
}

bool OutputReader::readSuccess() const {
    return digitalRead(success_pin);
}

bool OutputReader::readFailure() const {
    return digitalRead(failure_pin);
}

bool OutputReader::readInputDisable() const {
    return digitalRead(input_disable_pin);
}
