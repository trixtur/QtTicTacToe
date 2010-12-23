#include <QtGui/QApplication>
#include "tictactoe.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TicTacToe w;
    w.show();

    return a.exec();
}
