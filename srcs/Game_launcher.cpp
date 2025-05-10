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

int Game::launch_game_player_versus_ia(int bot_player, int difficulty) // Main loop for player versus IA
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
                Goof goof_ia = Goof(*this, bot_player, difficulty);
                Action action = goof_ia.miniMax_decision_ab();

                if(action.getType() == "stored")
                {
                    if (execute_moov(action.getMoovI(0),action.getMoovI(1),action.getMoovI(2)))
                    {
                        player[0].play(action.getMoovI(2));
                    }
                }
                else
                {
                    int temp = map[action.getMoovI(0)][action.getMoovI(1)].getCurrent();
                    this->map[action.getMoovI(0)][action.getMoovI(1)].undo_move();
                    if (checker())
                    {
                        tmp = 1;
                        this->display_game();
                        break;
                    }
                    execute_moov(action.getMoovI(2),action.getMoovI(3), temp);
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
                Goof goof_ia = Goof(*this, bot_player, difficulty);

                Action action = goof_ia.miniMax_decision_ab();

                if(action.getType() == "stored")
                {
                    if (execute_moov(action.getMoovI(0),action.getMoovI(1),action.getMoovI(2) + 4))
                    {
                        player[1].play(action.getMoovI(2));
                    }
                }
                else
                {
                    int temp = map[action.getMoovI(0)][action.getMoovI(1)].getCurrent();
                    this->map[action.getMoovI(0)][action.getMoovI(1)].undo_move();
                    if (checker())
                    {
                        tmp = 2;
                        this->display_game();
                        break;
                    }
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
    {
        std::cout << CYAN << " PLAYER 1 WON ! " << DEFAULT <<  std::endl;
        return (1);
    }
    else
    {
        std::cout << MAGENTA << " PLAYER 2 WON ! " << DEFAULT << std::endl;
        return (2);
    }
}


int Game::launch_game_ia_versus_ia(int p1_difficulty, int p2_difficulty)
{
    int victory;
    int turn = 0;
    std::cout << " The game has began !" << std::endl;
    this->display_game();
    while (true)
    {
        victory = this->checker();
        if (victory)
            break ;
        if (turn == 0)
        {
            std::cout << CYAN << "PLAYER 1 MOOV" << DEFAULT << std::endl << std::endl;
            Goof p1 = Goof(*this, 0, p1_difficulty);
            Action action = p1.miniMax_decision_ab();
            if(action.getType() == "stored")
            {
                if (execute_moov(action.getMoovI(0),action.getMoovI(1),action.getMoovI(2)))
                {
                    std::cout << CYAN << "Player 1 placed a " << action.getMoovI(2) << " piece in {" << action.getMoovI(0) << ";" << action.getMoovI(1) << "} case !" << DEFAULT <<std::endl;
                    player[0].play(action.getMoovI(2));
                }
            }
            else
            {
                std::cout << CYAN << "Player 1 mooved a " << action.getMoovI(4) << " piece from {" << action.getMoovI(0) << ";" << action.getMoovI(1) << "} case to {" << action.getMoovI(2) << ";" << action.getMoovI(3) << "} case !" << DEFAULT <<std::endl;
                int temp = map[action.getMoovI(0)][action.getMoovI(1)].getCurrent();
                this->map[action.getMoovI(0)][action.getMoovI(1)].undo_move();
                if (checker())
                {
                    victory = 2;
                    this->display_game();
                    break;
                }
                execute_moov(action.getMoovI(2),action.getMoovI(3), temp);
            }
        }
        else
        {
            std::cout << MAGENTA << "PLAYER 2 MOOV" << DEFAULT << std::endl << std::endl;
            Goof p2 = Goof(*this, 1, p2_difficulty);
            Action action = p2.miniMax_decision_ab();
            if(action.getType() == "stored")
            {
                if (execute_moov(action.getMoovI(0), action.getMoovI(1), (action.getMoovI(2) + 4)))
                {
                    player[1].play(action.getMoovI(2));
                    std::cout << MAGENTA << "Player 2 placed a " << action.getMoovI(2) << " piece in {" << action.getMoovI(0) << ";" << action.getMoovI(1) << "} case !" << DEFAULT <<std::endl;
                }
            }
            else
            {
                std::cout << MAGENTA << "Player 2 mooved a " << temp - 4 << " piece from {" << action.getMoovI(0) << ";" << action.getMoovI(1) << "} case to {" << action.getMoovI(2) << ";" << action.getMoovI(3) << "} case !" << DEFAULT <<std::endl;
                int temp = map[action.getMoovI(0)][action.getMoovI(1)].getCurrent();
                this->map[action.getMoovI(0)][action.getMoovI(1)].undo_move();
                if (checker())
                {
                    victory = 1;
                    this->display_game();
                    break;
                }
                execute_moov(action.getMoovI(2),action.getMoovI(3), temp);
                    
            }
        }
        turn = 1 - turn;
        this->up = 1 - this->up;
        this->display_game();
        sleep(1);
    }
    if (victory == 1)
    {
        std::cout << CYAN << " PLAYER 1 WON ! " << DEFAULT <<  std::endl;
        return (1);
    }
    else
    {
        std::cout << MAGENTA << " PLAYER 2 WON ! " << DEFAULT << std::endl;
        return (2);
    }
}
