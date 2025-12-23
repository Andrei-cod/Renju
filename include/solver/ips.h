#pragma once

#include "core/board.h"

#include <vector>
#include <utility>

namespace AI
{

    struct Patterns
    {
        int TwoInRow;
        int ThreeInRow;
        int FourInRow;
        int FiveInRow;
        int OpenEnd;
        int DoubleThreat;
    };

    /**
     * @brief Класс, реализующий алгоритмы поиска хода для игрового ИИ.
     *
     * Класс содержит методы для генерации возможных ходов, извлечения информации
     * о текущей ситуации на доске и выбора хода с использованием различных
     * алгоритмов поиска (DFS, эвристический поиск).
     */
    class Ips
    {
    private:
        Core::Color m_color; ///< Цвет игрока, за которого играет ИИ.

        /**
         * @brief Поиск хода с использованием алгоритма поиска в глубину (DFS).
         *
         * @param situation Текущая игровая ситуация.
         * @return std::pair<int, int> Координаты выбранного хода.
         */
        std::pair<int, int> minimax(Core::Situation &situation);

        /**
         * @brief Поиск хода с использованием эвристического алгоритма.
         *
         * @param situation Текущая игровая ситуация.
         * @return std::pair<int, int> Координаты выбранного хода.
         */
        std::pair<int, int> heur_find(Core::Situation &situation);

        /**
         * @brief Извлекает все камни с доски в виде вектора координат.
         *
         * @param situation Текущая игровая ситуация.
         * @return std::vector<std::pair<int,int>> Вектор координат всех камней.
         */
        std::vector<std::pair<int, int>> extract_stones(Core::Situation &situation);

        /**
         * @brief Генерирует все возможные ходы на пустые клетки доски.
         *
         * @param situation Текущая игровая ситуация.
         * @return std::vector<std::pair<int,int>> Вектор координат всех возможных ходов.
         */
        std::vector<std::pair<int, int>> generate_moves_base(Core::Situation &situation);

        /**
         * @brief Генерирует "умные" ходы только в окрестности существующих камней.
         *
         * Ходы генерируются только в радиусе 2 клеток от каждого существующего камня.
         * Это уменьшает количество рассматриваемых ходов.
         *
         * @param situation Текущая игровая ситуация.
         * @return std::vector<std::pair<int,int>> Вектор координат "умных" ходов.
         */
        std::vector<std::pair<int, int>> generate_moves_smart(Core::Situation &situation);

        /**
         * @brief Возвращает все камни на доске.
         *
         * @param situation Текущая игровая ситуация.
         * @return std::vector<std::pair<int,int>> Вектор координат всех камней.
         */
        std::vector<std::pair<int, int>> get_stones(Core::Situation &situation);

        /**
         * @brief Анализирует ценность хода опираясь на ситуацию на доске.
         *
         * @param situation Текущая игровая ситуация.
         * @param move Ход который предстоит оценить.
         *
         * @return int Числено выраженное качество позиции.
         * @note Чем больше численное значение, тем ближе ситуация к выигрышу8
         */
        int appraiser(Core::Situation &situation, std::pair<int, int> move, Core::Color color);

        Patterns row_assessment(Core::Situation &situation, std::pair<int, int> move, int dx, int dy, Core::Color color);

        int evaluate_position(Core::Situation &situation, Core::Color color);

        int minimax_recursive(Core::Situation &situation, int depth, bool maximizing_player, Core::Color color);

        std::pair<int, int> heur_find(Core::Situation &situation);

        int alphabeta_recursive(Core::Situation &situation, int depth, int alpha, int beta,
                                bool maximizing_player, Core::Color color);

        std::pair<int, int> alphabeta(Core::Situation &situation);

        void generate_moves_sorted(std::vector<std::pair<int, int>> &moves,
                                     Core::Situation &situation,
                                     Core::Color color,
                                     bool is_maximizing);

    public:
        /**
         * @brief Конструктор класса Ips.
         *
         * @param color Цвет игрока, за которого будет играть ИИ.
         */
        Ips(Core::Color color);

        /**
         * @brief Запрашивает у ИИ ход на основе текущей ситуации.
         *
         * Выбор алгоритма определяется глобальной константой SEARCH_ALGORITHM.
         *
         * @param situation Текущая игровая ситуация.
         * @return std::pair<int, int> — координаты выбранного хода (x, y)
         */
        std::pair<int, int> get_move(Core::Situation &situation);

        /**
         * @brief Возвращает цвет игрока, за которого играет ИИ.
         *
         * @return Core::Color Цвет игрока.
         */
        Core::Color get_color();
    };

} // namespace AI