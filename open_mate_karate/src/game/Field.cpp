#include "Field.h"

Field::Field(unsigned int x, unsigned int y)
    : x(x),
      y(y)
{

}

Field::~Field()
{

}

bool Field::operator<(const Field& field) const
{
    return (x < field.x) && (y < field.y);
}