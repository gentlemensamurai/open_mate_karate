#ifndef CREATURE_H
#define CREATURE_H

#include <string>

struct CreatureStats
{
    const std::string NAME;
    const unsigned short ATTACK;
    const unsigned short ARMOR;
    const unsigned short MAX_HP;
    const unsigned short MOVE_RANGE;

    CreatureStats
    (
        const std::string name,
        const unsigned short attack,
        const unsigned short armor,
        const unsigned short maxHp,
        const unsigned short moveRange
    );
};

class Creature
{
public:
    Creature
    (
        const std::string name,
        const unsigned short attack,
        const unsigned short armor,
        const unsigned short maxHp,
        const unsigned short moveRange
    );
    ~Creature();

private:
    CreatureStats creatureStats;
};

#endif // CREATURE_H