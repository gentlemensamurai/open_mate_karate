#ifndef FIELD_H
#define FIELD_H

class Field
{
public:
    Field(unsigned int x, unsigned int y);
    ~Field();

    inline unsigned int getX() { return x; }
    inline unsigned int getY() { return y; }

    bool operator<(const Field& field) const;

private:
    unsigned int x;
    unsigned int y;
};

#endif // FIELD_H