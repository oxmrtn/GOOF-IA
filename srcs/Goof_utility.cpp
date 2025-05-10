#include "../includes/Goof.hpp"

int Goof::utility_easy(Game state)
{
    int mult = (state.getUp() == this->player) ? -1 : 1;
    {
        int tmp = state.checker();;
        if (tmp == 1)
            return (mult * 10000);
        if (tmp == 2)
            return (mult * -10000);
    }
    int score = 0;
    score += (mult * state.central_control( this->player )) * 2;
    score += (mult * state.aligned_piece( this->player )) * 2; // player 1
    score -= (mult * state.aligned_piece( (this->player == 1 ? 0 : 1))) * 2; // player 2

    return (score);
}

int Goof::utility_medium(Game state)
{
    int mult = (state.getUp() == this->player) ? -1 : 1;
    {
        int tmp = state.checker();
        if (tmp == 1)
            return (mult * 10000);
        if (tmp == 2)
            return (mult * -10000);
    }
    int score = utility_easy(state);

    score += (state.piece_value( this->player ) * mult) * 2;
    score -= (state.piece_value( (this->player == 1 ? 0 : 1)) * mult) * 2;
    score += (state.count_threat( (this->player == 1 ? 0 : 1) ) * mult) * 2;
    return (score);
}

int Goof::utility_hard(Game state)
{
    int mult = (state.getUp() == this->player) ? -1 : 1;
    {
        int tmp = state.checker();
        if (tmp == 1)
            return (mult * 10000);
        if (tmp == 2)
            return (mult * -10000);
    }
    int score = utility_medium(state);
    score += (state.heat_map( this->player ) * mult);
    score += (state.remaining_piece( (this->player)) * mult);
    score -= (state.remaining_piece( (this->player == 1 ? 0 : 1)) * mult);
    score += (state.detect_fork((this->player)) * mult);
    score -= (state.detect_fork( (this->player == 1 ? 0 : 1) ) * mult);
    return (score);
}