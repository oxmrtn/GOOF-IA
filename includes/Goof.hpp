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
        int depht;
        int player;
    
    public:
        Goof(Game initState);
        ~Goof();
        void updateState(Game state);
        void setActionList();
        Action minMax_decision();
        int min_value(Game state);
        int max_Value(Game state);
        Game result(Action a,Game state);
        int Utility(Game state);
}