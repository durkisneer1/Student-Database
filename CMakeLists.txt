cmake_minimum_required(VERSION 3.24)
project(Student_Database)

set(CMAKE_CXX_STANDARD 23)
set(SDL2_INCLUDE_DIR libs/SDL/include)
set(SDL2_LIB_DIR libs/SDL/lib)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

add_executable(
        Student_Database
        src/main.cpp
        include/RenderWindow.hpp
        src/render_window.cpp
        include/Entity.hpp
        src/entity.cpp
        include/Math.hpp
        src/math.cpp
)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2 SDL2_image SDL2_ttf)
