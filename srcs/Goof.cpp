#include "../includes/Goof.hpp"

Goof::Goof(Game initstate)
{
    this->currentState = initState;
}

void Goof::updateState(Game state)
{
    this->currentState = state;
}

