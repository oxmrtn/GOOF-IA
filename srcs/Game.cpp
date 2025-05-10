#include "../includes/Game.hpp"

Game::Game()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            map[i][j] = Case();
        }
    }
    player[0] = Player();
    player[1] = Player();
    up = 0; //0 if it's player 1's turn, 1 if it's player 2's turn 
}

Game& Game::operator=(const Game& other)
{
    if (this != &other)
    {
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                this->map[i][j] = other.map[i][j];
            }
        }
        this->player[0] = other.player[0];
        this->player[1] = other.player[1];
        this->up = other.up;
    }
    return *this;
}


Game::Game(const Game& other)
{
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            this->map[i][j] = other.map[i][j];
        }
    }
    this->player[0] = other.player[0];
    this->player[1] = other.player[1];
    this->up = other.up;
}


void Game::display_game() // Human readable display of the board
{
    std::cout << std::endl;
    std::cout << YELLOW << "    0   1   2   3" << DEFAULT << std::endl;
    for (int i = 0; i < SIZE; i++)
    {
        int tmp;
        std::cout << YELLOW << "   --- --- --- ---" << DEFAULT << std::endl;
        for (int j = 0; j < SIZE; j++)
        {
            if (j == 0)
                std::cout << YELLOW <<  i << DEFAULT << " | ";
            else
                std::cout << YELLOW << " | " << DEFAULT;
            tmp = map[i][j].getCurrent();
            if (tmp == P2_SMALL || tmp == P2_MEDIUM || tmp == P2_BIG || tmp == P2_BBIG)
                std::cout << MAGENTA << tmp - 4 << DEFAULT;
            else if (tmp == P1_SMALL || tmp == P1_MEDIUM || tmp == P1_BIG || tmp == P1_BBIG)
                std::cout << CYAN << tmp << DEFAULT;
            else
                std::cout << tmp;
        }
        std::cout << YELLOW << " | " << DEFAULT;
        std::cout << std::endl;
    }
    std::cout << YELLOW << "   --- --- --- ---" << DEFAULT << std::endl;
    std::cout << std::endl;
}

Game::~Game()
{}

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
            if (idx == 1 && (c != P2_SMALL && c != P2_MEDIUM && c != P2_BIG && c != P2_BBIG))
            {
                std::cout << "This is not your piece !" << std::endl;
                continue;
            }
            else if (idx == 0 && (c != P1_SMALL && c != P1_MEDIUM && c != P1_BIG && c != P1_BBIG))
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

            int c = (idx == 1) ? p + 4 : p;
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


int Game::check_line(int a, int b, int c, int d) // Check a line for possible alignement
{
    int p1 = 0;
    int p2 = 0;
    int values[4] = {a, b, c, d};

    for (int i = 0; i < SIZE; i++)
    {
        if (DET_PLAYER(values[i]) == 1) // DET_PLAYER is a macro expent in Game.hpp
            p1++;
        if (DET_PLAYER(values[i]) == 2)
            p2++;
    }
    if (p1 == 4)
    {
        return (1);
    }
    if (p2 == 4)
    {
        return (2);
    }
    return (0);
}

int Game::checker() // Check the board for a potential victory
{
    for (int j = 0; j < SIZE; j++)
    {
        int tmp = check_line(map[0][j].getCurrent(), map[1][j].getCurrent(), map[2][j].getCurrent(), map[3][j].getCurrent());
        if (tmp)
            return (tmp);
    }
    for (int i = 0; i < SIZE; i++)
    {
        int tmp = check_line(map[i][0].getCurrent(), map[i][1].getCurrent(), map[i][2].getCurrent(),map[i][3].getCurrent() );
        if (tmp)
            return (tmp);
    }
    {
        int tmp = check_line(map[0][0].getCurrent(), map[1][1].getCurrent(), map[2][2].getCurrent(), map[3][3].getCurrent());
        if (tmp)
            return (tmp);
    }
    {
        int tmp = check_line(map[0][3].getCurrent(), map[1][2].getCurrent(), map[2][1].getCurrent(), map[3][0].getCurrent());
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

Player & Game::getPlayer(int idx) // Return a player
{
    if (idx != 0 && idx != 1)
        throw std::out_of_range("error: Player index out of range");
    return (player[idx]);
}

void Game::PlayerPlay(int idx, int play) // Call a func to withdraw a piece to the Player associated object
{
    this->player[idx].play(play);
}

int Game::getUp()
{
    return this->up;
}

void Game::setUp(int value)
{
    this->up = value;
}

void Game::display_raw() // Debug func to display the raw map, without color and with the actual value of pieces
{
    std::cout << "----------------------" << std::endl;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            std::cout << " " << this->map[i][j].getCurrent();
        }
        std::cout << std::endl;
    }
    std::cout << "----------------------" << std::endl;
}

