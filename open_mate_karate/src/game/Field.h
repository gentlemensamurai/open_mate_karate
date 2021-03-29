#ifndef FIELD_H
#define FIELD_H

struct FieldCoord
{
    unsigned short x;
    unsigned short y;

    FieldCoord(unsigned short x, unsigned short y);
    bool operator<(const FieldCoord& fieldCoord) const;
};

class Field
{
public:
    Field();
    ~Field();

private:

};

#endif // FIELD_H