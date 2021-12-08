#include "button.h"

const std::string up = "↑";
const std::string left = "→";
const std::string down = "↓";
const std::string right = "←";


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


ButtonControl::ButtonControl(Graph_lib::Window& win, Graph_lib::Point c, Field* f)
    : center{c}, field{f}{

    but.push_back(new ArrowButton{Graph_lib::Point{c.x, c.y-shift}, button_size, cb_clicked, DIRECT::UP});
    but.push_back(new ArrowButton{Graph_lib::Point{c.x+shift, c.y}, button_size, cb_clicked, DIRECT::LEFT});
    but.push_back(new ArrowButton{Graph_lib::Point{c.x, c.y+shift}, button_size, cb_clicked, DIRECT::DOWN});
    but.push_back(new ArrowButton{Graph_lib::Point{c.x-shift, c.y}, button_size, cb_clicked, DIRECT::RIGHT});
    
    for (int i=0; i<but.size(); ++i)
        win.attach(but[i]);
}

void ButtonControl::clicked(Graph_lib::Address widget){
    Fl_Widget& w = Graph_lib::reference_to<Fl_Widget>(widget);

    ArrowButton& b = Graph_lib::reference_to<ArrowButton>(w.user_data());

    field->move(b.get_dir());

    Fl::redraw();
}
