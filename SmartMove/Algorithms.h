#pragma once
#include <vector>
#include "../Offsets/Offsets.h"
#include <string>

struct Node {
    int x, y;
    int g = 0, h = 0, f = 0;
    Node* parent = nullptr;

    Node(int x, int y) : x(x), y(y) {}

    bool operator==(const Node& other) const;
};

// Heuristic: Manhattan distance
int heuristic(const Node& a, const Node& b);

// Lowest F-score from open list
int findLowestF(const std::vector<Node*>& open);

// Returns true if node is in the list
bool inList(const std::vector<Node*>& list, const Node& node);

// Returns true if found + index of the node
bool findInList(const std::vector<Node*>& list, const Node& node, int& index);

// Is this position walkable on map?
bool isWalkable(int x, int y, const std::vector<std::vector<int>>& map);

// Prints and reconstructs the final path
std::vector<Node*> reconstructPath(Node* end);

// Main pathfinding function
std::vector<Node*> findPath(Node startVal, Node goalVal, const std::vector<std::vector<int>>& map);

std::vector<std::vector<int>> loadMap(std::string type, std::string filename);
