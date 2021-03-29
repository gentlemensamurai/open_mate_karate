#include "engine/Engine.h"

#include "game/Game.h"

int main()
{
    Board board(20, 15);

    std::vector<std::shared_ptr<Creature>> leftSideCreatures;
    leftSideCreatures.push_back(std::make_shared<Creature>("Goblin", 5, 5, 5, 5));
    leftSideCreatures.push_back(std::make_shared<Creature>("Orc", 10, 10, 10, 10));
    leftSideCreatures.push_back(std::make_shared<Creature>("Minotaur", 20, 20, 20, 20));

    board.addCreature(FieldCoord(0, 0), leftSideCreatures[0]);
    board.addCreature(FieldCoord(0, 2), leftSideCreatures[1]);
    board.addCreature(FieldCoord(0, 3), leftSideCreatures[2]);

    std::vector<std::shared_ptr<Creature>> rightSideCreatures;
    rightSideCreatures.push_back(std::make_shared<Creature>("Demon", 5, 5, 5, 5));
    rightSideCreatures.push_back(std::make_shared<Creature>("Dragon", 10, 10, 10, 10));
    rightSideCreatures.push_back(std::make_shared<Creature>("Elf", 20, 20, 20, 20));

    board.addCreature(FieldCoord(4, 4), rightSideCreatures[0]);
    board.addCreature(FieldCoord(5, 5), rightSideCreatures[1]);
    board.addCreature(FieldCoord(6, 6), rightSideCreatures[2]);

    CreatureTurnQueue creatureTurnQueue(leftSideCreatures, rightSideCreatures);

    std::shared_ptr<Creature> activeCreature { creatureTurnQueue.getActiveCreature() };

    activeCreature->attack(board.getCreature(FieldCoord(5, 5)));

    std::shared_ptr<Creature> creatureOutOfTheBoard { std::make_shared<Creature>("Goblin", 5, 5, 5, 5) };

    std::optional<FieldCoord> fieldCoord { board.getFieldCoord(creatureOutOfTheBoard) };

    //Engine engine("Open Mate Karate", 1920, 1080, 3, 3, false, false);
    //engine.run();

    return 0;
}