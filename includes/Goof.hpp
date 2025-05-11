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
        int (Goof::*utilityFunction)(Game state, size_t nb_moov);
    
    public:
        Goof(Game initState, int player, int difficulty);
        ~Goof();
        void updateState(Game state);
        void setActionList();
        void fill_action_list(std::vector<Action> &vector, Game state);
        Action miniMax_decision_ab();
        int min_value_ab(Game state, int depthh, int alpha, int beta);
        int max_value_ab(Game state, int depthh, int alpha, int beta);
        Game result(Action a, const Game & state);
        int utility_easy(Game state, size_t nbr_moov);
        int utility_medium(Game state, size_t nbr_moov);
        int utility_hard(Game state, size_t nbr_moov);
};
