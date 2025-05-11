#include "../includes/Game.hpp"

void tournament()
{
    std::cout << "Tournament mode " << std::endl;
    {
        std::cout << "Easy vs Medium" << std::endl;
        {
        int mv = 0;
        int ev = 0;
        for (int i = 0; i < 25; i++)
        {
            Game init = Game();
            int tmp = init.launch_game_ia_versus_ia(0, 1);
            if (tmp == 1)
                ev++;
            else
                mv++;
        }
        std::cout << "Easy vs medium, Easy play firt result : \n Easy victory = " << ev << "\n Medium victory = " << mv << std::endl;
        }
        {
            int mv = 0;
            int ev = 0;
            for (int i = 0; i < 25; i++)
            {
                Game init = Game();
                int tmp = init.launch_game_ia_versus_ia(1, 0);
                if (tmp == 1)
                    mv++;
                else
                    ev++;
            }
            std::cout << "Easy vs medium, Medium play firt result : \n Easy victory = " << ev << "\n Medium victory = " << mv << std::endl;
        }
    }
    {
        std::cout << "Hard vs Easy" << std::endl;
        {
        int mv = 0;
        int ev = 0;
        for (int i = 0; i < 25; i++)
        {
            Game init = Game();
            int tmp = init.launch_game_ia_versus_ia(0, 2);
            if (tmp == 1)
                ev++;
            else
                mv++;
        }
        std::cout << "Hard vs easy, easy play firt result : \n Easy victory = " << ev << "\n Hard victory = " << mv << std::endl;
        }
        {
            int mv = 0;
            int ev = 0;
            for (int i = 0; i < 25; i++)
            {
                Game init = Game();
                int tmp = init.launch_game_ia_versus_ia(2, 0);
                if (tmp == 1)
                    mv++;
                else
                    ev++;
            }
            std::cout << "Easy vs Hard, Hard play firt result : \n Easy victory = " << ev << "\n Hard victory = " << mv << std::endl;
        }
    }
    {
        std::cout << "Hard vs Medium" << std::endl;
        {
        int mv = 0;
        int ev = 0;
        for (int i = 0; i < 25; i++)
        {
            Game init = Game();
            int tmp = init.launch_game_ia_versus_ia(1, 2);
            if (tmp == 1)
                ev++;
            else
                mv++;
        }
        std::cout << "Hard vs Medium, medium play firt result : \n Medium victory = " << ev << "\n Hard victory = " << mv << std::endl;
        }
        {
            int mv = 0;
            int ev = 0;
            for (int i = 0; i < 25; i++)
            {
                Game init = Game();
                int tmp = init.launch_game_ia_versus_ia(2, 1);
                if (tmp == 1)
                    mv++;
                else
                    ev++;
            }
            std::cout << "Medium vs Hard, Hard play firt result : \n Medium victory = " << ev << "\n Hard victory = " << mv << std::endl;
        }
    }
}

void display_difficulty_menu(int& difficulty)
{
    std::cout << "\nChoose difficulty level:" << std::endl;
    std::cout << "1. Easy\n2. Medium\n3. Hard" << std::endl;
    while (difficulty < 1 || difficulty > 3)
    {
        std::cout << "Your choice (1-3): ";
        std::cin >> difficulty;
    }
}

void menu()
{
    int gm_choice = 0;
    std::cout << BLUE << "Welcome to  Goofy Gobblets game ! Please choose a game mode :" << DEFAULT << std::endl;
    std::cout << "1. Player versus Player " << std::endl;
    std::cout << "2. Player versus Goofybot " << std::endl;
    std::cout << "3. Goofybot versus Goofybot " << std::endl;
    while (gm_choice != 1 && gm_choice != 2 && gm_choice != 3)
    {
        std::cout << RED << "Your choice : " << DEFAULT;
        std::cin >> gm_choice;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }
    }
    Game game;
    switch (gm_choice)
    {
        case 1:
        game.launch_game_player_versus_player();
        break;
        case 2:
        {
            int bot_player = 0;
            while (bot_player != 1 && bot_player != 2)
            {
                std::cout << "\nShould the bot be:\n1. Player 1\n2. Player 2\nYour choice: ";
                std::cin >> bot_player;
            }

            int difficulty = 0;
            display_difficulty_menu(difficulty);
            game.launch_game_player_versus_ia(bot_player - 1, difficulty - 1);
            break;
        }
        case 3:
        {
            int p1_difficulty = 0, p2_difficulty = 0;
            std::cout << "\nDifficulty for Goofybot Player 1:" << std::endl;
            display_difficulty_menu(p1_difficulty);

            std::cout << "\nDifficulty for Goofybot Player 2:" << std::endl;
            display_difficulty_menu(p2_difficulty);

            game.launch_game_ia_versus_ia(p1_difficulty - 1, p2_difficulty - 1);
            break;
        }
        default:
            break;
    }
    return ;

}


int main(int argc, char **argv)
{
    (void)argv;
    try{
        if (argc != 1)
        {
            std::cerr << "error: No argument is required !";
            return (1);
        }
        menu();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    return (0);
}
