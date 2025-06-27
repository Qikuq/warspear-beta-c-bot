#include "Cursor.h"

Cursor::Cursor() {
    updateCursor();
    cursorId = 0;
}

void Cursor::updateCursor() {
    address = m.ReadChain(gameBaseAddress + cursorAddress.baseOffset, cursorAddress.offsets);
    x = m.Read<short int>(m.ReadChain(gameBaseAddress + cursorAddress.baseOffset, cursorAddress.offsets));
    y = m.Read<short int>(m.ReadChain(gameBaseAddress + cursorAddress.baseOffset, cursorAddress.offsets) + 0x2);
    cursorId = m.Read<short int>(m.ReadChain(gameBaseAddress + cursorAddress.baseOffset, cursorAddress.offsets) + 0x70);
}
void Cursor::move(int x, int y) {
    m.Write<short>(this->address, x);
    m.Write<short>(this->address + 0x64, x);
    m.Write<short>(this->address + 0x2, y);
    m.Write<short>(this->address + 0x66, y);
}