#pragma once

#include <vector>
#include <string>

class Action
{
    private:
        std::string type;
        std::vector<int> moovs;
        Action();

    public:
        Action(int x1, int y1, int piece);
        Action(int x1, int y1, int x2, int y2, int piece);
        ~Action();
        int getMoovI(int idx);
        std::string getType();
};