#include "../includes/Goof.hpp"

int Goof::utility_easy(Game state, size_t nbr_moov) // Utility func for easy mode
{
    int mult = (state.getUp() == this->player) ? -1 : 1; // A variable to use the same function if the bot is player 1 or 2 eitherway
    {
        int tmp = state.checker();;
        if (tmp == 1)
            return (mult * 10000);
        if (tmp == 2)
            return (mult * -10000);
    }
    int score = 0;
    score += nbr_moov / 2;
    score += (state.central_control( this->player )); // Score for control of the middle  
    score += (state.aligned_piece( this->player )); // score for aligned piece
    score -= (state.aligned_piece(  1 - this->player ));

    return (mult * score);
}

int Goof::utility_medium(Game state, size_t nbr_moov) // Utility func for medium mode
{
    int mult = (state.getUp() == this->player) ? -1 : 1; // A variable to use the same function if the bot is player 1 or 2 eitherway
    {
        int tmp = state.checker();
        if (tmp == 1)
            return (mult * 10000);
        if (tmp == 2)
            return (mult * -10000);
    }
    int score = utility_easy(state, nbr_moov);

    score += (state.piece_value( this->player )) * 5; // Value of piece on the board
    score -= (state.piece_value( 1 - this->player)) * 5; 
    score += (state.count_threat( 1 - this->player )) * 3; // Count the threat 
    return (mult * score);
}

int Goof::utility_hard(Game state, size_t nbr_moov) // Utility func for hard mode
{
    int mult = (state.getUp() == this->player) ? -1 : 1; // A variable to use the same function if the bot is player 1 or 2 eitherway
    {
        int tmp = state.checker();
        if (tmp == 1)
            return (mult * 10000);
        if (tmp == 2)
            return (mult * -10000);
    }

    int score = utility_medium(state, nbr_moov);
    score += (state.heat_map( this->player )); // Call a heatmap to determine wich player has the more powerfull case 
    score += (state.remaining_piece( (this->player))); // The sumn of every remaining piece in hand
    score -= (state.remaining_piece( 1 - this->player)); 
    score += (state.detect_fork((this->player))); // Detect potential fork on the board
    score -= (state.detect_fork( (1 - this->player ))); // Detect potential fork for the opponent
    return (mult * score);
}