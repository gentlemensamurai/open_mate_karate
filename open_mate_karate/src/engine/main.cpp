#include "Game.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "Camera.h"
#include "Mesh.h"

int main()
{
    Game game("Open Mate Karate", 1920, 1080, 3, 3, false, false);
    game.run();

    return 0;
}