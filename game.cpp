#include "game.h"

namespace {
const int winningLines[8][3] = {
    {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
    {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
    {0, 4, 8}, {2, 4, 6}
};
}

Game::Game() { reset(); }

void Game::reset()
{
    board_.fill(0);
    currentPlayer_ = 'X';
    winner_ = 0;
    gameOver_ = false;
}

Game::MoveResult Game::play(int position)
{
    if (position < 0 || position >= static_cast<int>(board_.size()) ||
        board_[position] != 0 || gameOver_) return MoveResult::Invalid;

    board_[position] = currentPlayer_;
    if (hasWinner(currentPlayer_)) {
        winner_ = currentPlayer_;
        gameOver_ = true;
        return MoveResult::Won;
    }
    if (isFull()) {
        gameOver_ = true;
        return MoveResult::Draw;
    }
    currentPlayer_ = currentPlayer_ == 'X' ? 'O' : 'X';
    return MoveResult::Accepted;
}

char Game::cell(int position) const
{
    return position >= 0 && position < static_cast<int>(board_.size()) ? board_[position] : 0;
}

char Game::currentPlayer() const { return currentPlayer_; }
char Game::winner() const { return winner_; }
bool Game::isOver() const { return gameOver_; }

bool Game::isFull() const
{
    for (char value : board_) if (value == 0) return false;
    return true;
}

std::vector<int> Game::availableMoves() const
{
    std::vector<int> moves;
    for (int position = 0; position < static_cast<int>(board_.size()); ++position)
        if (board_[position] == 0) moves.push_back(position);
    return moves;
}

bool Game::hasWinner(char player) const
{
    for (const auto &line : winningLines) {
        if (board_[line[0]] == player && board_[line[1]] == player && board_[line[2]] == player) return true;
    }
    return false;
}
