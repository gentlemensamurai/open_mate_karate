#include "Game.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "Camera.h"
#include "Mesh.h"

#include "../game/Board.h"
#include "../game/CreatureTurnQueue.h"

int main()
{
    Board board(20, 15);
    std::vector<std::shared_ptr<Creature>> creatures;
    creatures.push_back(std::make_shared<Creature>("Goblin", 5, 5, 5, 5));
    creatures.push_back(std::make_shared<Creature>("Orc", 10, 10, 10, 10));
    creatures.push_back(std::make_shared<Creature>("Minotaur", 20, 20, 20, 20));

    board.addCreature(FieldCoord(0, 0), creatures[0]);
    board.addCreature(FieldCoord(5, 5), creatures[1]);
    board.addCreature(FieldCoord(10, 10), creatures[2]);

    CreatureTurnQueue creatureTurnQueue(creatures);

    std::shared_ptr<Creature> activeCreature { creatureTurnQueue.getActiveCreature() };

    activeCreature->attack(board.getCreature(FieldCoord(5, 5)));

    //Game game("Open Mate Karate", 1920, 1080, 3, 3, false, false);
    //game.run();

    return 0;
}