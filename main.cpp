/*
main.cpp
@Author: Taejun Ha
@Date: 02/04/2024
@Description: This file sets up the basic QT application with a main window
*/

#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
