#include "core/board.h"
#include "player/human.h"

#include <utility>
#include <iostream>

namespace Player
{

    Human::Human(Core::Color color) : m_color(color) {}

    std::pair<int, int> Human::get_move()
    {
        int x, y;
        std::cin >> x >> y;
        return std::make_pair(x, y);
    }

    Core::Color Human::get_color()
    {
        return m_color;
    }

}; // namespace Player
