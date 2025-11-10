#pragma once

namespace Core::Constants
{
    inline constexpr int MAX_SEARCH_DEPTH = 3;

    enum class SearchAlgo
    {
        DepthFirst = 1,
        BreadthFirst = 2,
        Heuristic = 3
    };

    inline constexpr SearchAlgo SEARCH_ALGORIMT = SearchAlgo::BreadthFirst;

    inline constexpr int FIELD_SIZE = 9;
} // namespace Core::Constants
