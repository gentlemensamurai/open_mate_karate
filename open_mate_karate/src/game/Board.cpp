#include "Board.h"

Board::Board()
    : creatures()
{

}

Board::~Board()
{

}

bool Board::addCreature(FieldCoord fieldCoord, std::shared_ptr<Creature> creature)
{
    auto result = creatures.insert(std::pair<FieldCoord, std::shared_ptr<Creature>>(fieldCoord, creature));
    return result.second;
}

std::shared_ptr<Creature> Board::getCreature(FieldCoord fieldCoord)
{
    auto it = creatures.find(fieldCoord);

    if ((it != creatures.end()) && (it->second != nullptr))
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}