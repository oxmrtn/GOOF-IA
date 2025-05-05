#include "../includes/Game.hpp"

int main(int argc, char **argv)
{
    (void)argv;
    if (argc != 1)
    {
        std::cerr << "error: No argument is required !";
        return (1);
    }
    Game init = Game();
    init.launch_game_player_versus_player();
    return (0);
}
