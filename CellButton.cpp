/*
CellButton.cpp
@Author: Taejun Ha
@Date: 02/04/2024
@Description: This function is responsible for each cell state such as revealed, flagged, and coordinates
and handles mouse events
*/

#include "CellButton.h"
#include <QIcon>

// Constructor, initializing the new CellButton with fixed size 
// @param parent: parent widget for the button
CellButton::CellButton(QWidget *parent) 
    : QPushButton(parent), x(0), y(0), revealed(false), flagged(false) {
    setFixedSize(20, 20);
}

// The function will set the coordinates of the cell button
// @param x: horizontal position of the cell in the grid
// @param y: vertical position of the cell in the grid
void CellButton::setCoordinates(int x, int y) {
    this->x = x;
    this->y = y;
}


// This function retrieves the horizontal position of the cell
// @return: the x-coordinate of the cell
int CellButton::getX() const {
    return x;
}


// This function retrieves the vertical position of the cell
// @return: y-coordinate of the cell
int CellButton::getY() const {
    return y;
}

// This function handles mouse clicking events and emits signals for left/right clicks
// @param event: mouse event information 
void CellButton::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        emit rightClicked(x, y); // emits signal when cell is right-clicked
    } else {
        QPushButton::mousePressEvent(event);
        emit leftClicked(x, y); // emits signal when cell is left-clicked
    }
}

// This function resets the cell to its default state - no icon, text, unflagged, unrevealed
void CellButton::reset() {
    setIcon(QIcon()); 
    setFlagged(false); 
    setRevealed(false); 
    setText(""); 
    setEnabled(true); 
    update(); // refreshes gameboard
}

// This function will display a number on the cell, indicating number of adjacent mines
// @param number: the number that gets displayed on the cell
void CellButton::displayNumber(int number) {
    if (number > 0) {
        setText(QString::number(number));
    } else {
        setText("");
    }
}

// This function will set the revealed state of the cell and update it
// @param rev: revealed state to set
void CellButton::setRevealed(bool rev) {
    revealed = rev;
    setEnabled(!revealed); // disables the button
}

// This function will check if the cell has been revealed yet
// @return: true if cell has been revealed, false if it hasn't
bool CellButton::isRevealed() const {
    return revealed;
}

// This function toggles the flagged state of the cell and updates the icon
void CellButton::toggleFlag() {
    if (isFlagged()) {
        setIcon(QIcon());
        flagged = false;
    } else {
        setIcon(QIcon(":/minesweeper_icons/mine_flag.png")); // adds a icon if flagged
        flagged = true;
    }
}

// This function will check if the cell has been flagged
// @return: True of cell has been flagged, false if it hasn't
bool CellButton::isFlagged() const {
    return flagged;
}

// This function will set the flagged state of cell and update the icon
// @param flag; flagged state to set
void CellButton::setFlagged(bool flag) {
    flagged = flag;
    if (flagged) {
        setIcon(QIcon(":/minesweeper_icons/mine_flag.png"));
    } else {
        setIcon(QIcon());
    }
}

// This function reveals the cell, displaying number of adjacent mines, and disables the cell
// @param number: number of adjacent mines 
void CellButton::reveal(int number) {
    setRevealed(true); // mark the cell as revealed
    displayNumber(number); // display number of adjacent mines
    if (number == 0) {
        setText("");
    } else {
        setText(QString::number(number));
    }

    setEnabled(false); 
}
