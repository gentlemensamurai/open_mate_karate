#ifndef CREATURE_H
#define CREATURE_H

#include <string>
#include <memory>

struct CreatureStats
{
    const std::string NAME;
    const short ATTACK;
    const short ARMOR;
    const short MAX_HP;
    const short MOVE_RANGE;

    CreatureStats
    (
        const std::string name,
        const short attack,
        const short armor,
        const short maxHp,
        const short moveRange
    );
};

class Creature
{
public:
    Creature
    (
        const std::string name,
        const short attack,
        const short armor,
        const short maxHp,
        const short moveRange
    );
    ~Creature();

    void attack(std::shared_ptr<Creature> defender);

private:
    const CreatureStats CREATURE_STATS;
    short currentHp;

    const short getCurrentHp() const;
    void setCurrentHp(const short hp);
    bool isAlive();
    short calculateDamage(const CreatureStats defenderStats);
};

#endif // CREATURE_H