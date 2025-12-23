#include "solver/ips.h"
#include "core/board.h"
#include "core/constans.h"

#include <utility>
#include <stdexcept>
#include <random>
#include <set>
#include <algorithm>

namespace AI
{

    Core::Color next_color(Core::Color color)
    {
        return color == Core::Color::Black ? Core::Color::White : Core::Color::Black;
    }
    /**
     * @brief Подсчет итогового веса паттерна.
     * @param pattern Структура с подсчитанными паттернами.
     * @return Суммарный вес позиции.
     */
    int count_impact(Patterns pattern)
    {
        return pattern.TwoInRow * (int)Core::Constants::Heights::TwoInRow +
               pattern.ThreeInRow * (int)Core::Constants::Heights::ThreeInRow +
               pattern.FourInRow * (int)Core::Constants::Heights::FourInRow +
               pattern.FiveInRow * (int)Core::Constants::Heights::FiveInRow +
               pattern.OpenEnd * (int)Core::Constants::Heights::OpenEnd +
               pattern.DoubleThreat * (int)Core::Constants::Heights::DoubleThreat;
    }

    /**
     * @brief Извлекает все камни с доски в виде вектора координат.
     *
     * Проходит по всем клеткам доски и добавляет координаты занятых клеток в вектор.
     *
     * @param situation Текущая игровая ситуация.
     * @return std::vector<std::pair<int, int>> Вектор координат всех камней.
     */
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

    /**
     * @brief Генерирует все возможные ходы на пустые клетки доски.
     *
     * Проходит по всем клеткам доски и добавляет координаты пустых клеток в вектор.
     *
     * @param situation Текущая игровая ситуация.
     * @return std::vector<std::pair<int, int>> Вектор координат всех возможных ходов.
     */
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

