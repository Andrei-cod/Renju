#pragma once

namespace Core{

    enum Color{White, Black, None};

    class Stone
    {
    private:
        Color color;
    public:
        Stone();

        void set_color(Color new_color);
        Color get_color() const;
    };   
}