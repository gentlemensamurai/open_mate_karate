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

    void addCreature(std::shared_ptr<Field> field, std::shared_ptr<Creature> creature);
    std::shared_ptr<Creature> getCreature(unsigned int x, unsigned int y);

private:
    std::map<std::shared_ptr<Field>, std::shared_ptr<Creature>> map;
};

#endif // BOARD_H