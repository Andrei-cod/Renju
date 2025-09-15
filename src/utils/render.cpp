#include "utils/render.h"


#include <iostream>

namespace Utils
{
    void Render::very_simple_draw(Core::Board& board){
        //system("clear");
        system("cls");
        std::cout.flush(); 

        for (int i = 0; i < board.get_size(); i++) {
            for (int j = 0; j < board.get_size(); j++) {
                switch (board.get_stone_color(i,j)) {
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
} // namespace Utils
