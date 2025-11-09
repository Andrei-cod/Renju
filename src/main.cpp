/**
 *   @project: Renju
 *   @brief: Traditional 5-in-a-row board game implementation
 *
 *   @author: Гущин Андрей Владимирович(Github: Andrei-cod)
 *   @date: 2025
 *   @version: 0.2
 */

#include "core/game.h"
#include "utils/render.h"
#include "core/constans.h"
#include "core/board.h"

#include <iostream>


int main()
{

    Core::Game game(Core::Situation(Core::Constans::FIELD_SIZE), Core::Type::pve);
    game.run();
/*
    Core::Status f = Core::ongoing;

    while (true)
    {
        if (f == Core::ongoing)
        {
            game.render();
        }else{
            return 0;
        }

        int x, y;
        std::cin >> x >> y;

        f = game.move(x, y);
    }
    */

}