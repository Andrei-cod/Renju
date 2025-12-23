#pragma once

namespace Core::Constants
{
    inline constexpr int MAX_SEARCH_DEPTH = 3;

    enum class Heights
    {
        TwoInRow     = 10,
        ThreeInRow   = 100,
        FourInRow    = 1000,
        FiveInRow    = 10000000, // Победа
        OpenEnd      = 5,      // Бонус за каждый открытый конец
        DoubleThreat = 50
    };

    enum class SearchAlgo
    {
        Minimax = 1,
        Alphabeta = 2,
        Heuristic = 3,
        AlphaBeta = 4
    };

    inline constexpr SearchAlgo SEARCH_ALGORIMT = SearchAlgo::Minimax;

    inline constexpr int FIELD_SIZE = 9;
} // namespace Core::Constants
