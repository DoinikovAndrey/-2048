#ifndef FIELD_H
#define FIELD_H

#include "../Graph_lib/Graph.h"
#include "window.h"
#include "button.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>


class Tile : public Graph_lib::Rectangle{
    public:
        Tile(int v, int len, Graph_lib::Point pos);

        int get_value() { return value; }
        void set_value(int new_v);
        void mult_by_2() { set_value(value*2); }

        Graph_lib::Point get_position() { return position; }
        void set_position(Graph_lib::Point new_pos);
        void move(int dx, int dy) override;

        void draw_lines() const override;

    private:
        int value;
        int length;
        Graph_lib::Point position;

        Graph_lib::Text value_label;
        Graph_lib::Color tile_col = Graph_lib::Color::white;
};

class Field : public ExWindow{
    public:
        Field(Graph_lib::Point pos, int win_w, int win_h, int w = 4, int h = 4);

        ButtonControl& get_butcont() { return but_control; }

        void move(DIRECT d);

        int get_score();

    private:
        void update();

        void add_random_tile();

        void stick_up();
        void stick_left();
        void stick_down();
        void stick_right();

        void move_up();
        void move_left();
        void move_down();
        void move_right();

        static void cb_clicked(Graph_lib::Address, Graph_lib::Address but){
            Graph_lib::Window* win = Graph_lib::reference_to<Graph_lib::Button>(but).get_window();
            Graph_lib::reference_to<Field>(win).get_butcont().clicked(Graph_lib::reference_to<ArrowButton>(but));
        }

        std::vector< Graph_lib::Vector_ref<Tile> > field;

        ButtonControl but_control;

        int tile_length;
        int number_w; //number of cells by weidth
        int number_h; //number of cells by height

        Graph_lib::Point position{50, 50};

        bool is_moved{false};
};

#endif // FIELD_H
