#include "Game.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "Camera.h"
#include "Mesh.h"

#include "../game/Board.h"

int main()
{
    Board board(20, 15);

    board.addCreature(FieldCoord(19, 5), std::make_shared<Creature>("Goblin"));
    board.addCreature(FieldCoord(2, 2), std::make_shared<Creature>("Orc"));

    board.moveCreature(FieldCoord(1, 1), FieldCoord(3, 3));

    //Game game("Open Mate Karate", 1920, 1080, 3, 3, false, false);
    //game.run();

    return 0;
}