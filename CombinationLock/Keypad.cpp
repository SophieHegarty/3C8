#include "Keypad.h"

                               /* Pinout to keys
                                * 1  2  3  4  5  6  7  8  9 10 11 12 13
                                * G  *  7  4  1  0  8  5  2  #  9  6  3
                                * x  0  1  2  3  4  5  6  7  8  9 10 11
                                *
                                * Keys to rows
                                * 0  1  2  3  4  5  6  7  8  9  *  #
                                * 4  3  7 11  2  6 10  1  5  9  0  8
                                * 
                                * Rows to latch pins
                                * 0  1  2  3  4  5  6  7  8  9 10 11
                                * 6  5  4  3  2  1  0  7 14 13 12 11
                                * 2  3  7 11  4  0 12  5  1 13  6 14
                                */
const byte Keypad::KEYMAP[12] = { 2, 3, 7, 11, 4, 0, 12, 5, 1, 13, 6, 14 };

Keypad::Keypad(byte a2, byte a1, byte a0,
               byte data_pin,
               byte write_disable_0,
               byte write_disable_1,
               byte reset_pin)
        : latches{ Latch8(a2, a1, a0, data_pin, write_disable_0, reset_pin),
                   Latch8(a2, a1, a0, data_pin, write_disable_1, reset_pin) } {}

void Keypad::setKey(byte key) const {
    clear();
    addKey(key);
}

void Keypad::writeKey(byte key, byte value) const {
    byte address = KEYMAP[key];
    const Latch8 *latch;
    if (address < 8) {
        latch = &latches[0];
    } else {
        latch = &latches[1];
        address -= 8;
    }
    latch->writePin(address, value);
}

void Keypad::addKey(byte key) const {
    writeKey(key, HIGH);
}

void Keypad::removeKey(byte key) const {
    writeKey(key, LOW);
}

void Keypad::reset() const {
    latches[0].reset();
    // Redundant, as the two latches use the same reset pin. Kept for uniformity
    // latches[1].reset();
}

void Keypad::clear() const {
    latches[0].clear();
    latches[1].clear();
}
