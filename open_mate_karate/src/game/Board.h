#ifndef BOARD_H
#define BOARD_H

#include <map>
#include <optional>
#include <iostream>
#include "Creature.h"
#include "Field.h"


class Board
{
public:
    Board();
    ~Board();

    bool addCreature(FieldCoord fieldCoord, std::shared_ptr<Creature> creature);
    std::shared_ptr<Creature> getCreature(FieldCoord fieldCoord);

private:
    std::map<FieldCoord, std::shared_ptr<Creature>> creatures;
};

#endif // BOARD_H