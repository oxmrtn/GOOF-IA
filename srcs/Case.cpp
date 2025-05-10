#include "../includes/Case.hpp"

Case::Case()
{
    for (int i = 0; i < 5; i++)
    {
        tab[i] = 0;
    }
    latest = 0;
}

Case::Case(const Case & other)
{
    for (int i = 0; i < 5; i++)
    {
        this->tab[i] = other.tab[i];
    }
    this->latest = other.latest;
}

Case& Case::operator=(const Case& other)
{
    if (this != &other)
    {
        for (int i = 0; i < 5; i++)
        {
            this->tab[i] = other.tab[i];
        }
        this->latest = other.latest;
    }
    return *this;
}


Case::~Case()
{}

int Case::getCurrent() // Return the current states of the case
{
    if (latest < 0 || 5 < latest)
        return (0);
    return (tab[latest]);
}

void Case::setCase(int value) // Set a new value for the case.
{
    if (latest > 4)
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

bool Case::space_on_case() // True if there is space on the case
{
    return (this->latest >= 4 ? false : true);
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
    else if ( value == P2_BBIG || value == P1_BBIG)
    {
        if ((!(this->getCurrent() == P1_BBIG) && !(this->getCurrent() == P2_BBIG)))
            return (true);
    }
    return (false);
}
