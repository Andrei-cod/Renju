#include "utils/render.h"

#include <iostream>

#ifdef _WIN32
    #include <windows.h>
#elif defined(__linux__) || defined(__APPLE__)
    #include <unistd.h>
#endif

namespace Utils
{
    /**
     * @brief Очищает консоль и сбрасывает буфер вывода
     * 
     * Функция автоматически выбирает способ очистки консоли в зависимости от ОС:
     * - Windows: использует system("cls")
     * - Linux/macOS: использует system("clear")
     * - Другие системы: использует ANSI escape codes
     * 
     * После очистки сбрасывает буфер вывода для немедленного отображения изменений.
     */
    void clear_console()
    {
        #ifdef _WIN32
            system("cls");
        #elif defined(__linux__) || defined(__APPLE__)
            system("clear");
        #else
            std::cout << "\033[2J\033[1;1H"; // ANSI escape codes
        #endif
        
        std::cout.flush(); // Принудительный сброс буфера вывода
    }


    /**
     * @brief Функция отрисовки поля в консоли
     *
     * Функция очищает консоль, запрашивает у доски board
     * информацию о камнях и отрисовывает их.
     *
     * @param board состояние поля и информация о камнях
     *
     * @note Для очистки консоли используются различные функции в зависимости от системы
     */
    void Render::very_simple_draw(Core::Situation &board)
    {
        clear_console();
        for (int i = 0; i < board.get_size(); i++)
        {
            for (int j = 0; j < board.get_size(); j++)
            {
                switch (board.get_stone_color(i, j))
                {
                case Core::Color::None:
                    std::cout << "_ ";
                    break;
                case Core::Color::Black:
                    std::cout << "O ";
                    break;
                case Core::Color::White:
                    std::cout << "X ";
                    break;
                }
            }
            std::cout << std::endl;
        }
        std::cout << "Введите ход (x y): ";
        std::cout.flush();
    }

    void Render::mess(std::string mess){
        std::cout << mess;
    }

    void Render::win(Core::Situation &board, Core::Status who_win)
    {
        clear_console();

        for (int i = 0; i < board.get_size(); i++)
        {
            for (int j = 0; j < board.get_size(); j++)
            {
                switch (board.get_stone_color(i, j))
                {
                case Core::Color::None:
                    std::cout << "_ ";
                    break;
                case Core::Color::Black:
                    std::cout << "O ";
                    break;
                case Core::Color::White:
                    std::cout << "X ";
                    break;
                }
            }
            std::cout << std::endl;
        }
        switch (who_win)
        {
        case Core::white_wins:
            std::cout << "Белые выиграли!!!" << std::endl; 
            break;
        case Core::black_wins:
            std::cout << "Черные выиграли!!!" << std::endl; 
            break;
        case Core::draw:
            std::cout << "Ничья" << std::endl; 
            break;
        }
        std::cout.flush();
    }
} // namespace Utils
