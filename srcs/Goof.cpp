#include "../includes/Goof.hpp"

Goof::Goof(Game initState, int player, int difficulty)
{
    this->currentState = initState;
    this->player = player;
    this->depth = 3;
    if (difficulty == 0)
        this->utilityFunction = &Goof::utility_easy;
    else if (difficulty == 1)
        this->utilityFunction = &Goof::utility_medium;
    else if (difficulty == 2)
    {
        this->utilityFunction = &Goof::utility_hard;
        this->depth = 3;
    }
    else
        this->utilityFunction = &Goof::utility_easy;

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
    Player a_p = this->currentState.getPlayer(currentState.getUp());
    int available_piece[5] = {0, 0, 0, 0, 0};
    for (int i = 0; i < 5; i++)
    {
        if (a_p.allowed_moov(i))
            available_piece[i] = i;
    }
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            Case tmp = currentState.map[i][j];
            int tmp2 = tmp.getCurrent();
            int tmp3 = tmp2;
            if ( tmp2 > 4)
                tmp3 = tmp2 - 4;
            for (int k = 0; k < 5; k++)
            {
           //   std::cout << "here" << std::endl
                if (available_piece[k] != 0 && available_piece[k] > tmp3)
                {
                    this->listAction.push_back(Action(i, j, available_piece[k]));
               //   std::cout << "[DEBUG] Added stored action (" << i << ", " << j << ", " << available_piece[k] << ")" << std::endl;
                }
            }
            if ((this->player == 0 && tmp2 > 4) || (this->player == 1 && tmp2 < 5))
                continue;
            if (tmp2 == 0)
                continue ;
            if ( tmp2 > 5)
                tmp2 -= 4;
            for (int p = 0; p < SIZE; p++)
            {
                for (int m = 0; m < SIZE; m++)
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

void Goof::fill_action_list(std::vector<Action> &vector, Game state)
{
    vector.clear();
    Player a_p = state.getPlayer(state.getUp());
    int available_piece[5] = {0, 0, 0, 0, 0};
    for (int i = 0; i < 5; i++)
    {
        if (a_p.allowed_moov(i))
            available_piece[i] = i;
    }
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            Case tmp = state.map[i][j];
            int tmp2 = tmp.getCurrent();
            int tmp3 = tmp2;
            if ( tmp2 > 4)
                tmp3 = tmp2 - 4;
            for (int k = 0; k < 5; k++)
            {
           //   std::cout << "here" << std::endl
                if (available_piece[k] != 0 && available_piece[k] > tmp3)
                {
                    vector.push_back(Action(i, j, available_piece[k]));
               //   std::cout << "[DEBUG] Added stored action (" << i << ", " << j << ", " << available_piece[k] << ")" << std::endl;
                }
            }
            if ((state.getUp() == 0 && tmp2 > 4) || (state.getUp() == 1 && tmp2 < 5))
                continue;
            if (tmp2 == 0)
                continue ;
            if ( tmp2 > 5)
                tmp2 -= 4;
            for (int p = 0; p < SIZE; p++)
            {
                for (int m = 0; m < SIZE; m++)
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

Game Goof::result(Action a, const Game & state)
{
    Game to_return = state;
    if (a.getType() == "stored")
    {
        int tmp = a.getMoovI(2);
        to_return.player[to_return.getUp()].play(tmp);
        if (to_return.getUp() == 1)
            to_return.execute_moov(a.getMoovI(0), a.getMoovI(1), tmp + 4);
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


int min(int a, int b)
{
    return (a < b ? a : b);
}

int max(int a, int b)
{
    return (a > b ? a : b);
}

Action Goof::miniMax_decision_ab()
{
    size_t idx = 0;
    int value = -2147483648;
    setActionList();
    Action to_return ;
    while (idx < listAction.size())
    {
        int tmp = min_value_ab(result(this->listAction[idx], this->currentState), this->depth - 1, -2147483648, 2147483647);
        //int tmpp2 = utility2(result(this->listAction[idx], this->currentState));
        // if (listAction[idx].getType() == "stored")
        //     std::cout << " Action type = " << listAction[idx].getType() << " {" << listAction[idx].getMoovI(0) << ";" << listAction[idx].getMoovI(1) << "}" << " piece " << listAction[idx].getMoovI(2) << " utility score = " << tmpp2 << std::endl;
        // else
        // {
        //     std::cout << " Action type = " << listAction[idx].getType() << " from  {" << listAction[idx].getMoovI(0) << ";" << listAction[idx].getMoovI(1) << "}" << " move to " << " {" << listAction[idx].getMoovI(2) << ";" << listAction[idx].getMoovI(3) << "}"<< listAction[idx].getMoovI(4) <<" utility score = " << tmpp2 << std::endl;
        // }
        // std::cout << " tmp = " << tmp << " value = " << value << " tmp > value = " << (tmp > value) << std::endl;
        if (tmp > value)
        {
            to_return = this->listAction[idx];
            value = tmp;
            std::cout << "hit" << std::endl;
        }
        idx++;
    }
    std::cout << "end of miniMAX, value = " << value << std::endl;
    std::cout << "moov = {" << to_return.getMoovI(0) << ", " << to_return.getMoovI(1) << "} piece = " << to_return.getMoovI(2) << std::endl;
    return (to_return);
}


int Goof::max_value_ab(Game state, int depthh, int alpha, int beta)
{
    std::vector<Action> actionList;
    fill_action_list(actionList, state);
    if (depthh <= 0 || actionList.empty() || state.checker())
    {
        if (state.checker())
            state.display_game();
        return ( (this->*utilityFunction)(state) );
    }
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
        if (state.checker())
            state.display_game();
        return ((this->*utilityFunction)(state) );
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