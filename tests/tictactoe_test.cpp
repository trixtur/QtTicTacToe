#include "game.h"
#include "computerplayer.h"
#include <cstdlib>
#include <iostream>

namespace {
int failures = 0;
void check(bool condition, const char *expression, int line)
{
    if (!condition) {
        std::cerr << "FAIL line " << line << ": " << expression << '\n';
        ++failures;
    }
}
#define CHECK(expression) check((expression), #expression, __LINE__)
#define CHECK_EQ(actual, expected) check((actual) == (expected), #actual " == " #expected, __LINE__)
}

void startsWithEmptyBoard()
{
    Game game;
    CHECK_EQ(game.currentPlayer(), 'X'); CHECK(!game.isFull()); CHECK(!game.isOver());
    for (int position = 0; position < 9; ++position) CHECK_EQ(game.cell(position), char(0));
}

void alternatesPlayersAndRejectsOccupiedCells()
{
    Game game;
    CHECK_EQ(game.play(0), Game::MoveResult::Accepted); CHECK_EQ(game.cell(0), 'X');
    CHECK_EQ(game.currentPlayer(), 'O'); CHECK_EQ(game.play(0), Game::MoveResult::Invalid);
    CHECK_EQ(game.currentPlayer(), 'O'); CHECK_EQ(game.play(-1), Game::MoveResult::Invalid);
    CHECK_EQ(game.play(9), Game::MoveResult::Invalid);
}

void detectsRowsColumnsAndDiagonals()
{
    Game row;
    row.play(0); row.play(3); row.play(1); row.play(4);
    CHECK_EQ(row.play(2), Game::MoveResult::Won); CHECK_EQ(row.winner(), 'X');

    Game diagonal;
    diagonal.play(0); diagonal.play(1); diagonal.play(4); diagonal.play(2);
    CHECK_EQ(diagonal.play(8), Game::MoveResult::Won); CHECK_EQ(diagonal.winner(), 'X');
}

void detectsDraw()
{
    Game game;
    const int moves[] = {0, 1, 2, 4, 3, 5, 7, 6, 8};
    for (int i = 0; i < 8; ++i) CHECK_EQ(game.play(moves[i]), Game::MoveResult::Accepted);
    CHECK_EQ(game.play(moves[8]), Game::MoveResult::Draw); CHECK(game.isFull()); CHECK(game.isOver());
}

void rejectsMovesAfterGameOver()
{
    Game game;
    game.play(0); game.play(3); game.play(1); game.play(4);
    CHECK_EQ(game.play(2), Game::MoveResult::Won); CHECK_EQ(game.play(5), Game::MoveResult::Invalid);
}

void computerAlwaysChoosesAnAvailableMove()
{
    Game game;
    game.play(0);
    const int move = ComputerPlayer::chooseMove(game, ComputerPlayer::Difficulty::Easy);
    CHECK(move >= 0 && move < 9 && game.cell(move) == 0);
}

void mediumBlocksAnImmediateWin()
{
    Game game;
    game.play(0); game.play(3); game.play(1);
    CHECK_EQ(ComputerPlayer::chooseMove(game, ComputerPlayer::Difficulty::Medium), 2);
}

void impossibleNeverLoses()
{
    Game game;
    CHECK_EQ(game.play(0), Game::MoveResult::Accepted);
    while (!game.isOver()) {
        const int move = ComputerPlayer::chooseMove(game, ComputerPlayer::Difficulty::Impossible);
        CHECK(move >= 0 && move < 9);
        CHECK(game.play(move) != Game::MoveResult::Won || game.winner() == 'O');
        if (game.isOver()) break;
        const auto moves = game.availableMoves();
        CHECK(!moves.empty());
        game.play(moves.back());
    }
    CHECK(game.winner() != 'X');
}

int main()
{
    startsWithEmptyBoard(); alternatesPlayersAndRejectsOccupiedCells();
    detectsRowsColumnsAndDiagonals(); detectsDraw(); rejectsMovesAfterGameOver();
    computerAlwaysChoosesAnAvailableMove(); mediumBlocksAnImmediateWin(); impossibleNeverLoses();
    std::cout << (failures == 0 ? "All tests passed\n" : "Tests failed\n");
    return failures == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
