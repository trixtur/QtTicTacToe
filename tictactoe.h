#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <QMainWindow>
#include <QMessageBox>
#include "ui_tictactoe.h"

namespace Ui {
    class TicTacToe;
}

class TicTacToe : public QMainWindow
{
    Q_OBJECT

public:
    explicit TicTacToe(QWidget *parent = 0);
    ~TicTacToe();
private slots:
    void PressTopLeft();
    void PressTopMiddle();
    void PressTopRight();
    void PressMiddleLeft();
    void PressMiddleMiddle();
    void PressMiddleRight();
    void PressBottomLeft();
    void PressBottomMiddle();
    void PressBottomRight();
    void MBoxClose(int);

private:
    Ui::TicTacToe *ui;
    static const int DIALOG_OK_BUTTON = 1;
    bool is_X;
    char winner;
    bool isFull();
    bool hasWinner();
    bool initialSetup;
    void Reset();
    void RunButtonPress(QPushButton*);
    void SetButton(QPushButton**, const QString&);
};

#endif // TICTACTOE_H
