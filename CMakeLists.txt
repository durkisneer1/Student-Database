cmake_minimum_required(VERSION 3.24)
project(Student_Database)

set(CMAKE_CXX_STANDARD 23)
set(SDL2_INCLUDE_DIR libs/SDL/include)
set(SDL2_LIB_DIR libs/SDL/lib)
set(JSON_INCLUDE_DIR libs/JSON)

include_directories(${SDL2_INCLUDE_DIR} ${JSON_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

add_executable(
        Student_Database
        src/main.cpp
        include/RenderWindow.hpp
        src/render_window.cpp
        include/Wallpaper.hpp
        src/wallpaper.cpp
        include/Math.hpp
        include/Button.hpp
        src/button.cpp
        include/Text.hpp
        src/text.cpp
        include/Utils.hpp
        include/MenuState.hpp
        src/menu_state.cpp
        include/SignUpState.hpp
        src/signup_state.cpp
        include/MajorSelect.hpp
        src/major_select.cpp include/LogInState.hpp src/login_state.cpp)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2 SDL2_image SDL2_ttf)
