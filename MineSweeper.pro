QT       += core widgets gui 
TARGET = myapp
TEMPLATE = app 
CONFIG += c++11
SOURCES += main.cpp \
         GameBoard.cpp \
         MainWindow.cpp \
         CellButton.cpp
HEADERS += CellButton.h \
        GameBoard.h \
        MainWindow.h 
RESOURCES += resources/minesweeper_icons/images.qrc
QMAKE_CXXFLAGS += -Wno-deprecated-copy