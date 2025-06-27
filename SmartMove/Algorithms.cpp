#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "Algorithms.h"

std::vector<std::vector<int>> loadMap(std::string type, std::string filename) {
    std::ifstream map("maps/" + type + "/" + filename);
    std::vector<std::vector<int>> result;

    if (!map.is_open()) {
        std::cout << "Cannot open file " << type + "/" + filename << "\n";
        return result;
    }

    std::string line;
    while (std::getline(map, line)) {
        std::vector<int> row;
        for (char c : line) {
            if (c == '0' || c == '1') {
                row.push_back(c - '0');  // convert char to int
            }
            // ignore other chars like spaces or newline
        }
        if (!row.empty()) {
            result.push_back(row);
        }
    }

    return result;
}

#include <algorithm>
#include <climits>
#include <cmath>

bool Node::operator==(const Node& other) const {
    return x == other.x && y == other.y;
}

int heuristic(const Node& a, const Node& b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

int findLowestF(const std::vector<Node*>& open) {
    int lowest = INT_MAX;
    int index = 0;
    for (int i = 0; i < open.size(); ++i) {
        if (open[i]->f < lowest) {
            lowest = open[i]->f;
            index = i;
        }
    }
    return index;
}

bool inList(const std::vector<Node*>& list, const Node& node) {
    for (auto* n : list)
        if (*n == node) return true;
    return false;
}

bool findInList(const std::vector<Node*>& list, const Node& node, int& index) {
    for (int i = 0; i < list.size(); ++i) {
        if (*list[i] == node) {
            index = i;
            return true;
        }
    }
    return false;
}

bool isWalkable(int x, int y, const std::vector<std::vector<int>>& map) {
    return y >= 0 && y < map.size() &&
        x >= 0 && x < map[0].size() &&
        map[y][x] == 1;
}

std::vector<Node*> reconstructPath(Node* end) {
    std::vector<Node*> path;
    for (Node* node = end; node != nullptr; node = node->parent)
        path.push_back(node);
    std::reverse(path.begin(), path.end());
    return path;
}

std::vector<Node*> findPath(Node startVal, Node goalVal, const std::vector<std::vector<int>>& map) {
    Node* start = new Node(startVal.x, startVal.y);
    Node* goal = new Node(goalVal.x, goalVal.y);

    start->g = 0;
    start->h = heuristic(*start, *goal);
    start->f = start->g + start->h;

    std::vector<Node*> open{ start };
    std::vector<Node*> closed;
    std::vector<Node*> allAllocated{ start, goal };

    while (!open.empty()) {
        int currentIndex = findLowestF(open);
        Node* current = open[currentIndex];

        if (*current == *goal) {
            return reconstructPath(current);
            for (Node* n : allAllocated) delete n;
        }

        open.erase(open.begin() + currentIndex);
        closed.push_back(current);

        int dx[] = { 1, -1, 0, 0 };
        int dy[] = { 0, 0, 1, -1 };

        for (int d = 0; d < 4; ++d) {
            int nx = current->x + dx[d];
            int ny = current->y + dy[d];

            if (!isWalkable(nx, ny, map))
                continue;

            Node* neighbor = new Node(nx, ny);
            allAllocated.push_back(neighbor);

            if (inList(closed, *neighbor)) continue;

            int tentativeG = current->g + 1;

            int openIndex;
            if (!findInList(open, *neighbor, openIndex)) {
                neighbor->g = tentativeG;
                neighbor->h = heuristic(*neighbor, *goal);
                neighbor->f = neighbor->g + neighbor->h;
                neighbor->parent = current;
                open.push_back(neighbor);
            }
            else if (tentativeG < open[openIndex]->g) {
                open[openIndex]->g = tentativeG;
                open[openIndex]->f = tentativeG + open[openIndex]->h;
                open[openIndex]->parent = current;
            }
        }
    }

    std::cout << "No path found.\n";
    for (Node* n : allAllocated) delete n;
    return std::vector<Node*>{};
}
