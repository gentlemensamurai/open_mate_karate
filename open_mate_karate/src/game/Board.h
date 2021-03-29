#ifndef BOARD_H
#define BOARD_H

#include <map>
#include <memory>
#include "Creature.h"
#include "Field.h"


class Board
{
public:
    Board(unsigned short boardWidth, unsigned short boardHeight);
    ~Board();

    bool addCreature(FieldCoord fieldCoord, std::shared_ptr<Creature> creature);
    std::shared_ptr<Creature> getCreature(FieldCoord fieldCoord);
    void moveCreature(FieldCoord sourcePoint, FieldCoord targetPoint);

private:
    const unsigned short BOARD_WIDTH;
    const unsigned short BOARD_HEIGHT;
    std::map<FieldCoord, std::shared_ptr<Creature>> creatures;
};

#endif // BOARD_H