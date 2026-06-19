// each Node represents a puzzle position within the A*
// Created by Juliana Suarez
//

#ifndef ASOLVE_H
#define ASOLVE_H

#include "PuzzleBoard.h"
#include "Heuristics.h"

#include <queue>
#include <unordered_set>
#include <memory>
#include <iostream>
#include <vector>

// A Node stores one puzzle board plus the information A* needs to decide which board to explore next
struct Node {
    PuzzleBoard board; // current board
    int g; // movements from start to current node
    int h; // movements from current node to solution
    int f; // total movements, f = g + h
    std::shared_ptr<Node> parent; // rebuild previous board

    Node(PuzzleBoard b, int gCost, int hCost, std::shared_ptr<Node> p = nullptr)
        : board(b), g(gCost), h(hCost), f(gCost + hCost), parent(p) {}
};

// priority_queue, the node with the lowest f value has the highest priority
struct CompareNode {
    bool operator()(const std::shared_ptr<Node>& a, const std::shared_ptr<Node>& b) {
        return a->f > b->f;
    }
};

class ASolve {
private:
    int statesExplored;

public:
    ASolve() {
        statesExplored = 0;
    }

    // A* algorithm.
    // heuristicType 1 = Manhattan Distance
    // heuristicType 2 = Manhattan + Linear No order
    std::vector<PuzzleBoard> solve(const PuzzleBoard& start, const PuzzleBoard& solvedBoard, int heuristicType) {
        statesExplored = 0;

        //heap
        std::priority_queue< std::shared_ptr<Node>,
            std::vector<std::shared_ptr<Node>>,
            CompareNode > openList;

        // set visited
        std::unordered_set<std::string> visited;

        // calculate first heuristic
        int startH = calculateHeuristic(start, solvedBoard, heuristicType);

        std::shared_ptr<Node> startNode = std::make_shared<Node>(start, 0, startH);

        openList.push(startNode);

        // A* searches through the graph of possible puzzle boards
        while (!openList.empty()) {
            // get better board option
            std::shared_ptr<Node> current = openList.top();
            openList.pop();

            std::string currentKey = current->board.toString();

            if (visited.find(currentKey) != visited.end()) {
                continue;
            }

            visited.insert(currentKey);
            statesExplored++;
            // board is solved, return the solution path
            if (current->board.isSolved(solvedBoard)) {
                return solutionPath(current);
            }
            // get possible boards
            std::vector<PuzzleBoard> neighbors = current->board.getNeighbors();

            for (PuzzleBoard neighbor : neighbors) {
                std::string neighborKey = neighbor.toString();

                if (visited.find(neighborKey) == visited.end()) {
                    int newG = current->g + 1;
                    int newH = calculateHeuristic(neighbor, solvedBoard, heuristicType);

                    std::shared_ptr<Node> neighborNode =
                        std::make_shared<Node>(neighbor, newG, newH, current);

                    openList.push(neighborNode);
                }
            }
        }
        return {};
    }

    // return  how many states A* explored
    int getStatesExplored() const {
        return statesExplored;
    }

private:

    // heuristics
    int calculateHeuristic(const PuzzleBoard& current, const PuzzleBoard& solve, int heuristicType) {
        if (heuristicType == 1) {
            return Heuristics::manhattanDistance(current, solve);
        }
        return Heuristics::manhattanAndOrder(current, solve);
    }

    // recursive follows parent pointers until it reaches the start node
    void buildPathRecursive(std::shared_ptr<Node> node,
                            std::vector<PuzzleBoard>& path) {
        if (node == nullptr) {
            return;
        }
        // first go all the way back to the start
        buildPathRecursive(node->parent, path);

        // then add the states in correct order
        path.push_back(node->board);
    }

    // returns the solution path
    std::vector<PuzzleBoard> solutionPath(std::shared_ptr<Node> node) {
        std::vector<PuzzleBoard> path;

        buildPathRecursive(node, path);

        return path;
    }
};

#endif //ASOLVE_H

