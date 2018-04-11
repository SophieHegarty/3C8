#include "Latch8.h"

#include "stl.h"

Latch8::Latch8 (byte a2, byte a1, byte a0,
                byte data_pin,
                byte write_disable,
                byte reset_pin)
        : address_pins{a0, a1, a2},
          data_pin(data_pin),
          write_disable(write_disable),
          reset_pin(reset_pin) {
    for (byte pin : {a2, a1, a0, data_pin}) {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);
    }

    if (reset_pin != BYTE_MAX) {
        pinMode(reset_pin, OUTPUT);
        digitalWrite(reset_pin, LOW);
    }

    pinMode(write_disable, OUTPUT);
    digitalWrite(write_disable, HIGH);

    clear();
}

void Latch8::writePin(byte pin, byte value) const {
    for (byte digit = 0; digit < 3; digit++) {
        digitalWrite(address_pins[digit], bitRead(pin, digit) ? HIGH : LOW);
    }
    digitalWrite(data_pin, value);
    delay(1);
    digitalWrite(write_disable, LOW);
    delay(1);
    digitalWrite(write_disable, HIGH);
}

void Latch8::reset() const {
    if (reset_pin != BYTE_MAX) {
        digitalWrite(reset_pin, HIGH);
        delay(1);
        digitalWrite(reset_pin, LOW);
    }
}

void Latch8::clear() const {
    for (byte i = 0; i < 8; i++) {
        writePin(i, LOW);
    }
}
