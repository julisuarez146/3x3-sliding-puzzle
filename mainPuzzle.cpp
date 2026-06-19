//
// Created by Juliana Suarez
//

#include <iostream>
#include <vector>

#include "PuzzleBoard.h"
#include "ASolve.h"

// print all boards in the solution path
void printSolution(const std::vector<PuzzleBoard>& path) {
    for (int i = 0; i < path.size(); i++) {
        std::cout << "Step " << i << ":" << std::endl;
        path[i].print();
    }
}

// run the 2 different heuristics on the puzzles
void runPuzzleExample(const std::string& title, const std::vector<int>& startBoard, const std::vector<int>& solvedBoard, int size) {
    PuzzleBoard start(startBoard, size);
    PuzzleBoard solved(solvedBoard, size);

    ASolve solver;

    std::cout << title << std::endl;
    // 1. manhattan Distance
    std::cout << "A* using Manhattan Distance" << std::endl;
    std::vector<PuzzleBoard> path1 = solver.solve(start, solved, 1);

    if (!path1.empty()) {
        printSolution(path1);
        std::cout << "Move count: " << path1.size() - 1 << std::endl;
        std::cout << "States explored: " << solver.getStatesExplored() << std::endl;
    } else {
        std::cout << "No solution found" << std::endl;
    }
    std::cout << std::endl;

    // 2. Manhattan Distance + Linear No order penalties
    std::cout << "A* using Manhattan + Linear Conflict" << std::endl;
    std::vector<PuzzleBoard> path2 = solver.solve(start, solved, 2);

    if (!path2.empty()) {
        printSolution(path2);
        std::cout << "Move count: " << path2.size() - 1 << std::endl;
        std::cout << "States explored: " << solver.getStatesExplored() << std::endl;
    } else {
        std::cout << "No solution found" << std::endl;
    }
    std::cout << std::endl;
}


int main() {
    int size = 3; //3x3

    // solved board for 3x3 puzzle
    std::vector<int> solvedBoard = {
        1, 2, 3,
        4, 5, 6,
        7, 8, 0
    };


    // easy example
    std::vector<int> easyBoard = {
        1, 2, 3,
        4, 0, 6,
        7, 5, 8
    };

    // hard example
    std::vector<int> hardBoard = {
        7, 2, 4,
        5, 0, 6,
        8, 3, 1
    };

    runPuzzleExample("Easy puzzle", easyBoard, solvedBoard, size);
    runPuzzleExample("Hard puzzle", hardBoard, solvedBoard, size);

    int size4 = 4; //4x4
    // solved board for 4x4 puzzle.
    std::vector<int> solvedBoard4 = {
        1,  2,  3,  4,
        5,  6,  7,  8,
        9, 10, 11, 12,
        13,14, 15, 0
    };

    // easy 4x4 example.
    std::vector<int> easyBoard4 = {
        1,  2,  3,  4,
        5,  6,  7,  8,
        9, 10, 11, 12,
        13,14,  0,15
    };

    runPuzzleExample("Easy 4x4 Puzzle", easyBoard4, solvedBoard4, size4);

    return 0;
}
