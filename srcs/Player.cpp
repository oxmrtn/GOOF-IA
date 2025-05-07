#include "../includes/Player.hpp"

Player::Player() : moov{1, 1, 2, 2, 3, 3}
{}

Player::Player(const Player & other)
{
    this->moov = other.moov;
}

Player& Player::operator=(const Player& other)
{
    if (this != &other)
    {
        this->moov = other.moov;
    }
    return *this;
}


Player::~Player()
{}

void Player::display_moov() // Display all the available moov
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

bool Player::allowed_moov(int play) // Check if a player has the right to play a moov
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

void Player::play(int play) // Withdraw a piece from the available piece
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

std::vector<int> Player::getMoov()
{
    return this->moov;
}
