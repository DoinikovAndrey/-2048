#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include "Graph_lib/Graph.h"

struct Scoreboard : public Graph_lib::Text{
    public:
        Scoreboard(Graph_lib::Point pos, std::string label);
        void update(int score);

    private:
        std::string label;
};


#endif // SCOREBOARD_H
