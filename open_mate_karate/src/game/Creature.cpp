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

void Creature::attack(std::shared_ptr<Creature> defender)
{
    if(!isAlive()) return;

    short attackDamage { calculateDamage(defender->CREATURE_STATS) };
    
    if (attackDamage > 0)
    {
        defender->setCurrentHp(defender->getCurrentHp() - attackDamage);
    }

    short counterDamage { defender->calculateDamage(CREATURE_STATS) };

    if (counterDamage > 0)
    {
        setCurrentHp(getCurrentHp() - counterDamage);
    }
}

const short Creature::getCurrentHp() const
{
    return currentHp;
}

void Creature::setCurrentHp(const short hp)
{
    currentHp = hp;
}

bool Creature::isAlive()
{
    return currentHp > 0;
}

short Creature::calculateDamage(const CreatureStats defenderStats)
{
    return CREATURE_STATS.ATTACK - defenderStats.ARMOR;
}