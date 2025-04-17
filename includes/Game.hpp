#pragma once

#include <iostream>
#include <string>
#include <exception>

#include "./Case.hpp"
#include "./enum.hpp"

#define DET_PLAYER(x) \
    ((x) == P1_SMALL || (x) == P1_MEDIUM || (x) == P1_BIG ? 1 : \
    ((x) == P2_SMALL || (x) == P2_MEDIUM || (x) == P2_BIG ? 2 : 0))

class Game
{
    private:
        Case map[3][3];

    public:
        Game();
        ~Game();
        void launch_game();
        void display_game();
        bool checker();
        bool check_line(int a, int b, int c);
        bool execute_moov(int i, int j, int value);
};
