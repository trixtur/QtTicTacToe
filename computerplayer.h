#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include "game.h"

class ComputerPlayer
{
public:
    enum class Difficulty { Easy, Medium, Impossible };

    static int chooseMove(const Game &game, Difficulty difficulty);

private:
    static int chooseRandomMove(const Game &game);
    static int chooseMediumMove(const Game &game);
    static int minimax(Game game, char computer);
};

#endif // COMPUTERPLAYER_H
