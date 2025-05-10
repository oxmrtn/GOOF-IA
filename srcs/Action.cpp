#include "../includes/Action.hpp"

Action::Action()
{
    this->type = "empty";
    this->moovs = {};
}

Action::Action(int x1, int y1, int piece) // Constructor to place a stored piece
{
    this->type = "stored";
    this->moovs = {x1, y1, piece};
}

Action::Action(int x1, int y1, int x2, int y2, int piece) // Constructor to moove a piece
{
    this->type = "placed";
    this->moovs = {x1, y1, x2, y2, piece};
}

Action::Action(const Action& other)
{
    this->type = other.type;
    this->moovs = other.moovs;
}

Action& Action::operator=(const Action& other)
{
    if (this != &other)
    {
        this->type = other.type;
        this->moovs = other.moovs;
    }
    return *this;
}


Action::~Action(){}

int Action::getMoovI(int idx) // Return the value at index idx.
{
    if (idx < 0 || static_cast<unsigned long>( idx ) >= moovs.size())
        return (-1);
    return (moovs[idx]);
}

std::string Action::getType() {return (type);} // Return the label of the moov