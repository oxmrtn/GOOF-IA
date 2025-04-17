#pragma once

#include <iostream>
#include <string>
#include <exception>


#define DET_PLAYER(x) \
    ((x) == P1_SMALL || (x) == P1_MEDIUM || (x) == P1_BIG ? 1 : \
    ((x) == P2_SMALL || (x) == P2_MEDIUM || (x) == P2_BIG ? 2 : 0))

enum moov
{
    EMPTY,
    P1_SMALL,
    P1_MEDIUM,
    P1_BIG,
    P2_SMALL,
    P2_MEDIUM,
    P2_BIG
};

class Case;

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
        void execute_moov(int i, int j, int player);
        bool is_allowed_moov(int i, int j, int player);
};

#include "./Case.hpp"