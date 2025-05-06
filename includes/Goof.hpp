#pragma once

#include <iostream>
#include <string>
#include <exception>
#include <vector>

#include "./Game.hpp"
#include "./Action.hpp"

class Goof
{
    private:
        Game currentState;
        std::vector<Action> actionList;
        int depth;
        int player;
    
    public:
        Goof(Game initState, int player);
        ~Goof();
        void updateState(Game state);
        void setActionList();
        Action minMax_decision();
        int min_value(Game state);
        int max_Value(Game state);
        Game & result(Action a, const Game & state);
        int utility(Game state);
}
