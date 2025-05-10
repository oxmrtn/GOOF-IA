#include "../includes/Game.hpp"

/* 
    Func in this file is tools for utility func to behave as expected

*/

int Game::central_control( int player ) // Check for the center of the board control
{
    int p1 = 0; int opps = 0;
    for (int i = 1; i < 3; i++)
    {
        for (int j = 1; j < 3; j++)
        {
            int k = DET_PLAYER(map[i][j].getCurrent());
            if (k == player)
                p1++;
            else if (k != 0)
                opps++;
        }
    }
    if (p1 > opps)
        return (3);
    else if (p1 == opps)
        return (0);
    else
        return (-3);
}

int check_partial_line(int a, int b, int c, int d, int player) // Check if a player has 3 piece aligned
{
    int player_id = player + 1;
    int count = 0;
    int empty = 0;
    
    if (DET_PLAYER(a) == player_id) count++;
    else if (DET_PLAYER(a) == 0) empty++;
    
    if (DET_PLAYER(b) == player_id) count++;
    else if (DET_PLAYER(b) == 0) empty++;

    if (DET_PLAYER(c) == player_id) count++;
    else if (DET_PLAYER(c) == 0) empty++;
    
    if (DET_PLAYER(d) == player_id) count++;
    else if (DET_PLAYER(d) == 0) empty++;
    
    if (count == 3 && empty == 1)
        return 10;
    if (count == 2 && empty == 2)
        return 3;
    if (count == 1 && empty == 3)
        return 1;    
    return 0;
}

int Game::aligned_piece( int pturn ) // Check every row, column if a player as aligned piece (= setup for a win)
{
    int score = 0;
    for (int j = 0; j < SIZE; j++)
    {
        score += check_partial_line(map[0][j].getCurrent(), map[1][j].getCurrent(), map[2][j].getCurrent(), map[3][j].getCurrent(), pturn);
    }
    for (int i = 0; i < SIZE; i++)
    {
        score += check_partial_line(map[i][0].getCurrent(), map[i][1].getCurrent(), map[i][2].getCurrent(),map[i][3].getCurrent(), pturn);

    }
    score += check_partial_line(map[0][0].getCurrent(), map[1][1].getCurrent(), map[2][2].getCurrent(), map[3][3].getCurrent(), pturn);
    score += check_partial_line(map[0][3].getCurrent(), map[1][2].getCurrent(), map[2][1].getCurrent(), map[3][0].getCurrent(), pturn);
    return (score);
}

int Game::piece_value( int player ) // Check the value of the piece on the board, the more a player have piece on the board, the more he have control on the board
{
    int score = 0;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            int tmp = map[i][j].getCurrent();
            if (DET_PLAYER(tmp) == player + 1)
            {
                if (tmp == P1_SMALL || tmp == P2_SMALL)
                    score += 3;
                else if (tmp == P1_MEDIUM || tmp == P2_MEDIUM)
                    score += 3;
                else if (tmp == P1_BIG || tmp == P2_BIG)
                    score += 4;
                else if (tmp == P1_BBIG || tmp == P2_BBIG)
                    score += 5;
            }
        }
    }
    return (score);
}

int check_threat(int a, int b, int c, int d, int player) // Check for potential threat of win (3 piece aligned and an empty case )
{
    int player_id = player + 1;
    int count = 0;
    int empty = 0;
    int opponent = 0;
    
    if (DET_PLAYER(a) == player_id) count++;
    else if (DET_PLAYER(a) == 0) empty++;
    else if (DET_PLAYER(a) != player) opponent++;
    
    if (DET_PLAYER(b) == player_id) count++;
    else if (DET_PLAYER(b) == 0) empty++;
    else if (DET_PLAYER(b) != player) opponent++;

    if (DET_PLAYER(c) == player_id) count++;
    else if (DET_PLAYER(c) == 0) empty++;
    else if (DET_PLAYER(c) != player) opponent++;
    
    if (DET_PLAYER(d) == player_id) count++;
    else if (DET_PLAYER(d) == 0) empty++;
    else if (DET_PLAYER(d) != player) opponent++;
    
    if (count == 3 && empty == 1)
        return 90;
    if (count == 2 && empty == 2)
        return 10;
    if (count == 1 && empty == 3)
        return 1;
    if (opponent == 3 && empty == 1)
        return (-400);
    if (opponent == 2 && empty == 2)
        return -10;
    return 0;
}


int Game::count_threat( int pturn) // Use to detect every threat on the board
{
    int score = 0;
    for (int j = 0; j < SIZE; j++)
    {
        score += check_threat(map[0][j].getCurrent(), map[1][j].getCurrent(), map[2][j].getCurrent(), map[3][j].getCurrent(), pturn);
    }
    for (int i = 0; i < SIZE; i++)
    {
        score += check_threat(map[i][0].getCurrent(), map[i][1].getCurrent(), map[i][2].getCurrent(),map[i][3].getCurrent(), pturn);

    }
    score += check_threat(map[0][0].getCurrent(), map[1][1].getCurrent(), map[2][2].getCurrent(), map[3][3].getCurrent(), pturn);
    score += check_threat(map[0][3].getCurrent(), map[1][2].getCurrent(), map[2][1].getCurrent(), map[3][0].getCurrent(), pturn);
    return (score);
}

int Game::heat_map( int player ) // Return a heatmap of the board, the more a case is powerfull, the more it give score
{
    int score = 0;
    int heat[4][4] = {{1, 3, 3, 1},
                      {3, 5, 5, 3},
                      {3, 5, 5, 3},
                      {1, 3, 3, 1}};
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            int tmp = DET_PLAYER(map[i][j].getCurrent());
            if (tmp == player + 1)
                score += heat[i][j];
            else if (tmp != 0)
                score -= heat[i][j];
        }
    }
    return (score);
}

int Game::detect_fork( int pturn ) // Detect potential fork, wich is two 3 aligned piece sequence.
{
    int count_fork = 0;
    for (int j = 0; j < SIZE; j++)
    {
        if (check_threat(map[0][j].getCurrent(), map[1][j].getCurrent(), map[2][j].getCurrent(), map[3][j].getCurrent(), pturn) == 90)
            count_fork++;
    }
    for (int i = 0; i < SIZE; i++)
    {
        if (check_threat(map[i][0].getCurrent(), map[i][1].getCurrent(), map[i][2].getCurrent(),map[i][3].getCurrent(), pturn) == 90)
            count_fork++;

    }
    if (check_threat(map[0][0].getCurrent(), map[1][1].getCurrent(), map[2][2].getCurrent(), map[3][3].getCurrent(), pturn) == 90)
        count_fork++;
    if (check_threat(map[0][3].getCurrent(), map[1][2].getCurrent(), map[2][1].getCurrent(), map[3][0].getCurrent(), pturn) == 90)
        count_fork++;
    if (count_fork >= 2)
        return (400);
    else
        return (0);
}

int Game::remaining_piece( int player ) // Return a score based on the piece the player have left
{
    return (this->player[player].score_count());
}


