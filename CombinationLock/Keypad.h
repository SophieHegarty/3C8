#ifndef KEYPAD_H_ZWSJK4QU
#define KEYPAD_H_ZWSJK4QU

#include "Latch8.h"

class Keypad {
public:
    Keypad(byte a2, byte a1, byte a0,
           byte data_pin,
           byte reset_pin,
           byte write_disable_0,
           byte write_disable_1);
    virtual ~Keypad() = default;

    // TODO: use actual keypad pinout
    static const byte RESET_KEY = 10;
    static const byte ENTER_KEY = 11;

    void setKey(byte key) const; // reset and set only the key
    void writeKey(byte key, byte value) const; // do not reset
    void addKey(byte key) const; // do not reset
    void removeKey(byte key) const; // do not reset
    void reset() const;

private:
    Latch8 latches[2];

    static constexpr byte KEYMAP[13] = { 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 10, 11 };
};

#endif /* end of include guard: KEYPAD_H_ZWSJK4QU */
