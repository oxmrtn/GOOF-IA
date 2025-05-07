#include "../includes/Goof.hpp"

Goof::Goof(Game initState, int player) : listAction(128)
{
    this->currentState = initState;
    this->player = player;
    this->depth = 3;
}

Goof::~Goof()
{}

void Goof::updateState(Game state)
{
    this->currentState = state;
}

void Goof::setActionList() // Determine every possible moov for a position
{
    Player a_p = this->currentState.getPlayer(this->player);
    int available_piece[4] = {0, 0, 0, 0};

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
            if ((this->player == 0 && tmp2 > 3) || (this->player == 1 && tmp2 < 4))
                continue;
            if ( tmp2 > 4)
                tmp2 -= 3;
            for (int k = 0; k < 4; k++)
            {
                if (available_piece[k] != 0 && available_piece[k] > tmp2)
                    this->listAction.push_back(Action(i, j, available_piece[k]));
            }
            if (tmp2 == 0)
                continue ;
            for (int p = 0; p < 3; p++)
            {
                for (int m = 0; m < 3; m++)
                {
                    if (tmp2 > currentState.map[p][m].getCurrent())
                    {
                        this->listAction.push_back(Action(i, j, p, m, tmp2));
                    }
                }
            }
        }
    }
}

Game Goof::result(Action a, const Game & state)
{
    Game to_return = state;
    if (a.getType() == "stored")
    {
        to_return.player[player].play(a.getMoovI(2));
        to_return.execute_moov(a.getMoovI(0), a.getMoovI(1), a.getMoovI(2));
    }
    else
    {
        int tmp = to_return.map[a.getMoovI(0)][a.getMoovI(1)].getCurrent();
        to_return.map[a.getMoovI(0)][a.getMoovI(1)].undo_move();
        if (to_return.checker())
            return (to_return);
        to_return.execute_moov(a.getMoovI(2), a.getMoovI(3), tmp);
    }
    return (to_return);
}


int Goof::utility(Game state)
{
    int score = 0;
    std::array<int, 2> tmp;
    int center;
    
    if (this->player == 0)
    {
        if(state.checker()==1)
            return (1000);
        if(state.checker()==2)
            return (-1000);
        center = state.check_center();
        if(center == 1)
            score += 50;
        else if (center == 2)
            score -= 50;
        tmp = state.checker_two_cases();
        if (state.getUp() == 0)
        {
            score += 100 * tmp[0]; 
            score -= 50 * tmp[1];
        }
        else
        {
            score -=100 * tmp[1];
            score += 50 * tmp[0];
        }
    }
    if (this->player == 1)
    {
        if (state.checker() == 1)
            return (-1000);
        if (state.checker() == 2)
            return (1000);
        center = state.check_center();
        if (center == 1)
            score -= 50;
        else if (center == 2)
            score += 50;
        tmp = state.checker_two_cases();
        if (state.getUp() == 0)
        {
            score -= 100*tmp[0];
            score += 50*tmp[1];
        }
        else
        {
            score += 100*tmp[1];
            score -= 50*tmp[0];
        }
    }
    return (score);
}

