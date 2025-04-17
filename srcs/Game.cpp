#include "../includes/Game.hpp"

Game::Game()
{
    std::cout << "Game default constructor called" << std::endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            map[i][j] = Case();
        }
    }
}

void Game::display_game()
{
    
    for (int i = 0; i < 3; i++)
    {
        std::cout << "  --- --- ---" << std::endl;
        for (int j = 0; j < 3; j++)
        {
            std::cout << " | ";
            std::cout << map[i][j].getCurrent();
        }
        std::cout << " | ";
        std::cout << std::endl;
    }
    std::cout << "  --- --- ---" << std::endl;
    std::cout << std::endl;
}

Game::~Game()
{
    std::cout << "Game destructor called" << std::endl;
}

void Game::launch_game()
{
    int i = 1;
    std::cout << " The game has began !" << std::endl;
    while (!this->checker())
    {
        if (i == 1)
        {
            std::string temp;
            std::cout << "PLAYER 1 MOOV" << std::endl << std::endl;
            execute_moov(0,0, P1_SMALL);
        }
        else
        {
            std::cout << "PLAYER 2 MOOV" << std::endl << std::endl;
            execute_moov(0,0, P2_MEDIUM);
        }
        i = -i;
        this->display_game();
        
    }
}

bool Game::check_line(int a, int b, int c)
{
    int p1 = 0;
    int p2 = 0;
    int values[3] = {a, b, c};

    for (int i = 0; i < 3; i++)
    {
        if (DET_PLAYER(values[i]) == 1)
            p1++;
        if (DET_PLAYER(values[i]) == 2)
            p2++;
    }
    if (p1 == 3)
    {
        std::cout << "Player 1 won" << std::endl;
        return (true);
    }
    if (p2 == 3)
    {
        std::cout << "Player 2 won" << std::endl;
        return (true);
    }
    return (false);
}

bool Game::checker()
{
    for (int j = 0; j < 3; j++)
    {
        if (check_line(map[0][j].getCurrent(), map[1][j].getCurrent(), map[2][j].getCurrent()))
            return (true);
    }
    for (int i = 0; i < 3; i++)
    {
        if (check_line(map[i][0].getCurrent(), map[i][1].getCurrent(), map[i][2].getCurrent()))
            return (true);
    }
    if (check_line(map[0][0].getCurrent(), map[1][1].getCurrent(), map[2][2].getCurrent()))
        return (true);

    if (check_line(map[0][2].getCurrent(), map[1][1].getCurrent(), map[2][0].getCurrent()))
        return (true);
    return (false);
}

bool Game::execute_moov(int i, int j, int value)
{
    if (!this->map[i][j].is_allowed( value ))
        return (false);
    else
    {
        this->map[i][j].setCase( value );
        return (true);
    }
}