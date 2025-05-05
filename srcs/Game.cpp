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
        std::cout << YELLOW << "   --- --- ---" << DEFAULT << std::endl;
        for (int j = 0; j < 3; j++)
        {
            if (j == 0)
                std::cout << YELLOW <<  i << DEFAULT << " | ";
            else
                std::cout << YELLOW << " | " << DEFAULT;
            tmp = map[i][j].getCurrent();
            if (tmp == P2_SMALL || tmp == P2_MEDIUM || tmp == P2_BIG)
                std::cout << MAGENTA << tmp - 3 << DEFAULT;
            else if (tmp == P1_SMALL || tmp == P1_MEDIUM || tmp == P1_BIG)
                std::cout << CYAN << tmp << DEFAULT;
            else
                std::cout << tmp;
        }
        std::cout << YELLOW << " | " << DEFAULT;
        std::cout << std::endl;
    }
    std::cout << YELLOW << "   --- --- ---" << DEFAULT << std::endl;
    std::cout << std::endl;
}

Game::~Game()
{
    std::cout << "Game destructor called" << std::endl;
}

void Game::turn(int idx)
{
    int n;

    while (true)
    {
        std::cout << "Available pieces: ";
        player[idx].display_moov();
        std::cout << "\nChoose an action:\n";
        std::cout << "1: Move a placed piece\n";
        std::cout << "2: Place a stored piece\n";

        std::cout << "Your choice: ";
        std::cin >> n;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        if (n == 1)
        {
            int a,b,c;
            std::cout << "Which piece do you want to move ? -1 to get back to previous menu " << std::endl;
            std::cout << "Enter row: ";
            std::cin >> a;
            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Invalid input.\n";
                continue;
            }
            std::cout << "Enter column: ";
            std::cin >> b;
            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Invalid input.\n";
                continue;
            }
            if (a == -1 || b == -1)
                continue;
            c = this->map[a][b].getCurrent();
            if (idx == 1 && (c != P2_SMALL && c != P2_MEDIUM && c != P2_BIG))
            {
                std::cout << "This is not your piece !" << std::endl;
                continue;
            }
            else if (idx == 0 && (c != P1_SMALL && c != P1_MEDIUM && c != P1_BIG))
            {
                std::cout << "This is not your piece !" << std::endl;
                continue;
            }
            std::cout << "CASE " << a << "; " << b << std::endl;
            this->map[a][b].undo_move();
            std::cout << "Where do you want to place the piece ? -1 to abort" << std::endl;
            int x, y;
            std::cout << "Enter row: ";
            std::cin >> x;
            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Invalid input.\n";
                continue;
            }
            std::cout << "Enter column: ";
            std::cin >> y;
            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Invalid input.\n";
                continue;
            }
            if (x == -1 || y == -1)
                continue;
            std::cout << "CASE " << x << "; " << y << std::endl;
            if (execute_moov(x, y, c))
            {
                std::cout << "Move executed.\n";
                break;
            }
            else
            {
                std::cout << "Move execution failed. Try again.\n";
                continue;
            }
        }
        else if (n == 2)
        {
            int p;
            if (!player[idx].moov_left())
                continue;
            std::cout << "You chose to place a stored piece.\n";
            std::cout << "Available pieces: ";
            player[idx].display_moov();
            std::cout << "\nWhich piece do you want to place? -1 to get back to previous menu ";

            std::cin >> p;
            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Invalid input.\n";
                continue;
            }
            if (p == -1)
                continue;
            if (!player[idx].allowed_moov(p))
            {
                std::cout << "Unavailable move.\n";
                continue;
            }

            int a, b;
            std::cout << "Enter row: ";
            std::cin >> a;
            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Invalid input.\n";
                continue;
            }

            std::cout << "Enter column: ";
            std::cin >> b;
            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Invalid input.\n";
                continue;
            }

            int c = (idx == 1) ? p + 3 : p;
            if (execute_moov(a, b, c))
            {
                player[idx].play(p);
                std::cout << "Move executed.\n";
                break;
            }
            else
            {
                std::cout << "Move execution failed. Try again.\n";
                continue;
            }
        }
        else
        {
            std::cout << "Please choose either 1 or 2.\n";
        }
    }
}


void Game::launch_game_player_versus_player()
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