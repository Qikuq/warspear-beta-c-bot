#include "../EntityList/ResolveEnList.h"
#pragma once

class LocalPlayer : public Entity {
public:
	short isFighting;
	void updateInfo();
	void init();
};

extern LocalPlayer localPlayer;
