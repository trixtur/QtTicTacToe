#include "tictactoe.h"

#include <QLoggingCategory>
#include <QMessageBox>

Q_LOGGING_CATEGORY(gameLog, "tictactoe.game")

TicTacToe::TicTacToe(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::TicTacToe)
{
    ui->setupUi(this);
    buttons_[0] = ui->TopLeft_Button;
    buttons_[1] = ui->TopMiddle_Button;
    buttons_[2] = ui->TopRight_Button;
    buttons_[3] = ui->MiddleLeft_Button;
    buttons_[4] = ui->MiddleMiddle_Button;
    buttons_[5] = ui->MiddleRight_Button;
    buttons_[6] = ui->BottomLeft_Button;
    buttons_[7] = ui->BottomMiddle_Button;
    buttons_[8] = ui->BottomRight_Button;

    for (int position = 0; position < 9; ++position)
        connect(buttons_[position], &QPushButton::clicked, this, &TicTacToe::handleMove);
    connect(ui->actionE_xit, &QAction::triggered, this, &QWidget::close);
    ui->menu_Edit->addAction(tr("Two Players"), this, [this] {
        computerMode_ = false;
        resetGame();
    });
    ui->menu_Edit->addAction(tr("Computer — Easy"), this, [this] {
        selectComputerMode(ComputerPlayer::Difficulty::Easy);
    });
    ui->menu_Edit->addAction(tr("Computer — Medium"), this, [this] {
        selectComputerMode(ComputerPlayer::Difficulty::Medium);
    });
    ui->menu_Edit->addAction(tr("Computer — Impossible"), this, [this] {
        selectComputerMode(ComputerPlayer::Difficulty::Impossible);
    });
    computerMode_ = false;
    difficulty_ = ComputerPlayer::Difficulty::Easy;
    resetGame();
    qCInfo(gameLog) << "game window initialized";
}

TicTacToe::~TicTacToe() { delete ui; }

void TicTacToe::handleMove()
{
    auto *button = qobject_cast<QPushButton *>(sender());
    int position = -1;
    for (int i = 0; i < 9; ++i) if (buttons_[i] == button) position = i;

    const char player = game_.currentPlayer();
    const Game::MoveResult result = game_.play(position);
    if (result == Game::MoveResult::Invalid) {
        qCWarning(gameLog) << "rejected move" << position << "player" << player;
        return;
    }
    qCInfo(gameLog) << "move accepted" << "position" << position << "player" << player;
    updateBoard();
    showResult(result);
    if (result == Game::MoveResult::Accepted && computerMode_) computerMove();
}

void TicTacToe::resetGame()
{
    game_.reset();
    updateBoard();
    ui->statusBar->showMessage(tr("New game — X's turn"));
    qCInfo(gameLog) << "game reset";
}

void TicTacToe::updateBoard()
{
    for (int position = 0; position < 9; ++position) {
        const QChar mark = game_.cell(position) == 0 ? QChar() : QChar(game_.cell(position));
        buttons_[position]->setText(mark);
        buttons_[position]->setEnabled(!game_.isOver() && mark.isNull());
    }
    if (!game_.isOver()) {
        const QString mode = computerMode_ && game_.currentPlayer() == 'O'
            ? tr("Computer's turn") : tr("%1's turn").arg(QChar(game_.currentPlayer()));
        ui->statusBar->showMessage(mode);
    }
}

void TicTacToe::computerMove()
{
    const int position = ComputerPlayer::chooseMove(game_, difficulty_);
    qCInfo(gameLog) << "computer move" << "difficulty" << static_cast<int>(difficulty_)
                    << "position" << position;
    const Game::MoveResult result = game_.play(position);
    updateBoard();
    showResult(result);
}

void TicTacToe::selectComputerMode(ComputerPlayer::Difficulty difficulty)
{
    computerMode_ = true;
    difficulty_ = difficulty;
    resetGame();
    qCInfo(gameLog) << "computer mode selected" << static_cast<int>(difficulty_);
}

void TicTacToe::showResult(Game::MoveResult result)
{
    if (result == Game::MoveResult::Accepted) return;

    const QString message = result == Game::MoveResult::Won
        ? tr("%1 has won!").arg(QChar(game_.winner()))
        : tr("The game ended in a tie.");
    if (result == Game::MoveResult::Won)
        qCInfo(gameLog) << "game completed" << "winner" << game_.winner();
    else
        qCInfo(gameLog) << "game completed" << "draw";

    ui->statusBar->showMessage(message);
    if (QMessageBox::question(this, tr("Game over"), message,
                              QMessageBox::Ok | QMessageBox::Close,
                              QMessageBox::Ok) == QMessageBox::Ok) resetGame();
}
