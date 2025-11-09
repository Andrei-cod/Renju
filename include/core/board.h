#pragma once
#include "stone.h"

#include <vector>
#include <deque>
#include <optional>

namespace Core
{
    /**
     * @brief Исход игры.
     */
    enum Status
    {
        white_wins,
        black_wins,
        draw,
        game_end,
        ongoing
    };
    /**
     * @brief Класс для хранения ситуации на игровом поле.
     *
     * Класс хранит в себе состояние игрового поля и информацию о позиции каждого камня.
     *
     * Функционал:
     * - Ход (move) - изменение состояния доски добавлением нового камня.
     * - Получение цвета конкретного камня по координатам (get_stone_color).
     *
     * @note В реализации поле представлено в виде двумерного вектора, хранящего объекты класса Stone.
     */
    class Situation
    {
    private:
        int m_size;
        int m_draw_counter;
        std::vector<std::vector<Stone>> m_stones;
        std::deque<std::pair<int, int>> last_move;

    public:
        /**
         * @brief Создает объект класса Situation размером size x size.
         *
         * Создает пустое игровое поле, инициализировав все камни значением Color::None.
         *
         * @param size Размер создаваемого поля.
         */
        Situation(int size);

        /**
         * @brief Создает объект класса Situation размером size x size(не конструктор).
         *
         * Создает непустое игровое поле:
         * по координатам из массива white устанавливаются белые камни,
         * по координатам из массива black устанавливаются черные камни.
         *
         * @param size Размер создаваемого поля.
         * @param white Вектор координат белых камней. Координаты начинаются с 0.
         * @param black Вектор координат черных камней. Координаты начинаются с 0.
         *
         * @return Объект класса Situation или nullptr в случае если партия уже
         * завершена.
         */
        static std::optional<Situation> create_from_template(
            int size,
            std::vector<std::vector<int>> white,
            std::vector<std::vector<int>> black);

        /**
         * @brief Ставит камень цвета color на позицию (x, y).
         *
         * @param x Координата x. Координаты начинаются с 0.
         * @param y Координата y. Координаты начинаются с 0.
         * @param color Цвет устанавливаемого камня.
         *
         * @return true Если ход успешно совершен (клетка пуста и существует).
         * @return false Если координаты не принадлежат полю размера size или клетка уже занята.
         */
        bool move(int x, int y, Color color);

        /**
         * @brief Отменяет последний выполненный ход.
         *
         * @return true Если отмена возможна.
         * @return false Если нет ходов для отмены.
         */
        bool un_move();

        /**
         * @brief Возвращает размер поля.
         *
         * @return int Размер поля.
         */
        int get_size();

        /**
         * @brief Возвращает цвет камня в указанной клетке.
         *
         * @param x Координата x. Координаты начинаются с 0.
         * @param y Координата y. Координаты начинаются с 0.
         *
         * @return Color Цвет камня по координатам (x, y).
         */
        Color get_stone_color(int x, int y);

        /**
         * @brief Функция проверки состояния игры
         *
         * Проверяет не завершилась ли игра,
         * Если да, то возвращает одну из трех концовок:
         *  1 - игра завершилась победой
         *  2 - ничья
         * Иначе:
         *  0 - игра продолжается
         *
         * @param x координата х.
         * @param y координата y.
         *
         * @return int Состояние игры.
         *
         * @note Проверка происходит относительно, поставленного только что камня.
         */
        int check_win(int x, int y);

        /**
         * @brief Функция проверки состояния игры
         *
         * Проверяет введнную комбинацию, не является ли та уже завершенным матчем.
         *
         * 1 - Игра уже завершена
         * 0 - Партию можно продолжить
         *
         * @return int Результат игры.
         *
         * @note Проверка всего поля.
         */

        int check_win();

        /**
         * @brief Проверяет, находятся ли координаты в пределах игрового поля.
         *
         * @param x Координата X.
         * @param y Координата Y.
         * @return true Если координаты допустимы.
         * @return false Если координаты выходят за границы.
         */

        bool is_within_bounds(int x, int y) const;

        /**
         * @brief Проверяет наличие последовательности из пяти камней подряд.
         *
         * @param x Начальная координата X.
         * @param y Начальная координата Y.
         * @param dx Направление по оси X.
         * @param dy Направление по оси Y.
         * @param base_color Цвет, который проверяется.
         * @return true Если найдена выигрышная комбинация.
         * @return false Если пять камней подряд отсутствуют.
         */

        bool has_five_in_a_row(int x, int y, int dx, int dy, Color base_color) const;

        bool setup_board(std::vector<std::vector<int>> white,
                         std::vector<std::vector<int>> black);
    };

} // namespace Core