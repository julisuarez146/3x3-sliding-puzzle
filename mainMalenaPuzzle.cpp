//
// Created by Juliana Suarez on 6/8/26.
//

#include <Malena/Engine/App/Application.h>
#include <Malena/Graphics/Text/Text.h>
#include <Malena/Graphics/Controls/RectangleButton.h>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include <string>

#include "PuzzleBoard.h"
#include "ASolve.h"

// create Malena
class PuzzleVisualizer : public ml::Application {
private:

    // A* solver object
    ASolve solver;

    // Stores every board
    std::vector<PuzzleBoard> path;

    int currentStep = 0;
    // Puzzle information
    int size = 3;
    int totalMoves = 0;
    int statesExplored = 0;

    // automatic time
    sf::Clock stepClock;
    float secondsPerStep = 0.8f;

    // Text objects
    ml::Text titleText;
    ml::Text infoText;
    ml::Text boardText;
    ml::Text instructionText;

    // Button
    ml::RectangleButton nextButton;
    ml::RectangleButton randomButton;

    int currentPuzzleIndex = 0;

    struct PuzzleExample {
        std::string name;
        int size;
        int shuffleMoves;
    };

    std::vector<PuzzleExample> puzzles;

public:
    PuzzleVisualizer()
        : ml::Application(sf::VideoMode({900, 700}), "Sliding Puzzle A*") {
    }

    // initialize
    void initialization() {
        createPuzzle();
        setupText();
        setupButtons();
        updateDisplay();
    }

    // move puzzle automatically
    void automaticStep() {
        if (path.empty()) {
            return;
        }

        if (stepClock.getElapsedTime().asSeconds() >= secondsPerStep) {
            if (currentStep < static_cast<int>(path.size()) - 1) {
                currentStep++;
                updateDisplay();
            }
            stepClock.restart();
        }
    }

private:
    // create the puzzle and solve
    void createPuzzle() {
        puzzles = {
            {"Easy Level 3x3", 3, 10},
            {"Hard Level 3x3", 3, 30},
            {"Easy Level 4x4", 4, 15}
        };
    }

    std::vector<int> createSolvedVector(int puzzleSize) {
        std::vector<int> solvedVector;

        int totalTiles = puzzleSize * puzzleSize;

        for (int i = 1; i < totalTiles; i++) {
            solvedVector.push_back(i);
        }
        solvedVector.push_back(0);
        return solvedVector;
    }


    void loadCurrentPuzzle() {
        PuzzleExample puzzle = puzzles[currentPuzzleIndex];

        size = puzzle.size;
        currentStep = 0;

        std::vector<int> solvedVector = createSolvedVector(size);

        PuzzleBoard solved(solvedVector, size);

        PuzzleBoard start = PuzzleBoard::generateRandomBoard(
            solved,
            puzzle.shuffleMoves
        );

        path = solver.solve(start, solved, 2);

        if (!path.empty()) {
            totalMoves = static_cast<int>(path.size()) - 1;
        } else {
            totalMoves = 0;
        }

        statesExplored = solver.getStatesExplored();

        stepClock.restart();
        updateDisplay();
    }

    // Sets up
    void setupText() {
        titleText.setString("Sliding Puzzle Solver");
        titleText.setCharacterSize(30);
        titleText.setPosition({60, 30});
        titleText.setFillColor(sf::Color::White);

        infoText.setCharacterSize(20);
        infoText.setPosition({60, 90});
        infoText.setFillColor(sf::Color::White);

        boardText.setCharacterSize(50);
        boardText.setPosition({350, 250});
        boardText.setFillColor(sf::Color::White);

        instructionText.setString("Random puzzle solved automatically");
        instructionText.setCharacterSize(20);
        instructionText.setPosition({100, 600});
        instructionText.setFillColor(sf::Color::White);

        addComponent(titleText);
        addComponent(infoText);
        addComponent(boardText);
        addComponent(instructionText);
    }

    // set up buttons
    void setupButtons() {
        nextButton.setString("Next");
        nextButton.setSize({180, 55});
        nextButton.setPosition({170, 520});
        nextButton.setFillColor(sf::Color::White);
        nextButton.setTextColor(sf::Color::Black);
        nextButton.setOutlineColor(sf::Color::White);

        nextButton.onClick([this]() {
            currentPuzzleIndex++;

            if (currentPuzzleIndex >= static_cast<int>(puzzles.size())) {
                currentPuzzleIndex = 0;
            }
            loadCurrentPuzzle();
        });

        randomButton.setString("New Random");
        randomButton.setSize({260, 55});
        randomButton.setPosition({520, 520});
        randomButton.setFillColor(sf::Color::White);
        randomButton.setTextColor(sf::Color::Black);
        randomButton.setOutlineColor(sf::Color::White);

        randomButton.onClick([this]() {
            loadCurrentPuzzle();
        });

        addComponent(nextButton);
        addComponent(randomButton);
    }

    // updates the board
    void updateDisplay() {
        if (path.empty()) {
            return;
        }

        infoText.setString(
            puzzles[currentPuzzleIndex].name + "\n"
            "Heuristic: Manhattan Distance + Linear Conflict\n"
            "Step: " + std::to_string(currentStep) + " / " + std::to_string(totalMoves) + "\n"
            "Total moves: " + std::to_string(totalMoves) + "\n"
            "States explored: " + std::to_string(statesExplored)
        );

        boardText.setString(boardToDisplay(path[currentStep]));
    }

    // Converts board
    std::string boardToDisplay(const PuzzleBoard& puzzle) {
        std::vector<int> board = puzzle.getBoard();
        std::string result = "";

        for (int i = 0; i < static_cast<int>(board.size()); i++) {
            if (board[i] == 0) {
                result += "    ";
            } else {
                if (board[i] < 10) {
                    result += " ";
                }
                result += std::to_string(board[i]) + "  ";
            }
            if ((i + 1) % size == 0) {
                result += "\n";
            }
        }
        return result;
    }
};

int main() {
    PuzzleVisualizer app;

    // Initialize
    app.initialization();

    // Automatically move
    app.onUpdate([&app]() {
        app.automaticStep();
    });

    app.run();

    return 0;
}
