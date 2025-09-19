#include "core/stone.h"

namespace Core
{
    /**
     * @brief Реализация конструктора по умолчанию
     *
     * Инициализирует камень со значением Color::None, что соответствует пустой клетке на доске.
     */
    Stone::Stone()
    {
        m_color = Color::None;
    }

    /**
     * @brief Реализация получения цвета камня
     *
     * @return Возвращает цвет камня на данный момент
     *
     * @note Color::None означает, что камень отсутствует (пустая клетка).
     */

    Color Stone::get_color() const
    {
        return m_color;
    }
    /**
     * @brief Реализация установки нового цвета камня
     *
     * @param new_color Новый цвет камня
     *
     * @warning Установка камню состояния Color::None противоречит правилам, но не проверяется
     * Ответственность - на вызывающей стороне
     * @note Color::None означает, что камень отсутствует (пустая клетка).
     */
    void Stone::set_color(Color new_color)
    {
        m_color = new_color;
    }
} // namespace Core
