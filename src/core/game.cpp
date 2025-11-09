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
    Game::Game(Core::Situation board, Type type)
        : m_size(board.get_size()), m_type(type), m_situation(board), m_turn(1), m_is_valid_move(true) {}

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
    Game::Game(Core::Situation board, Type type, int turn)
        : m_size(board.get_size()), m_type(type), m_situation(board),
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
        // Нормализация координат
        x--;
        y--;

        if (m_turn > 0)
        {
            m_is_valid_move = m_situation.move(x, y, Core::Color::White);
        }
        else
        {
            m_is_valid_move = m_situation.move(x, y, Core::Color::Black);
        }
        if (m_is_valid_move)
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
        Player::Ips ips (Black);
        Player::Human human (White);
        std::pair<int,int> move_pos;    
        
        Core::Status game_status = Core::ongoing;
        

        while (true)
        {
            if (game_status == Core::ongoing)
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

            game_status = move(move_pos.first, move_pos.second);
        }
    }

} // namespace Core
