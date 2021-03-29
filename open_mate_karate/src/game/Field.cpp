#include "Field.h"

FieldCoord::FieldCoord(unsigned short x, unsigned short y)
    : x(x),
      y(y)
{

}

bool FieldCoord::operator<(const FieldCoord& fieldCoord) const
{
    if (x < fieldCoord.x)
    {
        return true;
    }
    else if (x == fieldCoord.x)
    {
        if (y < fieldCoord.y)
        {
            return true;
        }
        else if (y == fieldCoord.y)
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

Field::Field()
{

}

Field::~Field()
{

}