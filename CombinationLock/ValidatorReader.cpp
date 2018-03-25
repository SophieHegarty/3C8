#include "ValidatorReader.h"

#include "stl.h"

ValidatorReader::ValidatorReader(byte p2, byte p1, byte p0,
                                 byte correct_pin)
        : position_pins{p0, p1, p2}, correct_pin(correct_pin) {
    for (byte pin : {p2, p1, p0, correct_pin}) {
        pinMode(pin, INPUT);
    }
}

byte ValidatorReader::readPosition() const {
    byte result = 0;
    for (byte i = 0; i < 3; i++) {
        bitWrite(result, i, digitalRead(position_pins[i]));
    }
    return result;
}

byte ValidatorReader::stillCorrect() const {
    return digitalRead(correct_pin);
}
