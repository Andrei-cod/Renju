#include "solver/ips.h"
#include "core/board.h"
#include "core/constans.h"

#include <utility>
#include <random>   

namespace AI
{
    std::pair<int, int> Ips::bfs(Core::Situation &situation)
    {
        int x, y;
        x = rand() % Core::Constans::FIELD_SIZE;
        y = rand() % Core::Constans::FIELD_SIZE;
        return std::make_pair(x, y);
    }
    std::pair<int, int> Ips::dfs(Core::Situation &situation)
    {
        return std::make_pair(1, 1);
    }
    std::pair<int, int> Ips::heur_find(Core::Situation &situation)
    {
        return std::make_pair(1, 1);
    }

    Ips::Ips(Core::Color color) : m_color(color) {}

    std::pair<int, int> Ips::get_move(Core::Situation &situation)
    {
        switch (Core::Constans::SEARCH_ALGORIMT)
        {
        case 1:
            return dfs(situation);
        case 2:
            return bfs(situation);
        case 3:
            return heur_find(situation);
        }
    }

    Core::Color Ips::get_color()
    {
        return m_color;
    }

} // namespace Player
