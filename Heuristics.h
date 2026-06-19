// A* functions --- h(n)
// estimating how far a board is from the solution
// Created by Juliana Suarez
//

#ifndef HEURISTICS_H
#define HEURISTICS_H

#include "PuzzleBoard.h"

class Heuristics {
public:

    // calculate how far each number is from the solution
    static int manhattanDistance(const PuzzleBoard& current, const PuzzleBoard& solve) {
        std::vector<int> currentBoard = current.getBoard();
        std::vector<int> goalBoard = solve.getBoard();

        int size = current.getSize();
        int distance = 0;

        for (int i = 0; i < currentBoard.size(); i++) {
            int tile = currentBoard[i];

            // ignore 0
            if (tile == 0) {
                continue;
            }
            int goalIndex = -1;

            // find where this tile should be in the solve board
            for (int j = 0; j < goalBoard.size(); j++) {
                if (goalBoard[j] == tile) {
                    goalIndex = j;
                    break;
                }
            }

            int currentRow = i / size;
            int currentCol = i % size;

            int goalRow = goalIndex / size;
            int goalCol = goalIndex % size;

            // vertical + horizontal distance
            distance += std::abs(currentRow - goalRow) + std::abs(currentCol - goalCol);
        }
        return distance;
    }

    // second heuristic, find if two tiles are in the correct row or column, but they are in an incorrect order
    static int linearNoOrder(const PuzzleBoard& current, const PuzzleBoard& solve) {
        int size = current.getSize();

        std::vector<int> currentBoard = current.getBoard();
        std::vector<int> goalBoard = solve.getBoard();

        int conflict = 0;

        // check row
        for (int row = 0; row < size; row++) {
            for (int col1 = 0; col1 < size; col1++) {
                for (int col2 = col1 + 1; col2 < size; col2++) {
                    int tile1 = currentBoard[row * size + col1];
                    int tile2 = currentBoard[row * size + col2];

                    if (tile1 == 0 || tile2 == 0) {
                        continue;
                    }
                    int goalIndex1 = findSolveIndex(goalBoard, tile1);
                    int goalIndex2 = findSolveIndex(goalBoard, tile2);

                    int goalRow1 = goalIndex1 / size;
                    int goalCol1 = goalIndex1 % size;

                    int goalRow2 = goalIndex2 / size;
                    int goalCol2 = goalIndex2 % size;

                    if (goalRow1 == row && goalRow2 == row && goalCol1 > goalCol2) {
                        conflict++;
                    }
                }
            }
        }

        // check column
        for (int col = 0; col < size; col++) {
            for (int row1 = 0; row1 < size; row1++) {
                for (int row2 = row1 + 1; row2 < size; row2++) {
                    int tile1 = currentBoard[row1 * size + col];
                    int tile2 = currentBoard[row2 * size + col];

                    if (tile1 == 0 || tile2 == 0) {
                        continue;
                    }

                    int goalIndex1 = findSolveIndex(goalBoard, tile1);
                    int goalIndex2 = findSolveIndex(goalBoard, tile2);

                    int goalRow1 = goalIndex1 / size;
                    int goalCol1 = goalIndex1 % size;

                    int goalRow2 = goalIndex2 / size;
                    int goalCol2 = goalIndex2 % size;

                    if (goalCol1 == col && goalCol2 == col && goalRow1 > goalRow2) {
                        conflict++;
                    }
                }
            }
        }

        // conflict requires at least 2 extra moves
        return conflict * 2;
    }

    // Manhattan Distance + Linear No order
    // calculate Manhattan Distance, add linear conflicts penalties
    // used when two tiles are in their correct row or column but reversed
    static int manhattanAndOrder(const PuzzleBoard& current, const PuzzleBoard& solve) {
        return manhattanDistance(current, solve) + linearNoOrder(current, solve);
    }

private:

    static int findSolveIndex(const std::vector<int>& solveBoard, int tile) {
        for (int i = 0; i < solveBoard.size(); i++) {
            if (solveBoard[i] == tile) {
                return i;
            }
        }
        return -1;
    }
};

#endif //HEURISTICS_H
