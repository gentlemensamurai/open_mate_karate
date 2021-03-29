#include "CreatureTurnQueue.h"

CreatureTurnQueue::CreatureTurnQueue
(
    const std::vector<std::shared_ptr<Creature>>& leftSideCreatures,
    const std::vector<std::shared_ptr<Creature>>& rightSideCreatures
)
    : creatureTurnQueue { },
      activeCreature { nullptr }
{
    for (auto i : leftSideCreatures)
    {
        creatureTurnQueue.push(i);
    }

    for (auto i : rightSideCreatures)
    {
        creatureTurnQueue.push(i);
    }

    next();
}

CreatureTurnQueue::~CreatureTurnQueue()
{

}

std::shared_ptr<Creature> CreatureTurnQueue::getActiveCreature()
{
    return activeCreature;
}

void CreatureTurnQueue::next()
{
    if (!creatureTurnQueue.empty())
    {
        activeCreature = creatureTurnQueue.front();
        creatureTurnQueue.pop();
        creatureTurnQueue.push(activeCreature);
    }
}
