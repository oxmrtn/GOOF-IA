#include "../includes/Player.hpp"

Player::Player() : moov{1, 1, 2, 2, 3, 3}
{}

Player::~Player()
{}

void Player::display_moov()
{
    for (int i = 0; i < 6; i++)
    {
        if (moov[i] != 0)
        {
            std::cout << moov[i] << " ";
        }
    }
    return ;
}

bool Player::allowed_moov(int play)
{
    if (play < 0 || play > 3)
        return (false);
    for (int i = 0; i < 6; i++)
    {
        if (moov[i] == play)
            return (true);
    }
    return (false);
}

void Player::play(int play)
{
    for (int i = 0; i < 6; i++)
    {
        if (moov[i] == play)
        {
            moov[i] = 0;
            return ;
        }
    }
    return ;
}

bool Player::moov_left()
{
    for (int i = 0; i < 6; i++)
    {
        if (moov[i] != 0)
        {
            return (true);
        }
    }
    return (false);
}
