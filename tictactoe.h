#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <QMainWindow>
#include <QPushButton>
#include "game.h"
#include "computerplayer.h"
#include "ui_tictactoe.h"

class TicTacToe : public QMainWindow
{
    Q_OBJECT
public:
    explicit TicTacToe(QWidget *parent = nullptr);
    ~TicTacToe();

private slots:
    void handleMove();
    void resetGame();

private:
    Ui::TicTacToe *ui;
    Game game_;
    bool computerMode_;
    ComputerPlayer::Difficulty difficulty_;
    QPushButton *buttons_[9];
    void updateBoard();
    void showResult(Game::MoveResult result);
    void computerMove();
    void selectComputerMode(ComputerPlayer::Difficulty difficulty);
};

#endif // TICTACTOE_H
