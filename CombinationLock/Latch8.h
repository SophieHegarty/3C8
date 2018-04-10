#ifndef LATCH8_H_P9NJ2JDM
#define LATCH8_H_P9NJ2JDM

#include "Arduino.h"

/**
 * Class aiding the use of the 4099 chip
 */
class Latch8 {
public:
    Latch8 (byte a2, byte a1, byte a0,
            byte data_pin,
            byte write_disable,
            byte reset_pin);

    void writePin(byte pin, byte value) const;
    void reset() const;
    void clear() const;

private:
    byte address_pins[3];
    byte data_pin;
    byte write_disable;
    byte reset_pin;
};

#endif /* end of include guard: LATCH8_H_P9NJ2JDM */
