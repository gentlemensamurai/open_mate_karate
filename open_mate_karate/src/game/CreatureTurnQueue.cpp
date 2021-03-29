#include "CreatureTurnQueue.h"

CreatureTurnQueue::CreatureTurnQueue(const std::vector<std::shared_ptr<Creature>>& creatures)
    : creatureTurnQueue { },
      activeCreature { nullptr }
{
    for (auto i : creatures)
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
