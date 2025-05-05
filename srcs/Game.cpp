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
    player[0] = Player();
    player[1] = Player(); 
}

void Game::display_game()
{
    std::cout << std::endl;
    std::cout << YELLOW << "    0   1   2 " << DEFAULT << std::endl;
    for (int i = 0; i < 3; i++)
    {
        int tmp;
        std::cout << "   --- --- ---" << std::endl;
        for (int j = 0; j < 3; j++)
        {
            if (j == 0)
                std::cout << YELLOW <<  i << DEFAULT << " | ";
            else
                std::cout << " | ";
            tmp = map[i][j].getCurrent();
            std::cout << "D" << tmp;
            if (tmp == P2_SMALL || tmp == P2_MEDIUM || tmp == P2_BIG)
                std::cout << MAGENTA << tmp - 3 << DEFAULT;
            else if (tmp == P1_SMALL || tmp == P1_MEDIUM || tmp == P1_BIG)
                std::cout << CYAN << tmp << DEFAULT;
            else
                std::cout << tmp;
        }
        std::cout << " | ";
        std::cout << std::endl;
    }
    std::cout << "   --- --- ---" << std::endl;
    std::cout << std::endl;
}

Game::~Game()
{
    std::cout << "Game destructor called" << std::endl;
}

void Game::turn(int idx)
{
    int n;

    std::cout << "Available piece : ";
    player[idx].display_moov();
    std::cout << std::endl;
    std::cout << "1: Moov a placed piece" << std::endl;
    std::cout << "2: Moov a stored piece" << std::endl;
    std::cin >> n;
    if (n < 1 || n > 2)
        return ;
    if (n == 1)
    {
        return ;
    }
    else
    {
        int p;
        std::cout << "You choose to place a stored piece" << std::endl;
        std::cout << "Available piece : ";
        player[idx].display_moov();
        std::cout << std::endl;
        std::cout << "What piece do u want to place" << std::endl;
        std::cin >> p;
        if (player[idx].allowed_moov(p))
        {
            std::cout << "DEBUG P = " << p << std::endl;
            int a, b, c;
            std::cout << "Row ? : ";
            std::cin >> a;
            std::cout << std::endl;
            std::cout << "Column ? : ";
            std::cin >> b;
            if (idx == 1)
                c = p + 3;
            else
                c = p;
            if (execute_moov(a,b,c))
                player[idx].play(p);
        }
        else
        {
            std::cout << "Unavailable moov" << std::endl;
        }

    }
}


void Game::launch_game()
{
    int i = 0;
    std::cout << " The game has began !" << std::endl;
    this->display_game();
    while (!this->checker())
    {
        if (i == 0)
        {
            std::cout << "PLAYER 1 MOOV" << std::endl << std::endl;
            turn(i);
        }
        else
        {
            std::cout << "PLAYER 2 MOOV" << std::endl << std::endl;
            turn(i);
        }
        if (i == 0)
            i = 1;
        else
            i = 0;
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
    {
        // std::cout << RED << "HERE" << DEFAULT << std::endl;
        return (false);
    }
    else
    {
        this->map[i][j].setCase( value );
        return (true);
    }
}