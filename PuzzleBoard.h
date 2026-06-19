// set up the board for the puzzle
// Created by Juliana Suarez
//

#ifndef PUZZLEBOARD_H
#define PUZZLEBOARD_H

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <random>
#include <algorithm>


// save one board configuration
class PuzzleBoard {
private:
    std::vector<int> board; // store puzzle in a 1D vector
    int size;               // 3x3 or 4x4

public:
    // Constructor
    PuzzleBoard(std::vector<int> startBoard, int puzzleSize) {
        board = startBoard;
        size = puzzleSize;
    }

    // Return board in a vector
    std::vector<int> getBoard() const {
        return board;
    }

    // return puzzle size
    int getSize() const {
        return size; // 3=3x3 -- 4=4x4
    }

    // Convert board into a string
    // it can be stored in set
    std::string toString() const {
        std::stringstream ss;

        for (int value : board) {
            ss << value << ",";
        }
        return ss.str();
    }

    // Checks if the board is solved
    bool isSolved(const PuzzleBoard& solve) const {
        return board == solve.getBoard();
    }

    // search 0, we can just move around the 0, 0 = blank space
    int findBlank() const {
        for (int i = 0; i < board.size(); i++) {
            if (board[i] == 0) {
                return i;
            }
        }
        return -1;
    }

    // get all possible movements by blank space
    std::vector<PuzzleBoard> getNeighbors() const {
        std::vector<PuzzleBoard> neighbors;

        int blankIndex = findBlank();

        int row = blankIndex / size;
        int col = blankIndex % size;

        // possible moves are up, down, left, right
        // each move crate a new puzzle board
        std::vector<std::pair<int, int>> moves ={
            {-1, 0}, {1, 0}, {0, -1}, {0, 1}
        };

        for (auto move : moves) {
            int newRow = row + move.first;
            int newCol = col + move.second;

            // check if the new position is inside the board.
            if (newRow >= 0 && newRow < size && newCol >= 0 && newCol < size) {
                int newIndex = newRow * size + newCol;

                std::vector<int> newBoard = board;

                // swap blank with the selected number.
                std::swap(newBoard[blankIndex], newBoard[newIndex]);
                neighbors.push_back(PuzzleBoard(newBoard, size));
            }
        }
        return neighbors;
    }

    // Create a random board
    // valid random moves from solved board
    static PuzzleBoard generateRandomBoard(const PuzzleBoard& solvedBoard, int shuffleMoves) {
        PuzzleBoard randomBoard = solvedBoard;

        std::random_device rd;
        std::mt19937 gen(rd());

        for (int i = 0; i < shuffleMoves; i++) {
            std::vector<PuzzleBoard> neighbors = randomBoard.getNeighbors();

            std::uniform_int_distribution<> dist(0, neighbors.size() - 1);
            randomBoard = neighbors[dist(gen)];
        }

        return randomBoard;
    }

    // print board
    void print() const {
        for (int i = 0; i < board.size(); i++) {
            if (board[i] == 0) {
                std::cout << "  ";
            } else {
                std::cout << board[i] << " ";
            }
            if ((i + 1) % size == 0) {
                std::cout << std::endl;
            }
        }
        std::cout << std::endl;
    }

    // Return the value at one index in the board
    int getTile(int index) const {
        return board[index];
    }
};

#endif //PUZZLEBOARD_H
