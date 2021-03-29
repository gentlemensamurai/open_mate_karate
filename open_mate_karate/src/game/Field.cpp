#include "Field.h"

FieldCoord::FieldCoord(unsigned short x, unsigned short y)
    : x { x },
      y { y }
{

}

bool FieldCoord::operator<(const FieldCoord& fieldCoord) const
{
    //if (fieldCoord.x < x && fieldCoord.y < y) return true;
    //if (fieldCoord.x < x && fieldCoord.y == y) return true;
    //if (fieldCoord.x < x && fieldCoord.y > y) return true;

    //if (fieldCoord.x == x && fieldCoord.y < y) return true;
    //if (fieldCoord.x == x && fieldCoord.y == y) return false;
    //if (fieldCoord.x == x && fieldCoord.y > y) return false;

    //if (fieldCoord.x > x && fieldCoord.y < y) return false;
    //if (fieldCoord.x > x && fieldCoord.y == y) return false;
    //if (fieldCoord.x > x && fieldCoord.y > y) return false;

    if (fieldCoord.x < x)
    {
        return true;
    }
    else if (fieldCoord.x == x && fieldCoord.y < y)
    {
        return true;
    }
    else if (fieldCoord.x > x)
    {
        return false;
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