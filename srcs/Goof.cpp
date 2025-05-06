#include "../includes/Goof.hpp"

Goof::Goof(Game initstate)
{
    this->currentState = initState;
}

Goof::~Goof()
{}

void Goof::updateState(Game state)
{
    this->currentState = state;
}

void setActionList()
{

}

