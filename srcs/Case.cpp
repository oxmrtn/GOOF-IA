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

int Case::getCurrent() // Return the current states of the case
{
    return (tab[latest]);
}

void Case::setCase(int value) // Set a new value for the case.
{
    if (latest >= 3)
        return ;
    latest++;
    this->tab[latest] = value;
}

void Case::undo_move() // Withdraw a value from a case
{
    if (latest <= 0)
        return ;
    this->tab[latest] = 0;
    this->latest--;
}

bool Case::space_on_case() // True if the case is empty
{
    return (this->latest >= 3 ? false : true);
}

bool Case::is_allowed( int value ) // True if a moov is allowed, false otherwise
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
