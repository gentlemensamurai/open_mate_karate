#include "Creature.h"

CreatureStats::CreatureStats
(
    const std::string name,
    const unsigned short attack,
    const unsigned short armor,
    const unsigned short maxHp,
    const unsigned short moveRange
)
    : NAME { name },
      ATTACK { attack },
      ARMOR { armor },
      MAX_HP { maxHp },
      MOVE_RANGE { moveRange }
{

}

Creature::Creature
(
    const std::string name,
    const unsigned short attack,
    const unsigned short armor,
    const unsigned short maxHp,
    const unsigned short moveRange
)
    : creatureStats { name, attack, armor, maxHp, moveRange }
{

}

Creature::~Creature()
{

}