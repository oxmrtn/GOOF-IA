#include "../includes/Game.hpp"

Game::Game()
{
    std::cout << "Game default constructor called" << std::endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            map[i][j] = 0;
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
            std::cout << map[i][j];
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
    std::cout << " The game has began !" << std::endl;
    this->display_game();
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
        if (check_line(map[0][j], map[1][j], map[2][j]))
            return (true);
    }
    for (int i = 0; i < 3; i++)
    {
        if (check_line(map[i][0], map[i][1], map[i][2]))
            return (true);
    }
    if (check_line(map[0][0], map[1][1], map[2][2]))
        return (true);

    if (check_line(map[0][2], map[1][1], map[2][0]))
        return (true);
    return (false);
}