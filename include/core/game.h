#pragma once

#include "board.h"
#include "utils/render.h"
#include "player/player.h"

namespace Core
{

    /**
     * @brief Режимы игры.
     */
    enum Type
    {
        pvp,
        pve,
        eve
    };
    struct MoveResult
    {
        bool valid;
        Status status;
        std::optional<Color> winner;

        static MoveResult invalid()
        {
            return {false, Status::ongoing, std::nullopt};
        }

        static MoveResult ongoing()
        {
            return {true, Status::ongoing, std::nullopt};
        }

        static MoveResult win(Color winner)
        {
            return {true, Status::game_end, winner};
        }

        static MoveResult draw()
        {
            return {true, Status::game_end, std::nullopt};
        }
    };

    /**
     * @brief Класс отвечающий за координацию игрового процесса
     * Этот класс работает с классами Board, Player и Render.
     * А также следит за сосотянием игры и оповещает в случае ее завершения.
     *
     * Функционал:
     * - Ход(move) - функция хода по координатам автоматически следящая
     * за очередностью хода.
     * - Проверка состояния(check_state) - функция проверяющее состояние игры.
     *
     * @note Также класс поддержиивает три типа игры:
     * игрок против игрока(pvp)
     * игрок против компьютера(pve)
     * компьютер против компьютера(eve)
     */

    class Game
    {
    private:
        int m_size;
        int m_turn; // очередность хода 1 - white, -1 - black
        Type m_type;
        Situation m_situation;
        bool m_is_valid_move;

        

    public:
        /**
         * @brief Базовый конструктор класса.
         * Генерирует игру без какой-либо начальной позиции
         * на поле размером size x size.
         * И с типом игры type(pvp, pve, eve)
         */
        Game(Core::Situation board, Type type);

        /**
         * @brief Конструктор класс с начальной позицией.
         * Генерирует поле размером size x size, на позициях из вектора white
         * устанавливаются белые камни и черные камни по вектору black соответственно.
         * Также необходимо передать параметр turn показывающий чей ход сейчас
         * 1 - white
         * -1 - black
         */
        Game(Core::Situation board, Type type, int turn);

        /**
         * @brief Функция хода.
         *
         * На позиции (x, y) устанавливается камень, цвет зависит от
         * очередности(turn).
         *
         * @param x координата х.
         * @param y координата y.
         *
         * @return MoveResult Состояние игры.
         * @note в после зода совершает проверку состояния игры
         */
        MoveResult move(int x, int y);

        /**
         * @brief Функция связи с классом отрисовки
         *
         * Просто передает ситуацию отрисовке
         */
        void render();

        /**
         * @brief Запуск основного цикла игры
         */
        void run();
    };

}