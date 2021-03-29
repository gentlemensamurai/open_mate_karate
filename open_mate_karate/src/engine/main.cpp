#include "Game.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "Camera.h"
#include "Mesh.h"

#include "../game/Board.h"

int main()
{
    Board board;

    board.addCreature(FieldCoord(2, 2), std::make_shared<Creature>("Goblin"));
    board.addCreature(FieldCoord(2, 2), std::make_shared<Creature>("Orc"));
    board.addCreature(FieldCoord(1, 1), std::make_shared<Creature>("Minotaur"));

    std::shared_ptr<Creature> creature { board.getCreature(FieldCoord(1, 1)) };

    if (creature != nullptr)
    {
        std::cout << "Creature exists: " << creature->name << std::endl;
    }
    else
    {
        std::cout << "Creature doesn't exist!" << std::endl;
    }

    //Game game("Open Mate Karate", 1920, 1080, 3, 3, false, false);
    //game.run();

    return 0;
}