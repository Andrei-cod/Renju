#include "core/stone.h"

namespace Core
{
    Stone::Stone(){
        m_color = Color::None;
    }
    Color Stone::get_color() const{
        return m_color;
    }
    void Stone::set_color(Color new_color){
        m_color = new_color;
    }
} // namespace Core
