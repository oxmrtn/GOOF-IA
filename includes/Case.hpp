#pragma once

#include <iostream>
#include <string>

class Case
{
    private:
        int tab[3];
        int latest;
    public:
        Case();
        ~Case();
        int getCurrent();
        void    setCase(int value);
};