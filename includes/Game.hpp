#pragma once

#include <iostream>
#include <string>
#include <exception>
#include <array>

#include "./Case.hpp"
#include "./enum.hpp"
#include "./Player.hpp"

#define DET_PLAYER(x) \
    ((x) == P1_SMALL || (x) == P1_MEDIUM || (x) == P1_BIG ? 1 : \
    ((x) == P2_SMALL || (x) == P2_MEDIUM || (x) == P2_BIG ? 2 : 0))


#define BLACK       "\033[30m"
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"
#define MAGENTA     "\033[35m"
#define CYAN        "\033[36m"
#define WHITE       "\033[37m"
#define DEFAULT     "\033[0m"

class Goof;

class Game
{
    private:
        Case map[3][3];
        Player player[2];
        int up;

    public:
        Game();
        Game(const Game & other);
        ~Game();
        void launch_game_player_versus_player();
        void display_game();
        int checker();
        int check_line(int a, int b, int c);
        bool execute_moov(int i, int j, int value);
        void turn(int idx);
        Player getPlayer(int idx);
        int getUp();
        std::array<bool, 2> check_two_cases(int a, int b, int c);
        std::array<int, 2> checker_two_cases();
        int check_center();
        friend class Goof;
};
