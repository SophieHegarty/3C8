#include "Latch8.h"

#include "stl.h"

Latch8::Latch8 (byte a2, byte a1, byte a0, byte data_pin, byte write_disable, byte reset_pin)
        : address_pins{a0, a1, a2}, data_pin(data_pin), write_disable(write_disable), reset_pin(reset_pin) {

    for (byte pin : {a2, a1, a0, data_pin, reset_pin}) {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);
    }

    pinMode(write_disable, OUTPUT);
    digitalWrite(write_disable, HIGH);
}

void Latch8::writePin(byte pin, byte value) const {
    for (byte digit = 0; digit < 3; digit++) {
        digitalWrite(address_pins[digit], (pin & (1 << digit)) ? HIGH : LOW);
    }
    digitalWrite(data_pin, value);
    delayMicroseconds(10);
    digitalWrite(write_disable, LOW);
    delayMicroseconds(10);
    digitalWrite(write_disable, HIGH);
}

void Latch8::reset() const {
    digitalWrite(reset_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(reset_pin, LOW);
}