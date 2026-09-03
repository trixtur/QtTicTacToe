#include "computerplayer.h"

#include <QRandomGenerator>
#include <algorithm>
#include <limits>

int ComputerPlayer::chooseMove(const Game &game, Difficulty difficulty)
{
    if (game.isOver() || game.availableMoves().empty()) return -1;
    if (difficulty == Difficulty::Easy) return chooseRandomMove(game);
    if (difficulty == Difficulty::Medium) return chooseMediumMove(game);

    int bestMove = -1;
    int bestScore = std::numeric_limits<int>::min();
    for (int move : game.availableMoves()) {
        Game candidate = game;
        candidate.play(move);
        const int score = minimax(candidate, game.currentPlayer());
        if (score > bestScore) {
            bestScore = score;
            bestMove = move;
        }
    }
    return bestMove;
}

int ComputerPlayer::chooseRandomMove(const Game &game)
{
    const auto moves = game.availableMoves();
    return moves[QRandomGenerator::global()->bounded(static_cast<int>(moves.size()))];
}

int ComputerPlayer::chooseMediumMove(const Game &game)
{
    const char computer = game.currentPlayer();
    for (int move : game.availableMoves()) {
        Game candidate = game;
        if (candidate.play(move) == Game::MoveResult::Won) return move;
    }

    const char opponent = computer == 'X' ? 'O' : 'X';
    const int lines[8][3] = {{0,1,2}, {3,4,5}, {6,7,8}, {0,3,6},
                             {1,4,7}, {2,5,8}, {0,4,8}, {2,4,6}};
    for (const auto &line : lines) {
        int empty = -1;
        int opponentMarks = 0;
        for (int i : line) {
            if (game.cell(i) == opponent) ++opponentMarks;
            if (game.cell(i) == 0) empty = i;
        }
        if (opponentMarks == 2 && empty >= 0) return empty;
    }
    return chooseRandomMove(game);
}

int ComputerPlayer::minimax(Game game, char computer)
{
    if (game.isOver()) {
        if (game.winner() == computer) return 10;
        if (game.winner() != 0) return -10;
        return 0;
    }

    const bool maximizing = game.currentPlayer() == computer;
    int best = maximizing ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
    for (int move : game.availableMoves()) {
        Game candidate = game;
        candidate.play(move);
        const int score = minimax(candidate, computer);
        best = maximizing ? std::max(best, score) : std::min(best, score);
    }
    return best;
}
