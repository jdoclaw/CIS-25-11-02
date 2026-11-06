#include "Board.h"
;
#include "Game.h"
;

#include <iostream>
#include <sstream>
#include <string>

namespace {
const Board* winningBoard = nullptr;
}

Board::Board() : grid(nullptr) {
    grid = new char*[3];
    for (int row = 0; row < 3; ++row) {
        grid[row] = new char[3];
    }
    clear();
}

Board::~Board() {
    if (winningBoard == this) {
        winningBoard = nullptr;
    }
    for (int row = 0; row < 3; ++row) {
        delete[] grid[row];
    }
    delete[] grid;
}

bool Board::makeMove(int row, int col, char crossOrCircle) {
    if (row < 0 || row >= 3 || col < 0 || col >= 3 ||
        (crossOrCircle != 'x' && crossOrCircle != 'o') ||
        grid[row][col] != ' ') {
        return false;
    }

    grid[row][col] = crossOrCircle;
    std::cout << "\n  1   2   3\n";
    for (int boardRow = 0; boardRow < 3; ++boardRow) {
        std::cout << boardRow + 1 << ' ' << grid[boardRow][0] << " | "
                  << grid[boardRow][1] << " | " << grid[boardRow][2] << '\n';
        if (boardRow < 2) {
            std::cout << " ---+---+---\n";
        }
    }
    return true;
}

void Board::clear() {
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            grid[row][col] = ' ';
        }
    }
    if (winningBoard == this) {
        winningBoard = nullptr;
    }
}

void Board::checkWinner() {
    for (int row = 0; row < 3; ++row) {
        if (grid[row][0] != ' ' && grid[row][0] == grid[row][1] &&
            grid[row][1] == grid[row][2]) {
            winningBoard = this;
            std::cout << grid[row][0] << " wins!\n";
            return;
        }
    }

    for (int col = 0; col < 3; ++col) {
        if (grid[0][col] != ' ' && grid[0][col] == grid[1][col] &&
            grid[1][col] == grid[2][col]) {
            winningBoard = this;
            std::cout << grid[0][col] << " wins!\n";
            return;
        }
    }

    if (grid[0][0] != ' ' && grid[0][0] == grid[1][1] &&
        grid[1][1] == grid[2][2]) {
        winningBoard = this;
        std::cout << grid[0][0] << " wins!\n";
        return;
    }

    if (grid[0][2] != ' ' && grid[0][2] == grid[1][1] &&
        grid[1][1] == grid[2][0]) {
        winningBoard = this;
        std::cout << grid[0][2] << " wins!\n";
        return;
    }

    if (winningBoard == this) {
        winningBoard = nullptr;
    }
}

bool Board::isFull() {
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            if (grid[row][col] == ' ') {
                return false;
            }
        }
    }
    return true;
}

void Game::run() {
    board.clear();
    crossOrCircle = 'x';
    std::cout << "Tic Tac Toe\nEnter row and column (1-3) to make a move.\n";

    while (true) {
        readInput();
        if (!std::cin) {
            std::cout << "\nGame ended.\n";
            return;
        }

        board.checkWinner();
        if (winningBoard == &board) {
            return;
        }
        if (board.isFull()) {
            std::cout << "It's a draw!\n";
            return;
        }
        switchPlayer();
    }
}

void Game::switchPlayer() {
    crossOrCircle = crossOrCircle == 'x' ? 'o' : 'x';
}

void Game::readInput() {
    while (true) {
        std::string input;
        int row;
        int col;
        std::cout << crossOrCircle << "'s turn. Choose row and column: ";

        if (!std::getline(std::cin, input)) {
            return;
        }

        std::istringstream inputStream(input);
        std::string extraInput;
        if (!(inputStream >> row >> col) || (inputStream >> extraInput) ||
            row < 1 || row > 3 || col < 1 || col > 3) {
            std::cout << "Please enter exactly two numbers from 1 to 3.\n";
            continue;
        }

        if (!board.makeMove(row - 1, col - 1, crossOrCircle)) {
            std::cout << "That square is unavailable. Choose an empty square.\n";
            continue;
        }
        return;
    }
}
