#pragma once

#include <iostream>
#include <string>
#include "./enum.hpp"


class Case
{
    private:
        int tab[4];
        int latest;
    public:
        Case();
        Case(const Case& other);
        ~Case();
        int     getCurrent( void );
        void    setCase( int value );
        void    undo_move( void );
        bool    space_on_case( void );
        bool    is_allowed( int value );
};