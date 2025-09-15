#pragma once

#include <vector>

#include "stone.h"

namespace Core
{

    class Board
    {
    private:
        int size;
        std::vector<std::vector<Stone>> stones;

    public:
        Board(int size);

        bool move(int x, int y, Color color);
        int get_size();
        Color get_stone_color(int x, int y);
    };

} // namespace Core