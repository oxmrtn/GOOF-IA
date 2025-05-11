#include "../includes/Goof.hpp"

Goof::Goof(Game initState, int player, int difficulty)
{
    this->currentState = initState;
    this->player = player;
    this->depth = 2;
    if (difficulty == 0)
        this->utilityFunction = &Goof::utility_easy;
    else if (difficulty == 1)
        this->utilityFunction = &Goof::utility_medium;
    else if (difficulty == 2)
        this->utilityFunction = &Goof::utility_hard;
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
                if (available_piece[k] != 0 && available_piece[k] > tmp3)
                {
                    this->listAction.push_back(Action(i, j, available_piece[k])); // Add an action to the attribute list
                }
            }
            if ((this->player == 0 && tmp2 > 4) || (this->player == 1 && tmp2 < 5))
                continue;
            if (tmp2 == 0)
                continue ;
            if ( tmp2 > 4)
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

void Goof::fill_action_list(std::vector<Action> &vector, Game state) // Fill the vector with every possible moov for a state
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
            if ( tmp3 > 4)
                tmp3 -= 4;
            for (int k = 0; k < 5; k++)
            {
                if (available_piece[k] != 0 && available_piece[k] > tmp3)
                {
                    vector.push_back(Action(i, j, available_piece[k]));
                }
            }
            if ((state.getUp() == 0 && tmp2 > 4) || (state.getUp() == 1 && tmp2 < 5))
                continue;
            if (tmp2 == 0)
                continue ;
            if ( tmp2 > 4 )
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

Game Goof::result(Action a, const Game & state) // Return a game wich is the "state" of the game with the a Action applied to it
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


int min(int a, int b) // Min func
{
    return (a < b ? a : b);
}

int max(int a, int b) // Max func
{
    return (a > b ? a : b);
}

size_t get_random_index(const std::vector<Action>& vec) {
    if (vec.empty())
    {
        throw std::invalid_argument("Le vecteur est vide !");
    }
    static std::mt19937 gen(static_cast<unsigned>(std::time(nullptr)));
    std::uniform_int_distribution<size_t> dist(0, vec.size() - 1);
    
    return dist(gen);
}

Action Goof::miniMax_decision_ab() // Minimax algorithm with alpha beta heuristic, it return the best Action to do in the current position
{
    size_t idx = 0;
    std::vector<Action> to_return; // The vector permit to have random moov amongst the best ones
    int value = -2147483648; // init value to minimum int
    int alpha = -2147483648;
    int beta = 2147483647;
    setActionList();
    while (idx < listAction.size())
    {
        int tmp = min_value_ab(result(this->listAction[idx], this->currentState), this->depth - 1, alpha, beta);
        if (tmp > value)
        {
            to_return.clear();
            to_return.push_back(this->listAction[idx]);
            value = tmp;
        }
        else if (tmp == value)
            to_return.push_back(this->listAction[idx]);
        alpha = max(alpha, value);
        idx++;
    }
    return (to_return[get_random_index(to_return)]);
}


int Goof::max_value_ab(Game state, int depthh, int alpha, int beta) // Maxvalue recursive algorithm used by minimax_decision
{
    std::vector<Action> actionList;
    fill_action_list(actionList, state);
    if (depthh <= 0 || actionList.empty() || state.checker())
    {
        return ( (this->*utilityFunction)(state, actionList.size()) );
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

int Goof::min_value_ab(Game state, int depthh, int alpha, int beta) // Minvalue recursive algorithm used by minimax_decision
{
    std::vector<Action> actionList;
    fill_action_list(actionList, state);
    if (depthh <= 0 || actionList.empty() || state.checker())
    {
        return ((this->*utilityFunction)(state, actionList.size()) );
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