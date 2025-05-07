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
        Game init = Game();
        init.launch_game_player_versus_player();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    return (0);
}
