/*
GameBoard.cpp
@Author: Taejun Ha
@Date: 02/04/2024
@Description: This file is responsible for the game logic of minesweeper such as checking for a win, resetting the board, place mines, 
and showing the number of adjacent mines
*/

#include "GameBoard.h"
#include <QIcon>
#include "CellButton.h"
#include <algorithm> 
#include <QTime>
#include <QCoreApplication>
#include <QMessageBox>

// This is the constructor that initializes the game board with mines and dimensions
// @param width: width of game board
// @param height: height of game board
// @param mines: number of mines on game board
// @param parent: parent widget 
GameBoard::GameBoard(int width, int height, int mines, QWidget *parent)
    : QWidget(parent), width(width), height(height), minesCount(mines) {
    this->mines.resize(height);

    for (int i = 0; i < height; ++i) {
        this->mines[i].resize(width); 
        std::fill(this->mines[i].begin(), this->mines[i].end(), false); 
    }

    setupBoard(width, height);
    placeMines();
}

// This function sets the game board up by taking in the parameters of width and height of the game board 
// and making a grid
// @param width: width of the game board
// @param height: height of the game board
void GameBoard::setupBoard(int width, int height) {
    gridLayout = new QGridLayout(this);
    gridLayout->setSpacing(1);

    for (int y = 0; y < height; ++y) {
        QVector<CellButton*> row;
        for (int x = 0; x < width; ++x) {
            auto* cell = new CellButton(this);
            cell->setCoordinates(x, y);
            gridLayout->addWidget(cell, y, x);
            row.push_back(cell);

            // connect signals and slots for CellButton
            connect(cell, &CellButton::leftClicked, this, &GameBoard::handleCellLeftClicked);
            connect(cell, &CellButton::rightClicked, this, &GameBoard::handleCellRightClicked);
        }
        cells.push_back(row);
    }
}

// This function places all the mines in the board randomly 
void GameBoard::placeMines() {
    static bool seeded = false;
    if (!seeded) {
        QTime time = QTime::currentTime();
        qsrand(static_cast<uint>(time.msec() + reinterpret_cast<long long>(this)));
        seeded = true;
    }

    for (int placedMines = 0; placedMines < minesCount; ) {
        int x = qrand() % width;
        int y = qrand() % height;

        // makes sure a mine isn't going ontop of another mine
        if (!mines[y][x]) {
            mines[y][x] = true;
            placedMines++;
        }
    }
}

// This function takes in the parameters of x and y, which is the location of the cell, and will
// determine what to do whenever the user left clicks on the cell, as in will it show the number
// of adjacent mines, or check if a user won, or if they lost
// @param x: horizontal position of cell
// @param y: vertical position of cell
void GameBoard::handleCellLeftClicked(int x, int y) {
    // ignore the click when there is flag
    if (cells[y][x]->isFlagged()) {
        return;
    }

    // there's a mine - game lost
    if (mines[y][x]) {
        cells[y][x]->setIcon(QIcon(":/minesweeper_icons/bomb.png")); 
        emit gameLost();
    } else {
        // reveal the cell and if there are no adjacent mines, reveal adjacent cells
        int adjacentMines = countAdjacentMines(x, y);
        cells[y][x]->reveal(adjacentMines); 
        if (adjacentMines == 0) {
            revealAdjacentCells(x, y);
        }
    }
    if (checkForWin()) {
        emit gameWon();
    }
}

// This function takes in the coordinates, x and y, of the cell the user right clicks on to flag it
// @param x: horizontal position of the cell
// @param y: vertical position of the cell
void GameBoard::handleCellRightClicked(int x, int y) {
    cells[y][x]->toggleFlag(); // flag
}

// This function is responsible for what happens when a cell is revealed, taking in the x and y
// coordinates of the cell. The function will check if the coordinates given are within the 
// gameboard, reveal all the surrounding cells where there aren't adjacent mines
// @param x: horizontal position of the cell
// @param y: vertical position of the cell
void GameBoard::revealCell(int x, int y) {
    // check the bounds and whether the cell is already revealed or flagged
    if (x < 0 || x >= width || y < 0 || y >= height || cells[y][x]->isRevealed() || cells[y][x]->isFlagged()) {
        return;
    }
    cells[y][x]->setRevealed(true);

    int adjacentMinesCount = countAdjacentMines(x, y);
    cells[y][x]->displayNumber(adjacentMinesCount);

    // reveal all surrounding cells when there are no adjacent mines
    if (adjacentMinesCount == 0) {
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (i == 0 && j == 0) continue; // skip the current cell
                int newX = x + j;
                int newY = y + i;
                revealCell(newX, newY); 
            }
        }
    }
}

// This function will check if the user has won or not, function will return true if the
// user has won, and will return false if they lost
// @return: true/false depending on outcome of game
bool GameBoard::checkForWin() {
    // checks every single cell to see if there is a cell with a mine
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (!mines[y][x] && !cells[y][x]->isRevealed()) {
                return false;
            }
        }
    }
    return true;
}

// This function takes in the cell coordinates, x and y, and will reveal all the adjacent cells
// @param x: horizontal position of the cell
// @param y: vertical position of the cell
void GameBoard::revealAdjacentCells(int x, int y) {
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int newX = x + j;
            int newY = y + i;
            if (newX >= 0 && newX < 30 && newY >= 0 && newY < 16 && !cells[newY][newX]->isRevealed()) {
                cells[newY][newX]->reveal(countAdjacentMines(newX, newY));
                if (countAdjacentMines(newX, newY) == 0) {
                    revealAdjacentCells(newX, newY);
                }
            }
        }
    }
}

// This function takes in the cell coordinates, x and y, and will count the number of adjacent mines to that
// cell
// @param x: horizontal position of the cell
// @param y: vertical position of the cell
// @return: the count of adjacent mines
int GameBoard::countAdjacentMines(int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            int newX = x + j;
            int newY = y + i;
            if (newX >= 0 && newX < width && newY >= 0 && newY < height && mines[newY][newX]) {
                count++;
            }
        }
    }
    return count;
}

// This function will reset the game board and place new mines in different locations and then
// update the game board
void GameBoard::resetBoard() {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            mines[y][x] = false; 
            cells[y][x]->reset(); 
        }
    }
    placeMines();
    update();
}
