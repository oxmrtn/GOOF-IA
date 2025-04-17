#pragma once

#include <iostream>
#include <string>
#include "./Game.hpp"

class Case
{
    private:
        int tab[4];
        int latest;
    public:
        Case();
        ~Case();
        int     getCurrent( void );
        void    setCase( int value );
        void    undo_move( void );
        bool    space_on_case( void );
        bool    is_allowed( int value );
};