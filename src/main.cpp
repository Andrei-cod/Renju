/**
*   @project: Renju
*   @brief: Traditional 5-in-a-row board game implementation
*
*   @author: Гущин Андрей Владимирович(Github: Andrei-cod)
*   @date: 2025
*   @version: 0.05
*/


#include "core/board.h"
#include "utils/render.h"
#include <iostream>

int main() {
    Core::Situation board(3);

    int q = 1;
    bool f;

    while (true) {
        Utils::Render::very_simple_draw(board);
        
        int x, y;
        std::cin >> x >> y;
        if (q > 0)
        {
            f = board.move(x-1, y-1, Core::Color::White);
        } else {
            f = board.move(x-1, y-1, Core::Color::Black);
        }
        if (f){
            q*=-1;
        }
    }
}