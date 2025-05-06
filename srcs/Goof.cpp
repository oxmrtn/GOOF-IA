#include "../includes/Goof.hpp"

Goof::Goof(Game initstate, int player)
{
    this->currentState = initState;
    this->player = player;
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

int Goof::utility(Game state)
{
    int turn = state.getUp;
    int score = 0;
    int tmp[2];
    int center;
    
    if(this.player == 1)
    {
        if(state.checker()==1)
        {
            return 1000;
        }

        if(state.checker()==2)
        {
            return -1000;
        }

        center = state.check_center();

        if(center == 1)
        {
            score+=50;

        }else if (center == 2)
        {
            score-=50;
        }
        
        tmp = state.checker_two_cases();

        if(state.getUp == 0)
        {
            score+=100*tmp[0];
            score-= 50*tmp[1];
        }else
        {
            score-=100*tmp[1];
            score+= 50*tmp[0];
        }
    }

    if(this.player == 2)
    {
        if(state.check_line==1)
        {
            return -1000;
        }

        if(state.check_line==2)
        {
            return 1000;
        }

        center = state.check_center();

        if(center == 1)
        {
            score-=50;

        }else if (center == 2)
        {
            score+=50
        }
        
        tmp = state.checker_two_cases()

        if(state.getUp == 0)
        {
            score-=100*tmp[0];
            score+= 50*tmp[1];
        }else
        {
            score+=100*tmp[1];
            score-= 50*tmp[0];
        }
    }

    return score;
}