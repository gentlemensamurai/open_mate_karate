#include "Game.h"

Game::Game
(
    const std::vector<std::shared_ptr<Creature>>& leftSideCratures,
    const std::vector<std::shared_ptr<Creature>>& rightSideCreatures
)
    : board { 20, 15 },
    creatureTurnQueue { leftSideCratures, rightSideCreatures }
{
    putCreaturesToBoard(leftSideCratures, rightSideCreatures);
}

Game::~Game()
{

}

void Game::move(FieldCoord targetField)
{
    //board.moveCreature(creatureTurnQueue.getActiveCreature(), )
}

void Game::putCreaturesToBoard
(
    const std::vector<std::shared_ptr<Creature>>& leftSideCratures,
    const std::vector<std::shared_ptr<Creature>>& rightSideCreatures
)
{
    for (size_t i { 0 }; i < leftSideCratures.size(); i++)
    {
        board.addCreature(FieldCoord(0, i * 2), leftSideCratures[i]);
    }

    for (size_t i { 0 }; i < rightSideCreatures.size(); i++)
    {
        board.addCreature(FieldCoord(board.BOARD_WIDTH - 1, i * 2), rightSideCreatures[i]);
    }
}