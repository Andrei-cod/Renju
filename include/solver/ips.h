#pragma once

#include "core/board.h"

#include <utility>

namespace AI
{
    class Ips
    {
    private:
        Core::Color m_color;

        std::pair<int, int> bfs(Core::Situation &situation);

        std::pair<int, int> dfs(Core::Situation &situation);

        std::pair<int, int> heur_find(Core::Situation &situation);


    public:
        Ips(Core::Color color);

        /**
         * @brief Запрашивает у игрока ход.
         *
         * @return std::pair<int, int> — координаты выбранного хода (x, y)
         */
        std::pair<int, int> get_move(Core::Situation &situation);

        Core::Color get_color();
    };

} // namespace Player
