#include "core/game.h"

namespace Core
{
    Game::Game(int size, Type type)
        : m_size(size), m_type(type), m_situation(size), m_turn(1), f(true) {}

    Game::Game(int size, std::vector<std::vector<int>> white,
               std::vector<std::vector<int>> black, int turn, Type type)
        : m_size(size), m_type(type), m_situation(size, white, black),
          m_turn(turn)
    {
        if (m_situation.check_win())
        {
        }
    }

        Status Game::move(int x, int y)
    {
        x--;
        y--;

        if (m_turn > 0)
        {
            f = m_situation.move(x, y, Core::Color::White);
        }
        else
        {
            f = m_situation.move(x, y, Core::Color::Black);
        }
        if (f)
        {
            m_turn *= -1;
        } else {
            return ongoing;
        }

        Status m = draw;
        int cw = m_situation.check_win(x, y);
        if (cw == 1)
        {
            if (m_turn > 0)
            {
                m = black_wins;
            }
            else
            {
                m = white_wins;
            }
            Utils::Render::win(m_situation, m);
            return game_end;
        }
        else if (cw == 2)
        {
            Utils::Render::win(m_situation, m);
            return game_end;
        }
        return ongoing;
    }



    void Game::render(){
        Utils::Render::very_simple_draw(m_situation);
    }


} // namespace Core
