#include "ValidatorWriter.h"

#include "stl.h"

ValidatorWriter::ValidatorWriter(byte p2, byte p1, byte p0,
                                 byte correct_pin,
                                 byte enter_pin)
        : position_pins{p0, p1, p2},
          correct_pin(correct_pin),
          enter_pin(enter_pin) {
    for (byte pin : {p2, p1, p0, correct_pin, enter_pin}) {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);
    }
}

void ValidatorWriter::writePosition(byte position) const {
    for (byte i = 0; i < 3; i++) {
        digitalWrite(position_pins[i], bitRead(position, i));
    }
}

void ValidatorWriter::setCorrect(bool correct) const {
    digitalWrite(correct_pin, correct ? HIGH : LOW);
}

void ValidatorWriter::setEnter(bool enter) const {
    digitalWrite(enter_pin, enter ? HIGH : LOW);
}
