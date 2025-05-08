#include "../includes/Goof.hpp"

Goof::Goof(Game initState, int player)
{
    this->currentState = initState;
    this->player = player;
    this->depth = 9;
}

Goof::~Goof()
{}

void Goof::updateState(Game state)
{
    this->currentState = state;
}

void Goof::setActionList() // Determine every possible moov for a position
{
    this->listAction.clear();
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
            int tmp3 = tmp2;
            if ( tmp2 > 4)
                tmp3 = tmp2 - 3;
            for (int k = 0; k < 4; k++)
            {
           //   std::cout << "here" << std::endl
                if (available_piece[k] != 0 && available_piece[k] > tmp3)
                {
                    this->listAction.push_back(Action(i, j, available_piece[k]));
               //   std::cout << "[DEBUG] Added stored action (" << i << ", " << j << ", " << available_piece[k] << ")" << std::endl;
                }
            }
            if ((this->player == 0 && tmp2 > 3) || (this->player == 1 && tmp2 < 4))
                continue;
            if (tmp2 == 0)
                continue ;
            if ( tmp2 > 4)
                tmp2 -= 3;
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
 // std::cout << "out of setactionlist" << std::endl;
}

Game Goof::result(Action a, const Game & state)
{
    Game to_return = state;
    if (a.getType() == "stored")
    {
        int tmp = a.getMoovI(2);
        to_return.player[player].play(tmp);
        if (player == 1)
            to_return.execute_moov(a.getMoovI(0), a.getMoovI(1), tmp + 3);
        else
            to_return.execute_moov(a.getMoovI(0), a.getMoovI(1), tmp);
        if (to_return.getUp() == 1)
            to_return.setUp(0);
        else if (to_return.getUp() == 0)
            to_return.setUp(1);
    }
    else
    {
        int tmp = to_return.map[a.getMoovI(0)][a.getMoovI(1)].getCurrent();
        to_return.map[a.getMoovI(0)][a.getMoovI(1)].undo_move();
        if (to_return.checker())
            return (to_return);
        to_return.execute_moov(a.getMoovI(2), a.getMoovI(3), tmp);
        if (to_return.getUp() == 1)
            to_return.setUp(0);
        else if (to_return.getUp() == 0)
            to_return.setUp(1);
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
            return (state.display_raw() , 1000);
        if(state.checker()==2)
            return (state.display_raw() ,-1000);

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
            return (state.display_raw() ,-1000);
        if (state.checker() == 2)
            return (state.display_raw() , 1000);
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
        for (int i = 0; i<3; i++)
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
            for (int k = 0; k < 4; k++)
            {
                if (available_piece[k] != 0 && available_piece[k] > tmp2)
                    vector.push_back(Action(i, j, available_piece[k]));
            }
            if (tmp2 == 0 || (this->player == 0 && tmp2 > 3) || (this->player == 1 && tmp2 < 4)) // Check if the piece belong to the current player
                continue;
            if ( tmp2 > 4)
                tmp2 -= 3;
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

Action Goof::miniMax_decision()
{
    size_t idx = 0;
    int value = -2147483648;
    setActionList(); // pas sur que ca marche
    Action to_return = this->listAction[0];
  //std::cout << "things = " << this->listAction[0].getMoovI(0) << std::endl;
    while (idx < listAction.size())
    {
        int tmp = min_value(result(this->listAction[idx], this->currentState), this->depth - 1);
        // int tmpp2 = utility2(result(this->listAction[idx], this->currentState));
        // if (listAction[idx].getType() == "stored")
        //     std::cout << " Action type = " << listAction[idx].getType() << " {" << listAction[idx].getMoovI(0) << ";" << listAction[idx].getMoovI(1) << "}" << " piece " << listAction[idx].getMoovI(2) << " utility score = " << tmpp2 <<   std::endl;
        // else
        // {
        //     std::cout << " Action type = " << listAction[idx].getType() << " from  {" << listAction[idx].getMoovI(0) << ";" << listAction[idx].getMoovI(1) << "}" << " move to " << " {" << listAction[idx].getMoovI(2) << ";" << listAction[idx].getMoovI(3) << "}"<< listAction[idx].getMoovI(4) <<" utility score = " << tmpp2 << std::endl;
        // }
        //std::cout << "TMP = " << tmp << "  \\ idx = " << idx << std::endl;
        if (tmp > value)
        {
            //std::cout << "MAX UPDATED = " << tmp << std::endl; 
            to_return = this->listAction[idx];
            value = tmp;
        }
        idx++;
    }
  //std::cout << "end of miniMAX, value = " << value << std::endl;
  //std::cout << "moov = {" << to_return.getMoovI(0) << ", " << to_return.getMoovI(1) << "} piece = " << to_return.getMoovI(2) << std::endl;
    return (to_return);
}

int Goof::max_value(Game state, int depthh)
{
    std::vector<Action> actionList;
    fill_action_list(actionList, state);
    if (depthh <= 0 || actionList.empty() || state.checker())
        return ( utility2(state));
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
    std::vector<Action> actionList;
    fill_action_list(actionList, state);
    if (depthh <= 0 || actionList.empty() || state.checker())
    {
        return ( utility2(state));
    }
    int v = 2147483647;
    size_t idx = 0;
    while (idx < actionList.size())
    {
        v = min(v, Goof::max_value(result(actionList[idx], state), depthh - 1));
        idx++;
    }
    return (v);
}

Action Goof::miniMax_decision_ab()
{
    size_t idx = 0;
    int value = -2147483648;
    setActionList();
    Action to_return = this->listAction[0];
    while (idx < listAction.size())
    {
        int tmp = min_value_ab(result(this->listAction[idx], this->currentState), this->depth - 1, -2147483648, 2147483647);

        if (tmp > value)
        {
            to_return = this->listAction[idx];
            value = tmp;
        }
        idx++;
    }
    return (to_return);
}


int Goof::max_value_ab(Game state, int depthh, int alpha, int beta)
{
    std::vector<Action> actionList;
    fill_action_list(actionList, state);
    if (depthh <= 0 || actionList.empty() || state.checker())
        return ( utility2(state));
    int v = -2147483648;
    size_t idx = 0;
    while (idx < actionList.size())
    {
        v = max(v, Goof::min_value_ab(result(actionList[idx], state), depthh - 1, alpha, beta));
        if (v >= beta)
            return (v);
        alpha = max(alpha, v);
        idx++;
    }
    return (v);
}

int Goof::min_value_ab(Game state, int depthh, int alpha, int beta)
{
    std::vector<Action> actionList;
    fill_action_list(actionList, state);
    if (depthh <= 0 || actionList.empty() || state.checker())
    {
        return ( utility2(state));
    }
    int v = 2147483647;
    size_t idx = 0;
    while (idx < actionList.size())
    {
        v = min(v, Goof::max_value_ab(result(actionList[idx], state), depthh - 1, alpha, beta));
        if (v <= alpha)
            return (v);
        beta  = min(beta, v);
        idx++;
    }
    return (v);
}