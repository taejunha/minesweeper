/*
CellButton.h
@Author: Taejun Ha
@Date: 02/04/2024
@Description: This header file defines the structure and the constructor of the GameBoard class 
*/

#ifndef CELLBUTTON_H
#define CELLBUTTON_H

#include <QPushButton>
#include <QMouseEvent>

class CellButton : public QPushButton {
    Q_OBJECT

public:
    explicit CellButton(QWidget *parent = nullptr);
    void setFlagged(bool flag);
    void setCoordinates(int x, int y);
    int getX() const;
    int getY() const;
    void reset();
    void setRevealed(bool revealed);
    void displayNumber(int number);
    void toggleFlag();
    bool isRevealed() const;
    bool isFlagged() const;
    void reveal(int number);

signals:
    void leftClicked(int x, int y);
    void rightClicked(int x, int y);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    int x, y;
    bool revealed;
    bool flagged;
};

#endif // CELLBUTTON_H
