/*
GameBoard.h
@Author: Taejun Ha
@Date: 02/04/2024
@Description: This header file defines the interface for the GameBoard
*/

#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>
#include <QGridLayout>
#include "CellButton.h"

class GameBoard : public QWidget {
    Q_OBJECT

public:
    explicit GameBoard(int width, int height, int mines, QWidget *parent = nullptr);
    void resetBoard();
    void revealCell(int x, int y);
    bool checkForWin();
    int countAdjacentMines(int x, int y);
    void revealAdjacentCells(int x, int y);

signals:
    void gameWon();
    void gameLost();

public slots:
    void handleCellLeftClicked(int x, int y); 
    void handleCellRightClicked(int x, int y); 

private:
    int width;
    int height;
    QGridLayout *gridLayout;
    QVector<QVector<CellButton*>> cells;
    QVector<QVector<bool>> mines;
    int minesCount;
    void setupBoard(int width, int height);
    void placeMines();
};

#endif // GAMEBOARD_H
