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
    up = 0 //0 if it's player 1's turn, 1 if it's player 2's turn 
}

Game::Game(const Game& other)
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            this->map[i][j] = other.map[i][j];
        }
    }
    this->player[0] = other.player[0];
    this->player[1] = other.player[1];
}


void Game::display_game() // Human readable display of the board
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

void Game::turn(int idx) // Function turn for two player, idx = 0 for player 1 turn and idx = 1 for player 2 turn.
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
            this->map[a][b].undo_move();
            if (this->checker())
                return ;
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
            {
                execute_moov(a, b, c);
                continue;
            }
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

void Game::launch_game_player_versus_player() // Main loop for two player
{
    int tmp = 0;
    std::cout << " The game has began !" << std::endl;
    this->display_game();
    while (!(tmp = this->checker()))
    {
        if (up == 0)
        {
            std::cout << CYAN << "PLAYER 1 MOOV" << DEFAULT << std::endl << std::endl;
            turn(up);
        }
        else
        {
            std::cout << MAGENTA << "PLAYER 2 MOOV" << DEFAULT << std::endl << std::endl;
            turn(up);
        }
        if (up == 0)
            up = 1;
        else
            up = 0;
        this->display_game();
    }
    if (tmp == 1)
        std::cout << CYAN << " PLAYER 1 WON ! " << DEFAULT <<  std::endl;
    else
        std::cout << MAGENTA << " PLAYER 2 WON ! " << DEFAULT << std::endl;
}

int Game::check_line(int a, int b, int c) // Check a line for possible alignement
{
    int p1 = 0;
    int p2 = 0;
    int values[3] = {a, b, c};

    for (int i = 0; i < 3; i++)
    {
        if (DET_PLAYER(values[i]) == 1) // DET_PLAYER is a macro expent in Game.hpp
            p1++;
        if (DET_PLAYER(values[i]) == 2)
            p2++;
    }
    if (p1 == 3)
    {
        return (1);
    }
    if (p2 == 3)
    {
        return (2);
    }
    return (0);
}

int Game::checker() // Check the board for a potential victory
{
    for (int j = 0; j < 3; j++)
    {
        int tmp = check_line(map[0][j].getCurrent(), map[1][j].getCurrent(), map[2][j].getCurrent());
        if (tmp)
            return (tmp);
    }
    for (int i = 0; i < 3; i++)
    {
        int tmp = check_line(map[i][0].getCurrent(), map[i][1].getCurrent(), map[i][2].getCurrent());
        if (tmp)
            return (tmp);
    }
    {
        int tmp = check_line(map[0][0].getCurrent(), map[1][1].getCurrent(), map[2][2].getCurrent());
        if (tmp)
            return (tmp);
    }
    {
        int tmp = check_line(map[0][2].getCurrent(), map[1][1].getCurrent(), map[2][0].getCurrent());
        if (tmp)
            return (tmp);
    }
    return (0);
}

bool Game::execute_moov(int i, int j, int value) // Tries to place a piece in at the map[i][j] case
{
    if (!this->map[i][j].is_allowed( value ))
    {
        return (false);
    }
    else
    {
        this->map[i][j].setCase( value );
        return (true);
    }
}

Player Game::getPlayer(int idx)
{
    if (idx != 0 || idx != 1)
        return (nullptr);
    return (player[i]);
}
int Game::getUp()
{
    return this->up;
}

bool []Game::check_two_cases(int a, int b, int c) // Check a line for possible 2 pieces in a row
{
    int p1 = 0;
    int p2 = 0;
    int values[3] = {a, b, c};
    bool tab[2] = {0,0};

    for (int i = 0; i < 3; i++)
    {
        if (DET_PLAYER(values[i]) == 1) // DET_PLAYER is a macro expent in Game.hpp
            p1++;
        if (DET_PLAYER(values[i]) == 2)
            p2++;
    }
    if (p1 == 2)
    {
        tab[0] = 1;
    }
    if (p2 == 2)
    {
        tab[1] = 1;
    }
    return tab;
}

int []Game::checker_two_cases() // Check the board for a potential 2 pieces in a row
{   
    int tab[2] = {0,0};

    for (int j = 0; j < 3; j++)
    {
        int tmp = check_two_cases(map[0][j].getCurrent(), map[1][j].getCurrent(), map[2][j].getCurrent());
        if (tmp[0])
        {
            tab[0] = 1;
        }
        if(tmp[1])
        {
            tab[1] = 1;
        }
    }
    for (int i = 0; i < 3; i++)
    {
        int tmp = check_two_cases(map[i][0].getCurrent(), map[i][1].getCurrent(), map[i][2].getCurrent());
        if (tmp[0])
        {
            tab[0] += 1;
        }
        if(tmp[1])
        {
            tab[1] += 1;
        }
    }
    {
        int tmp = check_two_cases(map[0][0].getCurrent(), map[1][1].getCurrent(), map[2][2].getCurrent());
        if (tmp[0])
        {
            tab[0] += 1;
        }
        if(tmp[1])
        {
            tab[1] += 1;
        }
    }
    {
        int tmp = check_two_cases(map[0][2].getCurrent(), map[1][1].getCurrent(), map[2][0].getCurrent());
        if (tmp[0])
        {
            tab[0] += 1;
        }
        if(tmp[1])
        {
            tab[1] += 1;
        }
    }
    return tab;
}

int Game::check_center() // Check the state of the center case, return 0 if no pieces, 1 if player 1's piece, 2 if player 2's piece
{
    if (DET_PLAYER(map[1][1].getCurrent()) == 1)
        return 1;
    
    if (DET_PLAYER(map[1][1].getCurrent()) == 2)
        return 2;
    
    return 0;
}
