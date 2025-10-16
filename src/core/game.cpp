#include "core/game.h"
#include "player/human.h"
#include "solver/ips.h"

namespace Core
{
    /**
     * @brief Конструктор новой игры.
     *
     * Инициализирует объект Game с пустым полем заданного размера и устанавливает начальный ход.
     *
     * @param size Размер стороны игрового поля.
     * @param type Тип игры (например, с ботом или между игроками).
     */
    Game::Game(int size, Type type)
        : m_size(size), m_type(type), m_situation(size), m_turn(1), f(true) {}

    /**
     * @brief Конструктор игры с уже установленным состоянием поля.
     *
     * Используется для загрузки сохранённой или тестовой позиции.
     *
     * @param size Размер стороны игрового поля.
     * @param white Массив координат белых камней.
     * @param black Массив координат чёрных камней.
     * @param turn Текущий ход (1 — белые, -1 — чёрные).
     * @param type Тип игры.
     */
    Game::Game(int size, std::vector<std::vector<int>> white,
               std::vector<std::vector<int>> black, int turn, Type type)
        : m_size(size), m_type(type), m_situation(size, white, black),
          m_turn(turn)
    {
        if (m_situation.check_win())
        {
        }
    }

    /**
     * @brief Выполняет ход в текущей партии.
     *
     * Проверяет корректность хода, обновляет состояние поля и переключает очередь хода.
     * Также выполняет проверку на победу или ничью.
     *
     * @param x Координата X (начиная с 1).
     * @param y Координата Y (начиная с 1).
     * @return Status:
     * - ongoing — если игра продолжается;
     * - game_end — если партия завершена (победа или ничья).
     */
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
        }
        else
        {
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

    void Game::render()
    {
        Utils::Render::very_simple_draw(m_situation);
    }
    /**
     * @brief Main-loop
     *  Основной игровой цикл, работает с ips и игроком
     */
    void Game::run()
    {
        Player::Ips ips(Black);
        Player::Human human (White);
        std::pair<int,int> move_pos;    
        
        Core::Status f = Core::ongoing;
        

        while (true)
        {
            if (f == Core::ongoing)
            {
                render();
            }
            else
            {
                break;
            }

            if (m_turn > 0)
            {
                move_pos = human.get_move();
            }
            else
            {
                move_pos = ips.get_move(m_situation);
            }

            f = move(move_pos.first, move_pos.second);
        }
    }

} // namespace Core
