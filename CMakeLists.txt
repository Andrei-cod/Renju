cmake_minimum_required(VERSION 3.20)
project(renju-game)

# Настройки компилятора
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Папка с исходниками
set(SOURCES
    src/main.cpp
    src/core/stone.cpp
    src/core/board.cpp
    src/core/game.cpp
    src/utils/render.cpp
    src/player/human.cpp
    src/solver/ips.cpp
)

# Папка с заголовками
set(HEADERS
    include/core/stone.h
    include/core/board.h
    include/core/game.h
    include/utils/render.h
    include/player/human.h
    include/solver/ips.h
)

# Создаем исполняемый файл
add_executable(renju-game ${SOURCES} ${HEADERS})

# Указываем где искать заголовки - ОБЯЗАТЕЛЬНО добавить
target_include_directories(renju-game PRIVATE include)