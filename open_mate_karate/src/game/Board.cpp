#include "Board.h"

Board::Board()
    : map()
{

}

Board::~Board()
{

}

void Board::addCreature(std::shared_ptr<Field> field, std::shared_ptr<Creature> creature)
{
    for (auto& i : map)
    {
        if ((i.first->getX() == field->getX()) && (i.first->getY() == field->getY()))
        {
            return;
        }
    }

    map.insert(std::pair<std::shared_ptr<Field>, std::shared_ptr<Creature>>(field, creature));
}

std::shared_ptr<Creature> Board::getCreature(unsigned int x, unsigned int y)
{
    for (auto& i : map)
    {
        if ((i.first->getX() == x) && (i.first->getY() == y) && (i.second != nullptr))
        {
            return i.second;
        }
    }

    return nullptr;
}