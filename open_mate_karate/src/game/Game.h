#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "CreatureTurnQueue.h"

class Game
{
public:
    Game
    (
        const std::vector<std::shared_ptr<Creature>>& leftSideCratures,
        const std::vector<std::shared_ptr<Creature>>& rightSideCreatures
    );

    ~Game();

    void move(FieldCoord targetField);
    void pass();
    void attack(FieldCoord attackedField);

private:
    Board board;
    CreatureTurnQueue creatureTurnQueue;

    void putCreaturesToBoard
    (
        const std::vector<std::shared_ptr<Creature>>& leftSideCratures,
        const std::vector<std::shared_ptr<Creature>>& rightSideCreatures
    );
};

#endif