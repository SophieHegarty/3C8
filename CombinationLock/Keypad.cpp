#include "Keypad.h"

const byte Keypad::KEYMAP[12] = { 5, 4, 8, 12, 3, 7, 11, 2, 6, 10, 1, 9 };

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
