#include "Board.h"

Board::Board(unsigned short boardWidth, unsigned short boardHeight)
    : BOARD_WIDTH { boardWidth },
      BOARD_HEIGHT { boardHeight },
      creatures { }

{

}

Board::~Board()
{

}

bool Board::addCreature(FieldCoord fieldCoord, std::shared_ptr<Creature> creature)
{
    if (fieldCoord.x < BOARD_WIDTH && fieldCoord.y < BOARD_HEIGHT)
    {
        auto result = creatures.insert(std::pair<FieldCoord, std::shared_ptr<Creature>>(fieldCoord, creature));
        return result.second;
    }
    else
    {
        return false;
    }
}

std::shared_ptr<Creature> Board::getCreature(FieldCoord fieldCoord)
{
    if (fieldCoord.x < BOARD_WIDTH && fieldCoord.y < BOARD_HEIGHT)
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
    else
    {
        return nullptr;
    }
}

std::optional<FieldCoord> Board::getFieldCoord(std::shared_ptr<Creature> creature)
{
    std::optional<FieldCoord> result { std::nullopt };

    if (creature != nullptr)
    {
        for (auto& i : creatures)
        {
            if (i.second.get() == creature.get())
            {
                result = i.first;
                break;
            }
        }
    }

    return result;
}

void Board::moveCreature(FieldCoord sourcePoint, FieldCoord targetPoint)
{
    if (sourcePoint.x < BOARD_WIDTH && sourcePoint.y < BOARD_HEIGHT &&
        targetPoint.x < BOARD_WIDTH && targetPoint.y < BOARD_HEIGHT)
    {
        std::shared_ptr<Creature> creature { getCreature(sourcePoint) };

        if (creature != nullptr)
        {
            creatures.erase(sourcePoint);
            addCreature(targetPoint, creature);
        }
    }
}