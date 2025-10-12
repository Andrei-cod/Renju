#pragma once
#include "core/board.h"

#include "string"

namespace Utils
{

    /**
     * @brief Класс, ответственный за отрисовку
     */
    class Render
    {
    private:
    public:
        /**
         * @brief Функция отрисовки доски в консоли
         *
         * @param board состояние поля и информация о камнях
         */
        static void very_simple_draw(Core::Situation &board);
        

        static void mess(std::string mess);
        
    };
} // namespace Utils
