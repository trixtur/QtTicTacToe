#ifndef GAME_H
#define GAME_H

#include <array>
#include <vector>

class Game
{
public:
    enum class MoveResult { Invalid, Accepted, Won, Draw };

    Game();
    void reset();
    MoveResult play(int position);
    char cell(int position) const;
    char currentPlayer() const;
    char winner() const;
    bool isOver() const;
    bool isFull() const;
    std::vector<int> availableMoves() const;

private:
    std::array<char, 9> board_;
    char currentPlayer_;
    char winner_;
    bool gameOver_;
    bool hasWinner(char player) const;
};

#endif // GAME_H
