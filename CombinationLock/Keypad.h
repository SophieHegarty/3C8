#ifndef KEYPAD_H_ZWSJK4QU
#define KEYPAD_H_ZWSJK4QU

#include "Latch8.h"

/**
 * Class simulating keypresses
 */
class Keypad {
private:
    Latch8 latches[2];

    static const byte KEYMAP[13];

public:
    Keypad(byte a2, byte a1, byte a0,
           byte data_pin,
           byte write_disable_0,
           byte write_disable_1,
           byte reset_pin);
    virtual ~Keypad() = default;

    static const byte ENTER_KEY = 1;
    static const byte RESET_KEY = 9;

    void setKey(byte key) const; // reset and set only the key
    void writeKey(byte key, byte value) const; // do not reset
    void addKey(byte key) const; // do not reset
    void removeKey(byte key) const; // do not reset
    void reset() const;
};

#endif /* end of include guard: KEYPAD_H_ZWSJK4QU */
