#include "../includes/Game.hpp"

int main(int argc, char **argv)
{
    (void)argv;
    try{
        if (argc != 1)
        {
            std::cerr << "error: No argument is required !";
            return (1);
        }
        std::cout << "Tournament mode " << std::endl;
        {
            std::cout << "Easy vs Medium" << std::endl;
            {
            int mv = 0;
            int ev = 0;
            while (int i = 0; i < 25; i++)
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
                while (int i = 0; i < 25; i++)
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
            while (int i = 0; i < 25; i++)
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
                while (int i = 0; i < 25; i++)
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
            while (int i = 0; i < 25; i++)
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
                while (int i = 0; i < 25; i++)
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

        Game init = Game();
        init.launch_game_ia_versus_ia(0, 0);
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    return (0);
}
