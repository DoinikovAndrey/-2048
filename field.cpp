#include "field.h"


Tile::Tile(int v, int len, Graph_lib::Point pos):
    value{v}, length{len}, position{pos}, value_label{Graph_lib::Point(pos.x+len/2,pos.y+len/2),std::to_string(v)},
    Graph_lib::Rectangle{pos, len, len}
{
    set_fill_color(tile_col);
}



void Tile::set_value(int new_v) {
    value = new_v;
    value_label.set_label(std::to_string(value));
}


void Tile::set_position(Graph_lib::Point new_pos) {
    Graph_lib::Rectangle::move(new_pos.x - position.x, new_pos.y - position.y);
    value_label.move(new_pos.x - position.x, new_pos.y - position.y);
    position = new_pos;
}

void Tile::draw_lines() const{
    Graph_lib::Rectangle::draw_lines();
    if (value)
        value_label.draw_lines();
}

void Tile::move(int dx, int dy) {
    Graph_lib::Rectangle::move(dx, dy);
    value_label.move(dx, dy);
    position.x += dx;
    position.y += dy;
}



Field::Field(Graph_lib::Point pos, int win_w, int win_h, int w, int h):
    tile_length{std::min(win_w / w,win_h / h)/1.3}, number_w{w}, number_h{h},
    ExWindow{pos, win_w, win_h, "2048"}, 
    but_control{this, Graph_lib::Point{600,300}, cb_clicked}
{
    field.resize(number_h);
    for (int i=0;i<h;i++)
        for (int j=0;j<w;j++){
            field[i].push_back(new Tile(0, tile_length, Graph_lib::Point{position.x+tile_length*i,position.y+tile_length*j}));
            attach(field[i][j]);
        }
    update();
}

void Field::add_random_tile(){
    int randx, randy;
    int randv = 2;
    if (rand() % 7 == 1) randv = 4;

    do {
        randx = rand() % number_w;
        randy = rand() % number_h;
    } while ( field[randy][randx].get_value() );

    field[randy][randx].set_value(randv);
}

void Field::move(DIRECT d){
    add_random_tile();
    update();
}

void Field::update(){
    //for (int i=0;i<number_h;i++)
    //    for (int j=0;j<number_w;j++){
    //        detach(field[i][j]);
    //        attach(field[i][j]);
    //    }
    Fl::redraw();
}
