#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "./enum.hpp"

class Player
{
    private:
        std::vector<int> moov;
    public:
        Player();
        Player(const Player & other);
        Player & operator=(const Player & other);
        ~Player();
        void display_moov();
        bool allowed_moov(int play);
        void play(int play);
        bool moov_left();
        int piece_left();
};
