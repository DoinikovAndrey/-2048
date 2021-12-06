#include "button.h"

void ArrowButton::attach(Graph_lib::Window& win){
    Button::attach(win);
}



ButtonControl::ButtonControl(Graph_lib::Window& win, Graph_lib::Point c)
    : center{c}{

    but.push_back(new ArrowButton{Graph_lib::Point{c.x, c.y-shift}, button_size, cb_clicked});
    but.push_back(new ArrowButton{Graph_lib::Point{c.x+shift, c.y}, button_size, cb_clicked});
    but.push_back(new ArrowButton{Graph_lib::Point{c.x, c.y+shift}, button_size, cb_clicked});
    but.push_back(new ArrowButton{Graph_lib::Point{c.x-shift, c.y}, button_size, cb_clicked});
    
    for (int i=0; i<but.size(); ++i)
        win.attach(but[i]);
}

void ButtonControl::clicked(Graph_lib::Address widget){
    Fl::redraw();
}
