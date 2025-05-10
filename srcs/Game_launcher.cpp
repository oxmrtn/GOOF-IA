#include "../includes/Game.hpp"

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

void Game::launch_game_player_versus_ia(int bot_player) // Main loop for player versus IA
{
    int tmp = 0;
    std::cout << " The game has began !" << std::endl;
    this->display_game();
    while (!(tmp = this->checker()))
    {
        if(bot_player == 0)
        {    
            if (this->up == 0)
            {
                std::cout << CYAN << "PLAYER 1 MOOV" << DEFAULT << std::endl << std::endl;
                Goof goof_ia = Goof(*this, bot_player, 2);
                Action action = goof_ia.miniMax_decision_ab();

                if(action.getType() == "stored")
                {
                    if (execute_moov(action.getMoovI(0),action.getMoovI(1),action.getMoovI(2)))
                    {
                        player[0].play(action.getMoovI(2));
                    }
                }else
                {
                    this->map[action.getMoovI(0)][action.getMoovI(1)].undo_move();
                    execute_moov(action.getMoovI(2),action.getMoovI(3),action.getMoovI(4));
                }
            }
            else
            {
                std::cout << MAGENTA << "PLAYER 2 MOOV" << DEFAULT << std::endl << std::endl;
                turn(this->up);
            }
        }
        if(bot_player == 1)
        {    
            if (this->up == 0)
            {   
                std::cout << CYAN << "PLAYER 1 MOOV" << DEFAULT << std::endl << std::endl;
                turn(this->up);
            }
            else
            {
                std::cout << MAGENTA << "PLAYER 2 MOOV" << DEFAULT << std::endl << std::endl;
                Goof goof_ia = Goof(*this, bot_player, 2);

                Action action = goof_ia.miniMax_decision_ab();

                if(action.getType() == "stored")
                {
                    std::cout << "BOT PLAYED A PIECE" << std::endl;
                    if (execute_moov(action.getMoovI(0),action.getMoovI(1),action.getMoovI(2) + 4))
                    {
                        player[1].play(action.getMoovI(2));
                    }
                }
                else
                {
                    std::cout << "BOT MOOVED A PIECE" << std::endl;
                    int temp = map[action.getMoovI(0)][action.getMoovI(1)].getCurrent();
                    this->map[action.getMoovI(0)][action.getMoovI(1)].undo_move();
                    if (checker())
                        continue;
                    execute_moov(action.getMoovI(2),action.getMoovI(3), temp);
                }
            }
        }
        if (this->up == 0)
            this->up = 1;
        else
            this->up = 0;
        this->display_game();
    }
    if (tmp == 1)
        std::cout << CYAN << " PLAYER 1 WON ! " << DEFAULT <<  std::endl;
    else
        std::cout << MAGENTA << " PLAYER 2 WON ! " << DEFAULT << std::endl;
}
