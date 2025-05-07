#pragma once

#include <iostream>
#include <string>
#include <exception>
#include <vector>
#include <array>

#include "./Game.hpp"
#include "./Action.hpp"

class Goof
{
    private:
        Game currentState;
        std::vector<Action> listAction;
        int depth;
        int player;
    
    public:
        Goof(Game initState, int player);
        ~Goof();
        void updateState(Game state);
        void setActionList();
        void fill_action_list(std::vector<Action> &vector, Game state);
        Action miniMax_decision();
        int min_value(Game state, int depthh);
        int max_value(Game state, int depthh);
        Game result(Action a, const Game & state);
        int utility(Game state);
};
