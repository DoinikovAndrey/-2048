#ifndef FIELD_H
#define FIELD_H

#include "../Graph_lib/Graph.h"
#include <iostream>

enum class DIRECT {
    UP = 0,
    LEFT,
    DOWN,
    RIGHT
};

class Tile : public Graph_lib::Rectangle{

};

class Field {
    public:

        void move(DIRECT d);

    private:

};

#endif // FIELD_H
