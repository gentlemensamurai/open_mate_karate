#ifndef BOARD_H
#define BOARD_H

#include <map>
#include <memory>
#include <optional>
#include "Creature.h"
#include "Field.h"

class Board
{
public:
    const unsigned short BOARD_WIDTH;
    const unsigned short BOARD_HEIGHT;

    Board(unsigned short boardWidth, unsigned short boardHeight);
    ~Board();

    bool addCreature(FieldCoord fieldCoord, std::shared_ptr<Creature> creature);
    std::shared_ptr<Creature> getCreature(FieldCoord fieldCoord);
    std::optional<FieldCoord> getFieldCoord(std::shared_ptr<Creature> creature);
    void moveCreature(FieldCoord sourcePoint, FieldCoord targetPoint);

private:
    std::map<FieldCoord, std::shared_ptr<Creature>> creatures;
};

#endif // BOARD_H
