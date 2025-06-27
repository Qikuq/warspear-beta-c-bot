#pragma once

#include <Windows.h>
#include <vector>
#include "../memory/memory2.hpp"
#include "../Player/player.h"

extern int WIDTH;
extern int HEIGHT;

extern HWND wind;

extern int TILES_HORIZONTAL;
extern int TILES_VERTICAL;

extern Memory m;

extern uintptr_t gameBaseAddress;

struct ChainToAddress {
	uintptr_t baseOffset;
	std::vector<uintptr_t> offsets;
	ChainToAddress() = default;

	ChainToAddress(uintptr_t baseOffset, std::vector<uintptr_t> offsets)
		: baseOffset(baseOffset), offsets(std::move(offsets)) {
	}
};
extern ChainToAddress localPlayerChain;
extern ChainToAddress entityList;
extern ChainToAddress objectList;
extern ChainToAddress cursorAddress;