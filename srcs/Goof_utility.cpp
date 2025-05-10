#include "../includes/Goof.hpp"

int Goof::utility_easy(Game state) // Utility func for easy mode
{
    int mult = (state.getUp() == this->player) ? 1 : 1; // A variable to use the same function if the bot is player 1 or 2 eitherway
    {
        int tmp = state.checker();;
        if (tmp == 1)
            return (mult * 10000);
        if (tmp == 2)
            return (mult * -10000);
    }
    int score = 0;
    score += (mult * state.central_control( this->player )) * 2; // Score for control of the middle  
    score += (mult * state.aligned_piece( this->player )) * 2; // score for aligned piece
    score -= (mult * state.aligned_piece( (this->player == 1 ? 0 : 1))) * 2;

    return (score);
}

int Goof::utility_medium(Game state) // Utility func for medium mode
{
    int mult = (state.getUp() == this->player) ? -1 : 1; // A variable to use the same function if the bot is player 1 or 2 eitherway
    {
        int tmp = state.checker();
        if (tmp == 1)
            return (mult * 10000);
        if (tmp == 2)
            return (mult * -10000);
    }
    int score = utility_easy(state);

    score += (state.piece_value( this->player ) * mult) * 2; // Value of piece on the board
    score -= (state.piece_value( (this->player == 1 ? 0 : 1)) * mult) * 2; 
    score += (state.count_threat( (this->player == 1 ? 0 : 1) ) * mult) * 2; // Count the threat 
    return (score);
}

int Goof::utility_hard(Game state) // Utility func for hard mode
{
    int mult = (state.getUp() == this->player) ? -1 : 1; // A variable to use the same function if the bot is player 1 or 2 eitherway
    {
        int tmp = state.checker();
        if (tmp == 1)
            return (mult * 10000);
        if (tmp == 2)
            return (mult * -10000);
    }
    int score = utility_medium(state);
    score += (state.heat_map( this->player ) * mult); // Call a heatmap to determine wich player has the more powerfull case 
    score += (state.remaining_piece( (this->player)) * mult); // The sumn of every remaining piece in hand
    score -= (state.remaining_piece( (this->player == 1 ? 0 : 1)) * mult); 
    score += (state.detect_fork((this->player)) * mult); // Detect potential fork on the board
    score -= (state.detect_fork( (this->player == 1 ? 0 : 1) ) * mult); // Detect potential fork for the opponent
    return (score);
}