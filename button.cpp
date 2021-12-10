#include "field.h"

const std::string up = "↑";
const std::string left = "←";
const std::string down = "↓";
const std::string right = "→";


const std::string& get_str(DIRECT d){
    if (d == DIRECT::UP)
        return up;
    if (d == DIRECT::LEFT)
        return left;
    if (d == DIRECT::DOWN)
        return down;
    if (d == DIRECT::RIGHT)
        return right;
} 


ArrowButton::ArrowButton(Graph_lib::Point xy, int but_s, Graph_lib::Callback cb, DIRECT d)
    : Button{xy, but_s, but_s, get_str(d), cb}, dir{d} {    
}

void ArrowButton::attach(Graph_lib::Window& win){
    Button::attach(win);
}


ButtonControl::ButtonControl(Field* f, Graph_lib::Point c, Graph_lib::Callback cb)
    : center{c}, field{f}{

    but.push_back(new ArrowButton{Graph_lib::Point{c.x, c.y-shift}, button_size, cb, DIRECT::UP});
    but.push_back(new ArrowButton{Graph_lib::Point{c.x-shift, c.y}, button_size, cb, DIRECT::LEFT});
    but.push_back(new ArrowButton{Graph_lib::Point{c.x, c.y+shift}, button_size, cb, DIRECT::DOWN});
    but.push_back(new ArrowButton{Graph_lib::Point{c.x+shift, c.y}, button_size, cb, DIRECT::RIGHT});
    
    for (int i=0; i<but.size(); ++i)
        field->attach(but[i]);
}

void ButtonControl::clicked(const ArrowButton& but){
    field->move( but.get_dir() );

    Fl::redraw();
}
