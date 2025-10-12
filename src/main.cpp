/**
 *   @project: Renju
 *   @brief: Traditional 5-in-a-row board game implementation
 *
 *   @author: Гущин Андрей Владимирович(Github: Andrei-cod)
 *   @date: 2025
 *   @version: 0.1
 */

#include "core/game.h"
#include "utils/render.h"
#include <iostream>

int main()
{
    Core::Game game (3, Core::Type::pve);

    Core::Status f;

    while (true)
    {
        game.render();

        int x, y;
        std::cin >> x >> y;

        f = game.move(x, y);

        switch (f)
        {
        case Core::Status::white_wins:
            return 0;
        case Core::Status::black_wins:
            return 0;
        case Core::Status::draw:
            return 0;
        }
    }
    return 0;
}