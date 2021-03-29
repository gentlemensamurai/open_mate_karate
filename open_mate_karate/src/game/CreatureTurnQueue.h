#ifndef CREATURE_TURN_QUEUE_H
#define CREATURE_TURN_QUEUE_H

#include <memory>
#include <queue>
#include "Creature.h"

class CreatureTurnQueue
{
public:
    CreatureTurnQueue
    (
        const std::vector<std::shared_ptr<Creature>>& leftSideCreatures,
        const std::vector<std::shared_ptr<Creature>>& rightSideCreatures
    );
    ~CreatureTurnQueue();

    std::shared_ptr<Creature> getActiveCreature();
    void next();

private:
    std::queue<std::shared_ptr<Creature>> creatureTurnQueue;
    std::shared_ptr<Creature> activeCreature;
};

#endif // CREATURE_TURN_QUEUE_H
