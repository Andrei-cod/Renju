#pragma once

#include "core/board.h"

#include <vector>
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

        std::vector<std::pair<int,int>> extract_stones(Core::Situation &situation);

        std::vector<std::pair<int,int>> generate_moves_base(Core::Situation &situation);

        std::vector<std::pair<int,int>> generate_moves_smart(Core::Situation &situation);

        std::vector<std::pair<int,int>> get_stones(Core::Situation &situation);
        

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
