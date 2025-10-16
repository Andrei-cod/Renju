#include "core/board.h"
#include "core/stone.h"
#include "core/constans.h"
#include "utils/render.h"

#include "string"
#include <vector>

namespace Core
{

    /**
     * @brief Реализация конструктора пустой доски.
     *
     * Инициализирует двумерный вектор размером m_size x m_size,
     * где каждый элемент по умолчанию имеет цвет Color::None.
     */
    Situation::Situation(int size)
    {
        m_size = size;
        m_draw_counter = size * size;
        m_stones = std::vector<std::vector<Stone>>(m_size, std::vector<Stone>(m_size));
    }

    /**
     * @brief Реализация конструктора доски с предустановленными камнями.
     *
     * Обрабатывает два массива координат для расстановки белых и черных камней.
     * Выполняются проверки на валидность координат для предотвращения выхода
     * за границы массива.
     *
     * @note После расстановки камней проверяет, не является ли позиция
     * уже завершённой (победной или ничейной).
     */
    Situation::Situation(int size, std::vector<std::vector<int>> white,
                         std::vector<std::vector<int>> black)
    {
        m_size = size;
        m_draw_counter = size * size;
        m_stones = std::vector<std::vector<Stone>>(m_size, std::vector<Stone>(m_size));
        for (auto &&pos : white)
        {
            if (pos.size() >= 2)
            {
                int x = pos[0];
                int y = pos[1];

                if (x >= 0 && x < m_size && y >= 0 && y < m_size)
                {
                    m_stones[y][x].set_color(Color::White);
                    m_draw_counter--;
                }
            }
        }

        for (auto &&pos : black)
        {
            if (pos.size() >= 2)
            {
                int x = pos[0];
                int y = pos[1];

                if (x >= 0 && x < m_size && y >= 0 && y < m_size)
                {
                    m_stones[y][x].set_color(Color::Black);
                    m_draw_counter--;
                }
            }
        }
        if (check_win())
        {
            Utils::Render::mess((std::string) "Это уже завершенная партия.");
        }
    }

    /**
     * @brief Реализация установки камня на доску.
     *
     * Проверяет:
     * 1. Что клетка пуста (Color::None)
     * 2. Что координаты не выходят за границы доски
     */
    bool Situation::move(int x, int y, Color color)
    {
        if (x < 0 || y < 0 || x >= m_size || y >= m_size || m_stones[y][x].get_color() != Color::None)
        {
            return false;
        }
        m_stones[y][x].set_color(color);
        m_draw_counter -= 1;
        last_move.push_back({x, y});
        if (last_move.size() > Constans::MAX_SEARCH_DEPTH)
        {
            last_move.pop_front();
        }

        return true;
    }

    /**
     * @brief Отменяет последний совершённый ход.
     *
     * Если в списке последних ходов есть хотя бы один элемент — снимает камень
     * с доски и восстанавливает предыдущее состояние.
     *
     * @return true — если отмена возможна;
     * @return false — если история ходов пуста.
     */
    bool Situation::un_move()
    {
        if (!last_move.size())
        {
            return false;
        }
        auto [x, y] = last_move.back();
        last_move.pop_back();
        m_stones[x][y].set_color(None);
        return true;
    }

    /**
     * @brief Реализация получения размера доски.
     *
     * @return Текущий размер доски (одна сторона квадратного поля)
     */
    int Situation::get_size()
    {
        return m_size;
    }

    /**
     * @brief Реализация получения цвета камня.
     *
     * @warning Не выполняет проверку границ - ответственность на вызывающей стороне.
     */
    Color Situation::get_stone_color(int x, int y)
    {
        return m_stones[y][x].get_color();
    }

    /**
     * @brief Функция, проверяющая статус игры
     *
     * Проверяет, завершилась ли игра победой или ничьей
     * после последнего хода (x, y). Победа — это пять
     * одинаковых камней подряд в одном из четырёх направлений.
     *
     * @param x X-координата последнего поставленного камня
     * @param y Y-координата последнего поставленного камня
     * @return int Статус игры:
     *   0 — игра продолжается
     *   1 — победа
     *   2 — ничья (все клетки заняты)
     */
    int Situation::check_win(int x, int y)
    {
        if (m_draw_counter <= 0)
            return 2; // ничья

        const Color base_color = m_stones[y][x].get_color();

        const int directions[4][2] = {
            {1, 0}, // горизонталь
            {0, 1}, // вертикаль
            {1, 1}, // диагональ верх лево -> право низ
            {-1, 1} // диагональ другая
        };

        for (const auto &dir : directions)
        {
            if (has_five_in_a_row(x, y, dir[0], dir[1], base_color))
                return 1; // победа
        }

        return 0; // игра продолжается
    }

    /**
     * @brief Проверяет текущее состояние всей доски.
     *
     * @return int:
     * - 1 — победа;
     * - 0 — игра продолжается.
     *
     * @note Используется при инициализации или отладке партий.
     */
    int Situation::check_win()
    {
        const int directions[4][2] = {
            {1, 0}, {0, 1}, {1, 1}, {-1, 1}};

        for (int y = 0; y < m_size; ++y)
        {
            for (int x = 0; x < m_size; ++x)
            {
                Color base_color = m_stones[y][x].get_color();

                if (base_color == Color::None)
                    continue;

                for (const auto &dir : directions)
                {
                    int streak = 0;

                    for (int offset = 0; offset < 5; ++offset)
                    {
                        int nx = x + dir[0] * offset;
                        int ny = y + dir[1] * offset;

                        if (nx < 0 || ny < 0 || nx >= m_size || ny >= m_size)
                            break;

                        if (m_stones[ny][nx].get_color() == base_color)
                        {
                            ++streak;
                        }
                        else
                        {
                            break;
                        }
                    }

                    if (streak == 5)
                        return 1;
                }
            }
        }

        return 0;
    }

    /**
     * @brief Проверяет, находятся ли координаты в пределах игрового поля
     *
     * @param x X-координата
     * @param y Y-координата
     * @return true — координаты в пределах поля
     */
    bool Situation::is_within_bounds(int x, int y) const
    {
        return x >= 0 && y >= 0 && x < m_size && y < m_size;
    }

    /**
     * @brief Проверяет, есть ли пять подряд по заданному направлению
     *
     * @param x X-координата центра (последнего хода)
     * @param y Y-координата центра (последнего хода)
     * @param dx Смещение по X (направление)
     * @param dy Смещение по Y (направление)
     * @param base_color Цвет, который должен повторяться
     * @return true — есть пять подряд
     */
    bool Situation::has_five_in_a_row(int x, int y, int dx, int dy, Color base_color) const
    {
        int streak = 0;

        for (int offset = -4; offset <= 4; offset++)
        {
            int nx = x + dx * offset;
            int ny = y + dy * offset;

            if (!is_within_bounds(nx, ny))
            {
                streak = 0;
                continue;
            }

            if (m_stones[ny][nx].get_color() == base_color)
            {
                streak++;
                if (streak >= 5)
                    return true;
            }
            else
            {
                streak = 0;
            }
        }

        return false;
    }

} // namespace Core