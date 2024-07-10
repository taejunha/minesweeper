/*
@Author: Taejun Ha
@Date: 02/04/2024
@Description: This header files is responsible for setting up the main window the user
plays the game on*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "GameBoard.h" 

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots: 
    void onGameWon();
    void onGameLost();

private:
    GameBoard *gameBoard; 
    void askForNewGame(); 
};

#endif // MAINWINDOW_H