int Goof::utility2(Game state)
{
    int score = 0;
    std::array<int, 2> tmp;
    int center;
    //array map = state.getMap();
    Player p1 = state.getPlayer(0);
    Player p2 = state.getPlayer(1);
    
    if (this->player == 0)
    {
        if(state.checker()==1)
            return (1000);
        if(state.checker()==2)
            return (-1000);

        center = state.check_center();
        if(center == 1)
            score += 50;
        else if (center == 2)
            score -= 50;
        tmp = state.checker_two_cases();
        if (state.getUp() == 0)
        {
            score += 100 * tmp[0]; 
            score -= 50 * tmp[1];
        }
        else
        {
            score -=100 * tmp[1];
            score += 50 * tmp[0];
        }

        for(int i = 0; i<3; i++)
        {
            for(int j = 0; j<3; j++)
            {
                switch(state.map[i][j].getCurrent())
                {
                    case P1_SMALL: score += 10;
                    break;
                    case P1_MEDIUM: score += 20;
                    break;
                    case P1_BIG: score += 30;
                    break;
                    case P2_SMALL: score -= 10;
                    break;
                    case P2_MEDIUM: score -= 20;
                    break;
                    case P2_BIG: score -= 30;
                    break;
                    default:
                    break;
                }
            }
        }
        
        for(size_t i = 0; i < p1.getMoov().size(); i++)
        {
            score+=5;
        }
        for(size_t i = 0; i < p2.getMoov().size(); i++)
        {
            score-=5;
        }

    }
    if (this->player == 1)
    {
        if (state.checker() == 1)
            return (-1000);
        if (state.checker() == 2)
            return (1000);
        center = state.check_center();
        if (center == 1)
            score -= 50;
        else if (center == 2)
            score += 50;
        tmp = state.checker_two_cases();
        if (state.getUp() == 0)
        {
            score -= 100*tmp[0];
            score += 50*tmp[1];
        }
        else
        {
            score += 100*tmp[1];
            score -= 50*tmp[0];
        }

        for(int i = 0; i<3; i++)
        {
            for(int j = 0; j<3; j++)
            {
                switch(state.map[i][j].getCurrent())
                {
                    case P1_SMALL: score -= 10;
                    break;
                    case P1_MEDIUM: score -= 20;
                    break;
                    case P1_BIG: score -= 30;
                    break;
                    case P2_SMALL: score += 10;
                    break;
                    case P2_MEDIUM: score += 20;
                    break;
                    case P2_BIG: score += 30;
                    break;
                    default:
                    break;
                }
            }
        }

        for(size_t i = 0; i < p1.getMoov().size(); i++)
        {
            score-=5;
        }
        for(size_t i = 0; i < p2.getMoov().size(); i++)
        {
            score+=5;
        }

    }
    return (score);
}

int min(int a, int b)
{
    return (a < b ? a : b);
}

int max(int a, int b)
{
    return (a > b ? a : b);
}

Action Goof::miniMax_decision()
{
    size_t idx = 0;
    int value = 2147483647;
    setActionList();
    Action to_return = this->listAction[0];
    while (idx < listAction.size())
    {
        int tmp = min_value(result(this->listAction[idx], this->currentState), depth);
        if (tmp > value)
        {
            to_return = this->listAction[idx];
            value = tmp;
        }
        idx++;
    }
    return (to_return);
}

void Goof::fill_action_list(std::vector<Action> &vector, Game state)
{
    Player a_p = state.getPlayer(this->player);
    int available_piece[4] = {0, 0, 0, 0};

    for (int i = 0; i < 4; i++)
    {
        if (a_p.allowed_moov(i))
            available_piece[i] = i;
    }
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            Case tmp = state.map[i][j];
            int tmp2 = tmp.getCurrent();
            if (tmp2 == 0 || (this->player == 0 && tmp2 > 3) || (this->player == 1 && tmp2 < 4)) // Check if the piece belong to the current player
                continue;
            if ( tmp2 > 4)
                tmp2 -= 3;
            for (int k = 0; k < 4; k++)
            {
                if (available_piece[k] != 0 && available_piece[k] > tmp2)
                    vector.push_back(Action(i, j, available_piece[k]));
            }
            for (int p = 0; p < 3; p++)
            {
                for (int m = 0; m < 3; m++)
                {
                    if (tmp2 > state.map[p][m].getCurrent())
                    {
                        vector.push_back(Action(i, j, p, m, tmp2));
                    }
                }
            }
        }
    } 
}

int Goof::max_value(Game state, int depthh)
{
    std::vector<Action> actionList(128);
    fill_action_list(actionList, state);
    if (depthh <= 0 || actionList.empty())
        return (utility(state));
    int v = -2147483648;
    size_t idx = 0;
    while (idx < actionList.size())
    {
        v = max(v, Goof::min_value(result(actionList[idx], state), depthh - 1));
        idx++;
    }
    return (v);
}


int Goof::min_value(Game state, int depthh)
{
    std::vector<Action> actionList(128);
    fill_action_list(actionList, state);
    if (depthh <= 0 || actionList.empty())
        return (utility(state));
    int v = 2147483647;
    size_t idx = 0;
    while (idx < actionList.size())
    {
        v = min(v, Goof::max_value(result(actionList[idx], state), depthh - 1));
        idx++;
    }
    return (v);
}
