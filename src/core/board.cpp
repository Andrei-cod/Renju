#include "core/board.h"
#include "core/stone.h"

#include <vector>

namespace Core
{
    Board::Board(int size1){
        size = size1;
        stones = std::vector<std::vector<Stone>>(size, std::vector<Stone>(size));
    }
    bool Board::move(int x, int y, Color color){
        if (stones[y-1][x-1].get_color() != Color::None) {
            return false;
        }
        stones[y-1][x-1].set_color(color);
        return true;
    }
    int Board::get_size(){
        return size;
    }
    Color Board::get_stone_color(int x, int y){
        return stones[x][y].get_color();
    }

} // namespace Core
