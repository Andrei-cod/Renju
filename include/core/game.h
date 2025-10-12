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
        bool f;

    public:
        /**
         * @brief Базовый конструктор класса.
         * Генерирует игру без какой-либо начальной позиции 
         * на поле размером size x size.
         * И с типом игры type(pvp, pve, eve)
         */
        Game(int size, Type type);

        /**
         * @brief Конструктор класс с начальной позицией.
         * Генерирует поле размером size x size, на позициях из вектора white
         * устанавливаются белые камни и черные камни по вектору black соответственно.
         * Также необходимо передать параметр turn показывающий чей ход сейчас
         * 1 - white
         * -1 - black
         */
        Game(int size, std::vector<std::vector<int>> white,
             std::vector<std::vector<int>> black, int turn, Type type);

        /**
         * @brief Функция хода.
         *
         * На позиции (x, y) устанавливается камень, цвет зависит от 
         * очередности(turn).
         * 
         * @param x координата х.
         * @param y координата y.
         * 
         * @return Status Состояние игры.
         * @note в после зода совершает проверку состояния игры
         */
        Status move(int x, int y);

        void win();
        
        void render();

    };

}