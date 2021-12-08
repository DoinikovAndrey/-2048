#ifndef FIELD_H
#define FIELD_H

#include "../Graph_lib/Graph.h"
#include "window.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>


enum class DIRECT {
    UP = 0,
    LEFT,
    DOWN,
    RIGHT
};

class Tile : public Graph_lib::Rectangle{
    public:
        Tile(int v, double len, Graph_lib::Point pos);

        int get_value() {return value;}
        void mult_by_2() { set_value(value*2); }
        void set_value(int new_v);

        Graph_lib::Point get_position() { return position; }
        void set_position(Graph_lib::Point new_pos);

        void draw_lines() const override;

        void move(int dx, int dy) override;
\
    private:
        int value;
        double length;
        Graph_lib::Point position;

        Graph_lib::Text value_label;
        Graph_lib::Color tile_col= Graph_lib::Color::white;
};

class Field : public ExWindow{
    public:
        Field(Graph_lib::Point pos, int win_w, int win_h, int w = 4, int h = 4);

        void move(DIRECT d);
        int get_score();
        void add_random_tile();
        void draw_lines() const;
        void update();
    private:
        std::vector< Graph_lib::Vector_ref<Tile> > field;
        double tile_length;
        int number_w; //number of cells by weidth
        int number_h; //number of cells by height
        Graph_lib::Point position{50, 50};

};

#endif // FIELD_H
