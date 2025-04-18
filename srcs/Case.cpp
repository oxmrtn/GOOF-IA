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
        return ;
    this->tab[latest] = 0;
    this->latest--;
}

bool Case::space_on_case()
{
    return (this->latest >= 3 ? false : true);
}

bool Case::is_allowed( int value )
{
    if (!space_on_case())
        return (false);
    if (latest == 0)
        return (true);
    else if (value == P1_MEDIUM || value == P2_MEDIUM)
    {
        if ((this->getCurrent() == P1_SMALL || this->getCurrent() == P2_SMALL))
            return (true);
    }
    else if (value == P1_BIG || value == P2_BIG)
    {
        if ((this->getCurrent() == P1_MEDIUM || this->getCurrent() == P2_MEDIUM)
            || (this->getCurrent() == P1_SMALL || this->getCurrent() == P2_SMALL))
            return (true);
    }
    return (false);
}
