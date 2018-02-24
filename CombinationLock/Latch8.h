#pragma once

#include "Arduino.h"

class Latch8 {
public:
    Latch8 (byte a2, byte a1, byte a0,
            byte data_pin,
            byte write_disable,
            byte reset_pin);
    virtual ~Latch8 () = default;

    void writePin(byte pin, byte value) const;
    void reset() const;

private:
    byte address_pins[3];
    byte data_pin;
    byte write_disable;
    byte reset_pin;
};
