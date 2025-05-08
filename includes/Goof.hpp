#pragma once

#include <iostream>
#include <string>
#include <exception>
#include <vector>
#include <array>
#include <unistd.h>


#include "./Game.hpp"
#include "./Action.hpp"
#include "./enum.hpp"

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
        Action miniMax_decision_ab();
        int min_value_ab(Game state, int depthh, int alpha, int beta);
        int min_value(Game state, int depthh);
        int max_value_ab(Game state, int depthh, int alpha, int beta);
        int max_value(Game state, int depthh);
        Game result(Action a, const Game & state);
        int utility(Game state);
        int utility2(Game state);
};
