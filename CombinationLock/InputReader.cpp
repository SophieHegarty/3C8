#include "InputReader.h"

#include "stl.h"

InputReader::InputReader(byte a3, byte a2, byte a1, byte a0, byte valid_pin, byte clear_pin, byte enter_pin)
        : address_pins{a0, a1, a2, a3}, valid_pin(valid_pin), clear_pin(clear_pin), enter_pin(enter_pin) {

    for (byte pin : {a3, a2, a1, a0, valid_pin, clear_pin, enter_pin}) {
        pinMode(pin, INPUT);
    }
}

byte InputReader::readNumber() const {
    byte result = 0;
    for (byte i = 0; i < 4; i++) {
        result |= digitalRead(address_pins[i]) ? 1 << i : 0;
    }
    return result;
}

bool InputReader::isNumberValid() const {
    return digitalRead(valid_pin);
}

bool InputReader::isClearEnabled() const {
    return digitalRead(clear_pin);
}

bool InputReader::isEnterEnabled() const {
    return digitalRead(enter_pin);
}
