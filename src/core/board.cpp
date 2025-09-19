#include "core/board.h"
#include "core/stone.h"

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
        m_stones = std::vector<std::vector<Stone>>(m_size, std::vector<Stone>(m_size));
    }

    /**
     * @brief Реализация конструктора доски с предустановленными камнями.
     * 
     * Обрабатывает два массива координат для расстановки белых и черных камней.
     * Координаты преобразуются из 1-indexed (пользовательский формат) в 0-indexed (внутренний формат).
     * Выполняются проверки на валидность координат для предотвращения выхода за границы массива.
     */
    Situation::Situation(int size, std::vector<std::vector<int>> white, std::vector<std::vector<int>> black)
    {
        m_size = size;
        m_stones = std::vector<std::vector<Stone>>(m_size, std::vector<Stone>(m_size));
        for (auto &&pos : white)
        {
            if (pos.size() >= 2)
            {
                int x = pos[0] - 1;
                int y = pos[1] - 1;

                if (x >= 0 && x < m_size && y >= 0 && y < m_size)
                {
                    m_stones[y][x].set_color(Color::White);
                }
            }
        }

        for (auto &&pos : black)
        {
            if (pos.size() >= 2)
            {
                int x = pos[0] - 1;
                int y = pos[1] - 1;

                if (x >= 0 && x < m_size && y >= 0 && y < m_size)
                {
                    m_stones[y][x].set_color(Color::Black);
                }
            }
        }
    }

    /**
     * @brief Реализация установки камня на доску.
     * 
     * Проверяет:
     * 1. Что клетка пуста (Color::None)
     * 2. Что координаты не выходят за границы доски
     * 
     * @note Координаты преобразуются из 1-indexed в 0-indexed
     */
    bool Situation::move(int x, int y, Color color)
    {
        if (m_stones[y - 1][x - 1].get_color() != Color::None || y - 1 > m_size || x - 1 > m_size)
        {
            return false;
        }
        m_stones[y - 1][x - 1].set_color(color);
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

} // namespace Core
