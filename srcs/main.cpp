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
        Player p1 = init.getPlayer(0);
        Player p2 = init.getPlayer(1);
        init.launch_game_player_versus_ia(1);
        // init.execute_moov(2,0,1);
        // init.PlayerPlay(0,1);
        // init.execute_moov(1,1,6);
        // init.PlayerPlay(1,3);
        // init.execute_moov(0,0,3);
        // init.PlayerPlay(0,3);
        // init.execute_moov(2,0,6);
        // init.PlayerPlay(1,3);
        // init.execute_moov(0,2,2);
        // init.PlayerPlay(0,2);
        // p1.display_moov();
        
        // p2.display_moov();
        // init.getPlayer(0).display_moov();
        // std::cout << std::endl;
        // init.getPlayer(1).display_moov();
        // std::cout << std::endl;
        // Goof test = Goof(init, 1);
        // Action tmp = test.miniMax_decision_ab();
        // if (tmp.getType() == "stored")
        //     std::cout << "Minimax return Action type = " << tmp.getType() << " {" << tmp.getMoovI(0) << ";" << tmp.getMoovI(1) << "}" << "  move to " << tmp.getMoovI(2) << std::endl;
        // else
        // {
        //     std::cout << " Minimax return Action type = " << tmp.getType() << "from  {" << tmp.getMoovI(0) << ";" << tmp.getMoovI(1) << "}" << " move to " << " {" << tmp.getMoovI(2) << ";" << tmp.getMoovI(3) << "}"<< tmp.getMoovI(2) << std::endl;
        // }
        // init.display_game();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    return (0);
}
