#include <iostream>
#include <vector>
#include <string>
#include "memory/memory2.hpp"
#include <unordered_set>
#include "EntityList/ResolveEnList.h"
#include "Offsets/Offsets.h"
#include <thread>
#include "Player/player.h"
#include "Cursor/Cursor.h"
#include <chrono>
#include "SmartMove/Algorithms.h"
#include "Controls/controls.h"
#include <cmath>

bool smartMove(int x, int y, std::vector<std::vector<int>>& map, Cursor& cursor, bool specialFarm = false);

bool interact(int x, int y, std::vector<std::vector<int>>& map, Cursor& cursor) {
    localPlayer.updateInfo();
    std::vector<Node*> path = findPath({ localPlayer.posX, localPlayer.posY }, { x, y }, map);

    if (path.empty()) {
        std::wcout << "No path found." << std::endl;
        return false;
    }

    for (auto node : path) {
        localPlayer.updateInfo();
        cursor.move(localPlayer.posX, localPlayer.posY);

        int dx = node->x - localPlayer.posX;
        int dy = node->y - localPlayer.posY;

        if (dx == 1) pressKey(VK_RIGHT);
        else if (dx == -1) pressKey(VK_LEFT);
        else if (dy == 1) pressKey(VK_DOWN);
        else if (dy == -1) pressKey(VK_UP);

        std::this_thread::sleep_for(std::chrono::milliseconds(228));
        pressKey(VK_RETURN);
        std::this_thread::sleep_for(std::chrono::milliseconds(228));

        while (localPlayer.posX != node->x || localPlayer.posY != node->y) {
            localPlayer.updateInfo();

            if (localPlayer.isFighting &&
                std::abs(node->x - localPlayer.posX) <= 1 && std::abs(node->y - localPlayer.posY) <= 1) {
                return true;
            }

            if (localPlayer.posX == x && localPlayer.posY == y) {
                return true;
            }

            std::cout << "SmartMove is working..." << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
    }

    // Final check at end of path
    localPlayer.updateInfo();
    return localPlayer.posX == x && localPlayer.posY == y;
}

bool smartMove(int x, int y, std::vector<std::vector<int>>& map, Cursor& cursor) {
    localPlayer.updateInfo();
    std::vector<Node*> path = findPath({ localPlayer.posX, localPlayer.posY }, { x, y }, map);

    if (path.empty()) {
        std::wcout << "No path found." << std::endl;
        return false;
    }

    for (auto node : path) {
        localPlayer.updateInfo();
        cursor.move(localPlayer.posX, localPlayer.posY);

        int dx = node->x - localPlayer.posX;
        int dy = node->y - localPlayer.posY;

        if (std::abs(x - localPlayer.posX) <= 1 && std::abs(y - localPlayer.posY) <= 1) {
            return true;
        }

        if (dx == 1) pressKey(VK_RIGHT);
        else if (dx == -1) pressKey(VK_LEFT);
        else if (dy == 1) pressKey(VK_DOWN);
        else if (dy == -1) pressKey(VK_UP);

        std::this_thread::sleep_for(std::chrono::milliseconds(228));
        pressKey(VK_RETURN);
        std::this_thread::sleep_for(std::chrono::milliseconds(228));

        while (localPlayer.posX != node->x || localPlayer.posY != node->y) {
            localPlayer.updateInfo();

            if (localPlayer.isFighting &&
                std::abs(node->x - localPlayer.posX) <= 1 && std::abs(node->y - localPlayer.posY) <= 1) {
                return true;
            }

            if (localPlayer.posX == x && localPlayer.posY == y) {
                return true;
            }

            std::cout << "SmartMove is working..." << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
    }

    // Final check at end of path
    localPlayer.updateInfo();
    return localPlayer.posX == x && localPlayer.posY == y;
}

int main() {
    Cursor cursor;
    localPlayer.init();
    uintptr_t entityListAddress = m.ReadChain(gameBaseAddress + entityList.baseOffset, entityList.offsets);
    uintptr_t objectListAddress = m.ReadChain(gameBaseAddress + objectList.baseOffset, objectList.offsets);
    std::vector<Entity> entities;
    std::vector<Object> objects;

    updateEntityAndObjectList(entityListAddress, objectListAddress, entities, objects, m);

    if (!wind) {
        std::wcout << "Could not find Warspear window!" << std::endl;
        return 1;
    }

    ShowWindow(wind, SW_SHOW);
    SetWindowPos(wind, HWND_TOP, 0, 0, WIDTH, HEIGHT, SWP_SHOWWINDOW);
    SetForegroundWindow(wind);

    auto map = loadMap("firstborn", "3.txt"); // Here u can use maps

    updateEntityAndObjectList(entityListAddress, objectListAddress, entities, objects, m);
    
    return 0;
}
