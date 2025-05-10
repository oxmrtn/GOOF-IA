#include "../includes/Player.hpp"

Player::Player() : moov{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4}
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
    size_t size = moov.size();
    for (size_t i = 0; i < size ; i++)
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
    if (play < 0 || play > 4)
        return (false);
    size_t size = moov.size();
    for (size_t i = 0; i < size; i++)
    {
        if (moov[i] == play)
            return (true);
    }
    return (false);
}

void Player::play(int play) // Withdraw a piece from the available piece
{
    size_t size = moov.size();
    for (size_t i = 0; i < size; i++)
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
    size_t size = moov.size();
    for (size_t i = 0; i < size; i++)
    {
        if (moov[i] != 0)
        {
            return (true);
        }
    }
    return (false);
}

int Player::piece_left()
{
    int result = 0;
    size_t size = moov.size();
    for (size_t i = 0; i < size; i++)
    {
        if (moov[i] != 0)
            result++;
    }
    return (result);
}

int Player::score_count()
{
    int score = 0;
    size_t size = moov.size();
    for (size_t i = 0; i < size; i++)
    {
        score += moov[i];
    }
    return (score);
}