#include "../memory/memory2.hpp"

#pragma once

class Entity {
public:
    uintptr_t address;
    short int posX;
    short int posY;
    short int isFighting;
    int health;
    int nameLength;
    wchar_t name[32];
    Entity() : address(0), health(0), nameLength(0), posX(-1), posY(-1) {
        memset(name, 0, sizeof(name));
    }
    Entity(uintptr_t address, Memory& m);
private:

};
class Object {
public:
    uintptr_t address;
    short int posX;
    short int posY;
    int nameLength;
    wchar_t name[32];
    Object() : address(0), nameLength(0), posX(-1), posY(-1) {
        memset(name, 0, sizeof(name));
    }
    Object(uintptr_t address, Memory& m);
private:
};

std::vector<uintptr_t> resolveEntityListTree(Memory* m, uintptr_t entityListAddress);

void updateEntityAndObjectList(uintptr_t entityListAddress, uintptr_t objectListAddress, std::vector<Entity>& entities, std::vector<Object>& objects, Memory& m);
Entity* findEntityByName(Memory& m, uintptr_t localPlayerAddress, const std::vector<Entity>& entityList, const wchar_t* name);
void updateEntityInfo(Entity& ent, Memory& m);