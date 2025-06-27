#include "ResolveEnList.h"
#include <vector>
#include <unordered_set>
#include "../memory/memory2.hpp"
#include <cmath>

std::vector<uintptr_t> resolveEntityListTree(Memory* m, uintptr_t entityListAddress) {
    uintptr_t left = 0x4;
    uintptr_t right = 0x8;

    std::unordered_set<uintptr_t> visited;
    std::vector<uintptr_t> stack{ entityListAddress };
    std::vector<uintptr_t> validEntityNodes;

    while (!stack.empty()) {

        if (visited.contains(stack.back()) || m->Read<uintptr_t>(stack.back()) == 0x0) {
            stack.pop_back();
            continue;
        }

        validEntityNodes.push_back(stack.back());
        visited.insert(stack.back());

        // Adding children and popping element out from the stack:

        uintptr_t leftChild = m->ReadChain(stack.back(), { left });
        uintptr_t rightChild = m->ReadChain(stack.back(), { right });

        // DEBUG  std::cout << "Node: " << std::hex << stack.back() << "\n    Left child: " << leftChild << "\n    Right Child: " << rightChild << std::endl;

        stack.pop_back();

        if (rightChild) {
            stack.push_back(rightChild);
        }
        if (leftChild) {
            stack.push_back(leftChild);
        }

    }

    visited.clear();
    stack.clear();

    return validEntityNodes;
}

Entity::Entity(uintptr_t address, Memory& m) {
    this->address = address;
    this->health = m.Read<int>(m.ReadChain(address, { 0x14, 0x108 }));
    this->nameLength = m.Read<int>(m.ReadChain(address, { 0x14, 0x58 }));

    m.ReadWIN(m.ReadChain(address, { 0x14, 0x60 }), &this->name, this->nameLength * 2);

    this->name[this->nameLength] = L'\0';

    this->posX = m.Read<short int>(m.ReadChain(address, { 0x14, 0x8 }));
    this->posY = m.Read<short int>(m.ReadChain(address, { 0x14, 0xA }));
}
Object::Object(uintptr_t address, Memory& m) {
    this->address = address;
    this->nameLength = m.Read<int>(m.ReadChain(address, { 0x14, 0x58 }));

    m.ReadWIN(m.ReadChain(address, { 0x14, 0x60 }), &this->name, this->nameLength * 2);

    this->name[this->nameLength] = L'\0';

    this->posX = m.Read<short int>(m.ReadChain(address, { 0x14, 0x8 }));
    this->posY = m.Read<short int>(m.ReadChain(address, { 0x14, 0xA }));
}

void updateEntityAndObjectList(uintptr_t entityListAddress, uintptr_t objectListAddress, std::vector<Entity>& entities, std::vector<Object>& objects, Memory& m) {
    std::vector<uintptr_t> entityAddresses = std::move(resolveEntityListTree(&m, entityListAddress));
    std::vector<uintptr_t> objectAddresses = std::move(resolveEntityListTree(&m, objectListAddress));
    
    entities.clear();
    objects.clear();

    entities.reserve(entityAddresses.size());

    for (auto i : entityAddresses) {
        entities.emplace_back(Entity(i, m));
    }

    objects.reserve(objectAddresses.size());

    for (auto i : objectAddresses) {
        objects.emplace_back(Object(i, m));
    }
}
Entity* findEntityByName(Memory& m, uintptr_t localPlayerAddress, const std::vector<Entity>& entityList, const wchar_t* name) {
    std::vector<const Entity*> matchedEntities;

    for (const auto& entity : entityList) {
        if (wcscmp(name, entity.name) == 0 && entity.health > 0) {
            matchedEntities.emplace_back(&entity);
        }
    }

    if (!matchedEntities.empty()) {
        short localPlayerPosX = m.Read<short>(m.ReadChain(localPlayerAddress, { 0x8 }));
        short localPlayerPosY = m.Read<short>(m.ReadChain(localPlayerAddress, { 0xA }));

        int minDistance = INT_MAX;
        const Entity* closestEntity = nullptr;

        for (const auto* entity : matchedEntities) {
            int dx = entity->posX - localPlayerPosX;
            int dy = entity->posY - localPlayerPosY;
            int distance = dx * dx + dy * dy;

            if (distance < minDistance) {
                minDistance = distance;
                closestEntity = entity;
            }
        }

        return const_cast<Entity*>(closestEntity); // if caller expects non-const
    }

    std::wcout << L"Entity: " << name << L" not found or all are dead." << std::endl;
    return nullptr;
}
void updateEntityInfo(Entity& ent, Memory& m) {
    ent.health = m.Read<int>(m.ReadChain(ent.address, { 0x14, 0x108 }));
    ent.nameLength = m.Read<int>(m.ReadChain(ent.address, { 0x14, 0x58 }));

    m.ReadWIN(m.ReadChain(ent.address, { 0x14, 0x60 }), &ent.name, ent.nameLength * 2);

    ent.name[ent.nameLength] = L'\0';

    ent.posX = m.Read<short int>(m.ReadChain(ent.address, { 0x14, 0x8 }));
    ent.posY = m.Read<short int>(m.ReadChain(ent.address, { 0x14, 0xA }));
    ent.isFighting = m.Read<short int>(m.ReadChain(ent.address, { 0x2E4 }));
}