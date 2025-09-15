#pragma once

#include "board.h"
#include "utils/render.h"
#include "player/player.h"

namespace Core{

    enum Type{pvp, pve, eve};

    class Game
    {
    private:
        int size;
        Type type;
    public:
        Game(int size, Type type);
        
        void move(int x, int y);
        
    };
    
}