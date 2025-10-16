#pragma once

#include "core/board.h"

#include <utility>

namespace Player
{
    class Human
    {
    private:
        Core::Color m_color;

    public:
        Human(Core::Color color);

        /**
         * @brief Запрашивает у игрока ход.
         *
         * @return std::pair<int, int> — координаты выбранного хода (x, y)
         */
        std::pair<int, int> get_move();

        Core::Color get_color();
    };

} // namespace Player
