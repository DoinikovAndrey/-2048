#ifndef WINDOW_H
#define WINDOW_H

#include "../Graph_lib/Simple_window.h"

struct ExWindow : Simple_window {

    ExWindow (Graph_lib::Point xy, int w, int h, const std::string& title)
        : Simple_window{ xy, w, h, title }, 
        exit_button{ Graph_lib::Point{x_max()-70, 20}, 70, 20, "Exit", cb_exit }
    {
        attach (exit_button);
    }

    Graph_lib::Button exit_button;

    private:

    static void cb_exit (Graph_lib::Address, Graph_lib::Address addr) {
        Graph_lib::reference_to<ExWindow>(addr).exit();
    }
    void exit ()  { hide(); }
};


#endif // WINDOW_H
