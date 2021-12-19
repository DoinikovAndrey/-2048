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
    if (value && value < 128)
        set_fill_color(fl_rgb_color(255 - (value * 2), 255, 255));
    else if (value >= 128)
                set_fill_color(fl_rgb_color(255, 0, 255));
    else
        set_fill_color(fl_rgb_color(200, 200, 200));
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
    but_control{this, Graph_lib::Point{600,300}, cb_clicked},
    scb{Graph_lib::Point{490, 40}, ("Score: " + std::to_string(0))},
    is_over{Graph_lib::Point{490, 100}, ""}
{
    field.resize(number_h);
    for (int i=0;i<h;i++)
        for (int j=0;j<w;j++){
            field[i].push_back(new Tile(0, tile_length, Graph_lib::Point{position.x+tile_length*j,position.y+tile_length*i}));
            attach(field[i][j]);
        }
    
    for (int i=0; i<3; i++)
        add_random_tile();
    attach(scb);
    attach(is_over);
    update();
}

void Field::add_random_tile(){
    int randv = 2;
    if (rand() % 7 == 1) 
        randv = 4;

    int randx, randy;
    do {
        randx = rand() % number_w;
        randy = rand() % number_h;
    } while ( field[randy][randx].get_value() );

    field[randy][randx].set_value(randv);
}

void Field::move(DIRECT d){
    is_moved = false;
    
    if (d == DIRECT::UP)
        move_up(), stick_up(), move_up();
    else if (d == DIRECT::LEFT)
        move_left(), stick_left(), move_left();
    else if (d == DIRECT::DOWN)
        move_down(), stick_down(), move_down();
    else if (d == DIRECT::RIGHT)
        move_right(), stick_right(), move_right();

    if (is_moved){
        add_random_tile();
        scb.update(score);
        update();
    }
}

void Field::stick_up(){
    for (int x = 0; x<number_w; ++x){
        for (int y = 0; y<number_h-1; ++y){
            if (field[y][x].get_value() == field[y+1][x].get_value()){
                field[y][x].set_value(0);
                field[y+1][x].mult_by_2();
                score += field[y+1][x].get_value();
                is_moved = true;

                ++y;
            }
        }
    }
}

void Field::stick_left(){
    for (int y = 0; y<number_h; ++y){
        for (int x = number_w-1; x>0; --x){
            if (field[y][x].get_value() == field[y][x-1].get_value()){
                field[y][x].set_value(0);
                field[y][x-1].mult_by_2();
                score += field[y][x-1].get_value();
                is_moved = true;
                --x;
            }
        }
    }
}

void Field::stick_down(){
    for (int x = 0; x<number_w; ++x){
        for (int y = number_h-1; y>0; --y){
            if (field[y][x].get_value() == field[y-1][x].get_value()){
                field[y][x].set_value(0);
                field[y-1][x].mult_by_2();
                score += field[y-1][x].get_value();
                is_moved = true;
                --y;
            }
        }
    }
}

void Field::stick_right(){
    for (int y = 0; y<number_h; ++y){
        for (int x = 0; x<number_w-1; ++x){
            if (field[y][x].get_value() == field[y][x+1].get_value()){
                field[y][x].set_value(0);
                field[y][x+1].mult_by_2();
                score += field[y][x+1].get_value();
                is_moved = true;
                ++x;
            }
        }
    }
}

void Field::move_up(){
    for (int x = 0; x<number_w; ++x){
        int last = 0;
        for (int y = 0; y<number_h; ++y){
            if (field[y][x].get_value()){
                if (last != y) {
                    field[last][x].set_value( field[y][x].get_value() );
                    field[y][x].set_value(0);
                    is_moved = true;
                }
                last++;
            }
        }
    }    
    
}

void Field::move_left(){
    for (int y = 0; y<number_h; ++y){
        int last = 0;
        for (int x = 0; x<number_w; ++x){
            if (field[y][x].get_value()){
                if (last != x) {
                    field[y][last].set_value( field[y][x].get_value() );
                    field[y][x].set_value(0);
                    is_moved = true;
                }
                last++;
            }
        }
    }    
}

void Field::move_down(){
    for (int x = 0; x<number_w; ++x){
        int last = number_h-1;
        for (int y = number_h-1; y>=0; --y){
            if (field[y][x].get_value()){
                if (last != y) {
                    field[last][x].set_value( field[y][x].get_value() );
                    field[y][x].set_value(0);
                    is_moved = true;
                }
                last--;
            }
        }
    }    
    
}

void Field::move_right(){
    for (int y = 0; y<number_h; ++y){
        int last = number_w-1;
        for (int x = number_w-1; x>=0; --x){
            if (field[y][x].get_value()){
                if (last != x) {
                    field[y][last].set_value( field[y][x].get_value() );
                    field[y][x].set_value(0);
                    is_moved = true;
                }
                last--;
            }
        }
    }    
}

bool Field::is_end(){ // Проверяет наличие одинаковых клеток в поле
    for (int i = 0; i < number_h; ++i) {
        for (int j = 0; j < number_w - 1; ++j) {
            if (field[i][j].get_value() == field[i][j + 1].get_value()
                    || field[i][j].get_value() == 0 || field[i][j + 1].get_value() == 0)
                return false;
        }
    }

    for (int i = 0; i < number_h - 1; ++i) {
        for (int j = 0; j < number_w; ++j) {
            if (field[i][j].get_value() == field[i + 1][j].get_value()
                    || field[i][j].get_value() == 0 || field[i + 1][j].get_value() == 0)
                return false;
        }
    }
    return true;
}

void Field::update(){
    game_over = is_end();
    if (game_over)
        is_over.set_label("Game Over");
    Fl::redraw();
}
