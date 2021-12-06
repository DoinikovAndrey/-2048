#ifndef BUTTON_H
#define BUTTON_H


#include <string>
#include "../Graph_lib/GUI.h"
#include "window.h"
#include "field.h"


const std::string& get_str(DIRECT d); 

struct ArrowButton : Graph_lib::Button {
    public:
        ArrowButton(Graph_lib::Point xy, int but_s, Graph_lib::Callback cb, DIRECT d);

        void attach(Graph_lib::Window& win);

        DIRECT get_dir() const { return dir; }
    private:
        DIRECT dir;
        
};


class ButtonControl {
    public:
        ButtonControl(Graph_lib::Window& win, Graph_lib::Point xy, Field* f);
    private:
        Graph_lib::Vector_ref<ArrowButton> but;
        
        Field* field;

        Graph_lib::Point center;
        static constexpr int button_size{40};
        static constexpr int shift{40};

        static void cb_clicked(Graph_lib::Address widget, Graph_lib::Address win){
            Graph_lib::reference_to<ButtonControl>(win).clicked(widget);
        }
        void clicked(Graph_lib::Address widget);
};

#endif // BUTTON_H
