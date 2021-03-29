#include "Creature.h"

CreatureStats::CreatureStats
(
    const std::string name,
    const short attack,
    const short armor,
    const short maxHp,
    const short moveRange
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
    const short attack,
    const short armor,
    const short maxHp,
    const short moveRange
)
    : CREATURE_STATS { name, attack, armor, maxHp, moveRange },
      currentHp { CREATURE_STATS.MAX_HP }
{

}

Creature::~Creature()
{

}

void Creature::attack(const std::shared_ptr<Creature> defender)
{
    short damage { CREATURE_STATS.ATTACK - defender->CREATURE_STATS.ARMOR };
    
    if (damage > 0)
    {
        defender->currentHp = defender->currentHp - damage;
    }
}

const short Creature::getCurrentHp() const
{
    return currentHp;
}