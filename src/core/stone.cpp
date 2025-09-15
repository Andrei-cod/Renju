#include "core/stone.h"

namespace Core
{
    Stone::Stone(){
        color = Color::None;
    }
    Color Stone::get_color() const{
        return color;
    }
    void Stone::set_color(Color new_color){
        color = new_color;
    }
} // namespace Core
