#include "../includes/Goof.hpp"

Goof::Goof(Game initState) : actionList(128)
{
    this->currentState = initState;
}

void Goof::updateState(Game state)
{
    this->currentState = state;
}

void Goof::setActionList()
{
    Player a_p = this->currentState.getPlayer(this->player);
    int available_piece[4] = {0, 0, 0};

    for (int i = 0; i < 4; i++)
    {
        if (a_p.allowed_moov(i))
            available_piece[i] = i;
    }
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            Case tmp = currentState.map[i][j];
            int tmp2 = tmp.getCurrent();
            if (tmp2 == 0 || (this->player == 0 && tmp2 > 3) || (this->player == 1 && tmp2 < 4))
                continue;
            if ( tmp2 > 4)
                tmp2 -= 3;
            for (int k = 0; k < 3; k++)
            {
                if (available_piece[k] != 0 && available_piece[k] > tmp2)
                    this->actionList.push_back(Action(i, j, available_piece[k]));
            }
            for (int p = 0; p < 3; p++)
            {
                for (int m = 0; m < 3; m++)
                {
                    if (tmp2 > currentState.map[p][m].getCurrent())
                    {
                        this->actionList.push_back(Action(i, j, p, m, tmp2));
                    }
                }
            }
        }
    }
}
