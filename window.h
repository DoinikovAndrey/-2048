#ifndef WINDOW_H
#define WINDOW_H

#include "Graph_lib/Simple_window.h"

struct Help_window : Simple_window {

    Help_window (Graph_lib::Point xy, int w, int h, const std::string& title)
        : Simple_window{ xy, w, h, title },
          hide_button{ Graph_lib::Point{x_max()-70, 20}, 70, 20, "hide", cb_hide }
    {
        attach (hide_button);
    }

    Graph_lib::Button hide_button;


private:

    static void cb_hide (Graph_lib::Address, Graph_lib::Address but) {
        Graph_lib::Window* win = Graph_lib::reference_to<Graph_lib::Button>(but).get_window();
        Graph_lib::reference_to<Help_window>(win).myhide();
    }

    void myhide () { hide(); }

};




struct ExWindow : Simple_window {

    ExWindow (Graph_lib::Point xy, int w, int h, const std::string& title)
        : Simple_window{ xy, w, h, title }, 
        exit_button{ Graph_lib::Point{x_max()-70, 20}, 70, 20, "Exit", cb_exit },
        help_button{ Graph_lib::Point{x_max()-70, 40}, 70, 20, "Help", cb_help }, help_msg{"переопределить текст"}
    {
        attach (exit_button);
        attach (help_button);

    }

    Graph_lib::Button exit_button;
    Graph_lib::Button help_button;

    std::string help_msg;

    private:

    static void cb_exit (Graph_lib::Address, Graph_lib::Address but) {
        Graph_lib::Window* win = Graph_lib::reference_to<Graph_lib::Button>(but).get_window();
        Graph_lib::reference_to<ExWindow>(win).exit();
    }
    static void cb_help (Graph_lib::Address, Graph_lib::Address but) {
        Graph_lib::Window* win = Graph_lib::reference_to<Graph_lib::Button>(but).get_window();
        Graph_lib::reference_to<ExWindow>(win).help();
    }
    virtual std::string help_message(){
        return "sss";
    }
    void exit ()  { hide(); }
    void help () {
        Help_window winh { Graph_lib::Point(200, 200), 600 , 400 , " Window Help " };
        Graph_lib::Text helpt{Graph_lib::Point(20, 20), help_msg};
        winh.attach(helpt);
        winh.wait_for_button();
    }

};

#endif // WINDOW_H

