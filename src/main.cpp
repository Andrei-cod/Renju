#include "core/board.h"
#include "utils/render.h"
#include <iostream>

int main() {
    Core::Board board(3);

    int q = 1;
    bool f;

    while (true) {
        Utils::Render::very_simple_draw(board);
        
        int x, y;
        std::cin >> x >> y;
        if (q > 0)
        {
            f = board.move(x, y, Core::Color::White);
        } else {
            f = board.move(x, y, Core::Color::Black);
        }
        if (f){
            q*=-1;
        }
    }
}