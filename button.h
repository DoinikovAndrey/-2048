#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include "Graph_lib/GUI.h"
#include "window.h"


enum class DIRECT {
    UP = 0,
    LEFT,
    DOWN,
    RIGHT,
    NONE
};


const std::string& get_str(DIRECT d); 

struct ArrowButton : Graph_lib::Button {
    public:
        ArrowButton(Graph_lib::Point xy, int but_s, Graph_lib::Callback cb, DIRECT d);

        void attach(Graph_lib::Window& win);

        DIRECT get_dir() const { return dir; }

    private:
        DIRECT dir;
};

class Field;

class ButtonControl {
    public:
        ButtonControl(Field* f, Graph_lib::Point xy, Graph_lib::Callback cb);

        void clicked(const ArrowButton& but);
    private:
        Graph_lib::Vector_ref<ArrowButton> but;
        
        Field* field;

        Graph_lib::Point center;
        static constexpr int button_size{40};
        static constexpr int shift{40};
};

#endif // BUTTON_H
