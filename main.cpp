#include <iostream>
#include <sstream>
#include <exception>

//#include "../Graph_lib/Graph.h"
//#include "../Graph_lib/Simple_window.h"

#include "field.h"

int main ()
try {
    srand(time(NULL));

    Field field(Graph_lib::Point{10,10},700,500);
    field.wait_for_button();

    return 0;
} catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 1;
} catch (...) {
    std::cerr << "Oops, something went wrong..." << std::endl;
    return 2;
}
