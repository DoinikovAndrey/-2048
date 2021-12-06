#include <iostream>
#include <sstream>
#include <exception>

//#include "../Graph_lib/Graph.h"
//#include "../Graph_lib/Simple_window.h"

#include "window.h"
#include "button.h"

int main ()
try {
    ExWindow win(Graph_lib::Point{2,0}, 500, 500, "ok");
    ButtonControl but(win, Graph_lib::Point{100, 100});
    win.wait_for_button();
    return 0;
} catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 1;
} catch (...) {
    std::cerr <<"Oops, something went wrong..."<< std::endl;
    return 2;
}