        return moves;
    }

    /**
     * @brief Генерирует "умные" ходы только в окрестности существующих камней.
     *
     * Если на доске нет камней, возвращает ход в центр доски.
     * Иначе генерирует ходы в радиусе 2 клеток от каждого существующего камня.
     *
     * @param situation Текущая игровая ситуация.
     * @return std::vector<std::pair<int, int>> Вектор координат "умных" ходов.
     */
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

    /**
     * @brief Оценка текущей ситуации для минимакса
     *
     * @param situation Текущая игровая ситуация
     * @param color Цвет игрока, для которого оцениваем
     * @return int Оценка позиции
     */
    int Ips::evaluate_position(Core::Situation &situation, Core::Color color)
    {
        int total_score = 0;

        for (int i = 0; i < Core::Constants::FIELD_SIZE; i++)
        {
            for (int j = 0; j < Core::Constants::FIELD_SIZE; j++)
            {
                if (situation.is_empty(i, j))
                {

                    total_score += appraiser(situation, {i, j}, color);

                    total_score -= appraiser(situation, {i, j}, next_color(color));
                }
            }
        }

        return total_score;
    }

    /**
     * @brief Рекурсивная часть минимаксного алгоритма
     *
     * @param situation Текущая игровая ситуация (будет изменяться и восстанавливаться)
     * @param depth Текущая глубина поиска
     * @param maximizing_player Истина, если это ход максимизирующего игрока (наш ИИ)
     * @param color Цвет текущего игрока
     * @return int Оценка позиции
     */
    int Ips::minimax_recursive(Core::Situation &situation, int depth, bool maximizing_player, Core::Color color)
    {

        if (depth == 0)
        {
            return evaluate_position(situation, m_color);
        }

        std::vector<std::pair<int, int>> moves = generate_moves_smart(situation);

        if (moves.empty())
        {
            return evaluate_position(situation, m_color);
        }

        if (maximizing_player)
        {

            int best_score = std::numeric_limits<int>::min();

            for (size_t i = 0; i < moves.size(); i++)
            {
                std::pair<int, int> move = moves[i];

                situation.move(move.first, move.second, color);

                int score = minimax_recursive(situation, depth - 1, false, next_color(color));

                situation.un_move();

                if (score > best_score)
                {
                    best_score = score;
                }
            }

            return best_score;
        }
        else
        {
            int best_score = std::numeric_limits<int>::max();

            for (size_t i = 0; i < moves.size(); i++)
            {
                std::pair<int, int> move = moves[i];

                situation.move(move.first, move.second, color);

                int score = minimax_recursive(situation, depth - 1, true, next_color(color));

                situation.un_move();

                if (score < best_score)
                {
                    best_score = score;
                }
            }

            return best_score;
        }
    }

    /**
     * @brief Минимаксный алгоритм для поиска лучшего хода
     *
     * @param situation Текущая игровая ситуация
     * @return std::pair<int, int> Координаты лучшего хода
     */
    std::pair<int, int> Ips::minimax(Core::Situation &situation)
    {
        std::vector<std::pair<int, int>> moves = generate_moves_smart(situation);

        if (moves.empty())
        {
            return {-1, -1};
        }

        std::pair<int, int> best_move = moves[0];
        int best_score = std::numeric_limits<int>::min();

        for (size_t i = 0; i < moves.size(); i++)
        {
            std::pair<int, int> move = moves[i];

            situation.move(move.first, move.second, m_color);

            int score = minimax_recursive(situation, Core::Constants::MAX_SEARCH_DEPTH - 1, false, next_color(m_color));

            situation.un_move();

            if (score > best_score)
            {
                best_score = score;
                best_move = move;
            }
        }

        return best_move;
    }
    /**
     * @brief Поиск хода с использованием эвристического алгоритма.
     *
     * В текущей реализации возвращает фиксированный ход (1,1).
     *
     * @param situation Текущая игровая ситуация.
     * @return std::pair<int, int> Координаты хода (1,1).
     */
    std::pair<int, int> Ips::heur_find(Core::Situation &situation)
    {

        std::vector<std::pair<int, int>> moves = generate_moves_smart(situation);
        std::pair<int, int> best_move = moves[0];
        int max_score = std::numeric_limits<int>::min();

        Core::Color color = get_color();

        for (auto &move : moves)
        {
            int my_score = appraiser(situation, move, color);

            int opponent_score = appraiser(situation, move, next_color(color));

            int score = my_score - opponent_score;
            if (score > max_score)
            {
                max_score = score;
                best_move = move;
            }
        }

        return best_move;
    }

    /**
     * @brief Рекурсивный альфа-бета с отсечениями.
     * @param situation Ситуация (изменяется в процессе поиска).
     * @param depth Глубина поиска.
     * @param alpha Нижняя граница для отсечений.
     * @param beta Верхняя граница для отсечений.
     * @param maximizing_player Флаг максимизирующего игрока.
     * @param color Цвет текущего игрока.
     * @return Лучшая оценка для текущей ветви.
     */

    int Ips::alphabeta_recursive(Core::Situation &situation, int depth, int alpha, int beta,
                                 bool maximizing_player, Core::Color color)
    {
        if (depth == 0)
        {
            return evaluate_position(situation, color);
        }

        std::vector<std::pair<int, int>> moves = generate_moves_smart(situation);

        generate_moves_sorted(moves, situation, color, maximizing_player);

        if (moves.empty())
        {
            return evaluate_position(situation, color);
        }

        if (maximizing_player)
        {
            int best_score = std::numeric_limits<int>::min();

            for (const auto &move : moves)
            {
                situation.move(move.first, move.second, color);

                int score = alphabeta_recursive(situation, depth - 1, alpha, beta,
                                                false, next_color(color));

                situation.un_move();

                best_score = std::max(best_score, score);
                alpha = std::max(alpha, best_score);

                if (beta <= alpha)
                {
                    break;
                }
            }

            return best_score;
        }
        else
        {
            int best_score = std::numeric_limits<int>::max();

            for (const auto &move : moves)
            {
                situation.move(move.first, move.second, color);

                int score = alphabeta_recursive(situation, depth - 1, alpha, beta,
                                                true, next_color(color));

                situation.un_move();

                best_score = std::min(best_score, score);
                beta = std::min(beta, best_score);

                if (beta <= alpha)
                {
                    break;
                }
            }

            return best_score;
        }
    }

    /**
     * @brief Полный альфа-бета с выбором лучшего хода.
     * @param situation Текущая игровая ситуация.
     * @return Координаты лучшего хода.
     */
    std::pair<int, int> Ips::alphabeta(Core::Situation &situation)
    {
        std::vector<std::pair<int, int>> moves = generate_moves_smart(situation);

        if (moves.empty())
        {
            return {-1, -1};
        }

        generate_moves_sorted(moves, situation, m_color, true);

        std::pair<int, int> best_move = moves[0];
        int best_score = std::numeric_limits<int>::min();
        int alpha = std::numeric_limits<int>::min();
        int beta = std::numeric_limits<int>::max();

        for (const auto &move : moves)
        {
            situation.move(move.first, move.second, m_color);

            int score = alphabeta_recursive(situation,
                                            Core::Constants::MAX_SEARCH_DEPTH - 1,
                                            alpha, beta, false, next_color(m_color));

            situation.un_move();

            if (score > best_score)
            {
                best_score = score;
                best_move = move;
                alpha = std::max(alpha, best_score);
            }
        }

        return best_move;
    }

    /**
     * @brief Сортировка ходов для оптимизации альфа-бета отсечений.
     * @param moves Вектор ходов для сортировки.
     * @param situation Текущая игровая ситуация.
     * @param color Цвет игрока для оценки.
     * @param is_maximizing Флаг типа игрока.
     */
    void Ips::generate_moves_sorted(std::vector<std::pair<int, int>> &moves,
                                    Core::Situation &situation,
                                    Core::Color color,
                                    bool is_maximizing)
    {
        if (moves.empty())
            return;

        std::vector<std::pair<int, std::pair<int, int>>> scored_moves;
        scored_moves.reserve(moves.size());

        for (const auto &move : moves)
        {
            int score = appraiser(situation, move, color);
            scored_moves.emplace_back(score, move);
        }

        if (is_maximizing)
        {
            std::sort(scored_moves.begin(), scored_moves.end(),
                      [](const auto &a, const auto &b)
                      {
                          return a.first > b.first;
                      });
        }
        else
        {
            std::sort(scored_moves.begin(), scored_moves.end(),
                      [](const auto &a, const auto &b)
                      {
                          return a.first < b.first;
                      });
        }

        for (size_t i = 0; i < scored_moves.size(); ++i)
        {
            moves[i] = scored_moves[i].second;
        }
    }

    /**
     * @brief Конструктор класса Ips.
     *
     * @param color Цвет игрока, за которого будет играть ИИ.
     */
    Ips::Ips(Core::Color color) : m_color(color) {}

    /**
     * @brief Запрашивает у ИИ ход на основе текущей ситуации.
     *
     * Выбор алгоритма определяется глобальной константой SEARCH_ALGORITHM.
     *
     * @param situation Текущая игровая ситуация.
     * @return std::pair<int, int> — координаты выбранного хода (x, y)
     */
    std::pair<int, int> Ips::get_move(Core::Situation &situation)
    {
        using namespace Core::Constants;

        switch (Core::Constants::SEARCH_ALGORIMT)
        {
        case SearchAlgo::Minimax:
            return minimax(situation);
        case SearchAlgo::Heuristic:
            return heur_find(situation);
        case SearchAlgo::AlphaBeta:
            return alphabeta(situation);
        default:
            return minimax(situation);
        }
    }

    /**
     * @brief Возвращает цвет игрока, за которого играет ИИ.
     *
     * @return Core::Color Цвет игрока.
     */
    Core::Color Ips::get_color()
    {
        return m_color;
    }
    /**
     * @brief Быстрая оценка одного хода (аппрайзер).
     * @param situation Текущая игровая ситуация.
     * @param move Оцениваемый ход.
     * @param color Цвет игрока.
     * @return Оценка качества хода.
     */
    int Ips::appraiser(Core::Situation &situation, std::pair<int, int> move, Core::Color color)
    {
        int move_impact = 0;

        const int directions[4][2] = {
            {1, 0}, // горизонталь
            {0, 1}, // вертикаль
            {1, 1}, // диагональ верх лево -> право низ
            {-1, 1} // диагональ другая
        };

        for (const auto &dir : directions)
        {
            AI::Patterns friends_patterns, opponents_patterns;

            friends_patterns = row_assessment(situation, move, dir[0], dir[1], color);
            opponents_patterns = row_assessment(situation, move, dir[0], dir[1], next_color(color));
            move_impact += count_impact(friends_patterns) - count_impact(opponents_patterns);
        }

        return move_impact;
    }
    /**
     * @brief Анализ линии из 9 клеток для обнаружения паттернов.
     * @param situation Текущая игровая ситуация.
     * @param move Центральная клетка для анализа.
     * @param dx Направление по X.
     * @param dy Направление по Y.
     * @param color Цвет анализируемых камней.
     * @return Структура с найденными паттернами.
     */
    Patterns Ips::row_assessment(Core::Situation &situation,
                                 std::pair<int, int> move, int dx, int dy,
                                 Core::Color color)
    {
        Patterns result;

        int x = move.first;
        int y = move.second;
        int streak = 0;

        for (int offset = -4; offset <= 4; offset++)
        {
            Core::Stone stone;
            int nx = x + dx * offset;
            int ny = y + dy * offset;

            try
            {
                stone = situation.get_stone(nx, ny);
            }
            catch (const std::out_of_range &stone)
            {
                continue;
            }

            if (stone.get_color() == color)
            {
                streak++;
            }
            else
            {
                switch (streak)
                {
                case 0:
                case 1:
                    break;
                case 2:
                    result.TwoInRow++;
                    break;
                case 3:
                    result.ThreeInRow++;
                    break;
                case 4:
                    result.FourInRow++;
                    break;
                default:
                    result.FiveInRow++;
                    break;
                }
                streak = 0;
            }
        }

        return result;
    }

} // namespace AI