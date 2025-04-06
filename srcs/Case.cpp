#include "../includes/Case.hpp"

Case::Case()
{
    for (int i = 0; i < 3; i++)
    {
        tab[i] = 0;
    }
    latest = 0;
}

Case::~Case()
{}

int Case::getCurrent()
{
    return (tab[latest]);
}

void Case::setCase(int value)
{
    if (latest >= 2)
        return ;
    this->tab[latest + 1] = value;
    latest++;
}

void Case::undo_move()
{
    if (latest <= 0)
    {
        return ;
    }
    this->tab[latest] = 0;
    this->latest--;
}
