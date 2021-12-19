#include "scoreboard.h"

Scoreboard::Scoreboard(Graph_lib::Point pos, std::string label)
    : Graph_lib::Text {pos, label}{
}

void Scoreboard::update(int score){
    label = "Score: " + std::to_string(score);
    set_label(label);
}
