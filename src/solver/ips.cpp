#include "solver/ips.h"
#include "core/board.h"
#include "core/constans.h"

#include <utility>
#include <random>
#include <set>

namespace AI
{
    std::vector<std::pair<int, int>> Ips::extract_stones(Core::Situation &situation)
    {
        std::vector<std::pair<int, int>> stones;

        for (int i = 0; i < Core::Constants::FIELD_SIZE; ++i)
        {
            for (int j = 0; j < Core::Constants::FIELD_SIZE; ++j)
            {
                if (!situation.is_empty(i, j))
                {
                    stones.emplace_back(i, j);
                }
            }
        }

        return stones;
    }

    std::vector<std::pair<int, int>> Ips::generate_moves_base(Core::Situation &situation)
    {
        std::vector<std::pair<int, int>> moves;

        for (int i = 0; i < Core::Constants::FIELD_SIZE; i++)
        {
            for (int j = 0; j < Core::Constants::FIELD_SIZE; j++)
            {
                if (situation.is_within_bounds(i, j) && situation.is_empty(i, j))
                {
                    moves.push_back(std::pair<int, int>(i, j));
                }
            }
        }
    }

    std::vector<std::pair<int, int>> Ips::generate_moves_smart(Core::Situation &situation)
    {
        std::vector<std::pair<int, int>> moves;

        const auto &stones = extract_stones(situation);
        if (stones.empty())
        {
            return {{(int)(Core::Constants::FIELD_SIZE / 2),
                     (int)(Core::Constants::FIELD_SIZE / 2)}};
        }

        std::set<std::pair<int, int>> unique_moves;

        for (const auto &stone : stones)
        {
            for (int dx = -2; dx <= 2; ++dx)
            {
                for (int dy = -2; dy <= 2; ++dy)
                {
                    int x = stone.first + dx;
                    int y = stone.second + dy;

                    if (situation.is_within_bounds(x, y) && situation.is_empty(x, y))
                    {
                        unique_moves.emplace(x, y);
                    }
                }
            }
        }

        moves.assign(unique_moves.begin(), unique_moves.end());
        return moves;
    }

    std::pair<int, int> Ips::bfs(Core::Situation &situation)
    {
        int x, y;
        x = rand() % Core::Constants::FIELD_SIZE;
        y = rand() % Core::Constants::FIELD_SIZE;
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
        using namespace Core::Constants;

        switch (Core::Constants::SEARCH_ALGORIMT)
        {
        case SearchAlgo::DepthFirst:
            return dfs(situation);
        case SearchAlgo::BreadthFirst:
            return bfs(situation);
        case SearchAlgo::Heuristic:
            return heur_find(situation);
        }
    }

    Core::Color Ips::get_color()
    {
        return m_color;
    }

} // namespace Player
