/*
@Author: Taejun Ha
@Date: 02/06/2024
@Description: This file is responsible for creating all windows in the GUI including the
main window that the user plays the game on, and the window for the user when
they win or lose the game. 
*/

#include "MainWindow.h"
#include <QMessageBox>
#include <QApplication>

// This constructor is for the main window of the game
// @param parent: parent widget
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // creating game GUI
    setFixedSize(800, 600);
    QWidget::setWindowTitle("Minesweeper");
    gameBoard = new GameBoard(30, 16, 99, this);
    setCentralWidget(gameBoard);

    connect(gameBoard, &GameBoard::gameWon, this, &MainWindow::onGameWon);
    connect(gameBoard, &GameBoard::gameLost, this, &MainWindow::onGameLost);
}

// This function will display a window pop-up for when the user wins the game
void MainWindow::onGameWon() {
    QMessageBox::information(this, "Game Won", "Congratulations! You have cleared the minefield!");
    askForNewGame(); // asks user if they want to play again
}

// This function will display a different window pop-up for when the user loses
void MainWindow::onGameLost() {
    QMessageBox gameLostBox;
    gameLostBox.setWindowTitle("Uh Oh!");
    gameLostBox.setText("You have hit a mine and exploded.");
    gameLostBox.setStandardButtons(QMessageBox::Retry | QMessageBox::Close);
    gameLostBox.setDefaultButton(QMessageBox::Retry);
    gameLostBox.setButtonText(QMessageBox::Retry, tr("Try Again?"));
    gameLostBox.setButtonText(QMessageBox::Close, tr("Exit"));

    QPixmap bombIcon(":/resources/minesweeper_icons/bomb_explode.png"); 
    gameLostBox.setIconPixmap(bombIcon.scaled(64, 64, Qt::KeepAspectRatio));

    int ret = gameLostBox.exec();
    switch (ret) {
      case QMessageBox::Retry:
          gameBoard->resetBoard();
          break;
      case QMessageBox::Close:
      default:
          QApplication::exit();
          break;
    }
}

// This function will ask the user if they want to play again with a window pop-up
void MainWindow::askForNewGame() {
    QMessageBox msgBox;
    msgBox.setWindowTitle("Play Again?");
    msgBox.setText("Would you like to start a new game?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);
    
    if (msgBox.exec() == QMessageBox::Yes) {
        gameBoard->resetBoard();    // resets the game for a new attempt
    } else {
        QApplication::quit();       // exits game
    }
}


