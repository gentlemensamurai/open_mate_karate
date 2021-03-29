#include "Game.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "Camera.h"
#include "Mesh.h"

#include "../game/Board.h"
#include "../game/CreatureTurnQueue.h"

int main()
{
    std::vector<std::shared_ptr<Creature>> creatures;
    creatures.push_back(std::make_shared<Creature>("Goblin"));
    creatures.push_back(std::make_shared<Creature>("Orc"));
    creatures.push_back(std::make_shared<Creature>("Minotaur"));

    CreatureTurnQueue creatureTurnQueue(creatures);

    //Game game("Open Mate Karate", 1920, 1080, 3, 3, false, false);
    //game.run();

    return 0;
}