#include "Offsets/offsets.h"
#include "Player/player.h"

int WIDTH = 900;
int HEIGHT = 650;

int TILES_HORIZONTAL = 16;
int TILES_VERTICAL = 10;

Memory m(L"warspear.exe");
HWND wind = FindWindowA(NULL, "Warspear Online");
ChainToAddress localPlayerChain(0x0090AE2C, { 0x0, 0x14 });
ChainToAddress entityList(0x0090AE2C, { 0x0, 0x10, 0x0 });
ChainToAddress objectList(0x0090AE2C, { 0x0, 0x24, 0x0 });
ChainToAddress cursorAddress(0x008FE480, { 0x2C, 0x10, 0x4, 0x338, 0x8 });
uintptr_t gameBaseAddress = m.getModuleBaseAddress(L"warspear.exe");
LocalPlayer localPlayer;

