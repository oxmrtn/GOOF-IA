#pragma once

#include <iostream>
#include <string>
#include <exception>
#include <array>
#include <random>
#include <ctime>

#include "./Case.hpp"
#include "./Action.hpp"
#include "./enum.hpp"
#include "./Player.hpp"

#define DET_PLAYER(x) \
    ((x) == P1_SMALL || (x) == P1_MEDIUM || (x) == P1_BIG || (x) == P1_BBIG ? 1 : \
    ((x) == P2_SMALL || (x) == P2_MEDIUM || (x) == P2_BIG || (x) == P2_BBIG ? 2 : 0))


#define BLACK       "\033[30m"
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"
#define MAGENTA     "\033[35m"
#define CYAN        "\033[36m"
#define WHITE       "\033[37m"
#define DEFAULT     "\033[0m"

#define SIZE 4
#define NBR_PIECE 4

class Goof;

class Game
{
    private:
        Case map[SIZE][SIZE];
        Player player[2];
        int up;

    public:
        Game();
        Game(const Game & other);
        Game & operator=(const Game & other);
        ~Game();
        void launch_game_player_versus_player();
        int launch_game_player_versus_ia(int bot_player, int difficulty);
        int launch_game_ia_versus_ia(int p1_difficulty, int p2_difficulty);
        void display_game();
        void display_raw();
        int checker();
        int check_line(int a, int b, int c, int d);
        bool execute_moov(int i, int j, int value);
        void turn(int idx);
        Player & getPlayer(int idx);
        void PlayerPlay(int idx, int play);
        int getUp();
        void setUp(int value);
        int central_control(int player);
        int aligned_piece(int player);
        int piece_value(int player);
        int count_threat(int player);
        int heat_map(int player);
        int remaining_piece(int player);
        int detect_fork(int pturn);
        friend class Goof;
};

#include "./Goof.hpp"