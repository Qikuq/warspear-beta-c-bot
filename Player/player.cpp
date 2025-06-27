#include "player.h"
#include "../Offsets/Offsets.h"

void LocalPlayer::init() {
	address = m.ReadChain(gameBaseAddress + localPlayerChain.baseOffset, localPlayerChain.offsets);
}

void LocalPlayer::updateInfo() {
	posX = m.Read<short int>(m.ReadChain(address, { 0x8 }));
	posY = m.Read<short int>(m.ReadChain(address, { 0xA }));
	health = m.Read<int>(m.ReadChain(address, { 0x108 }));
	nameLength = m.Read<int>(m.ReadChain(address, { 0x5C }));
	isFighting = m.Read<short int>(m.ReadChain(address, { 0x2E4 }));

	m.ReadWIN(m.ReadChain(address, { 0x60 }), &this->name, this->nameLength * 2);
	this->name[this->nameLength] = L'\0';
}