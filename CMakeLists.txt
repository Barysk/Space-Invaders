cmake_minimum_required(VERSION 3.16)

project(SpaceInvaders LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(SpaceInvaders main.cpp
    spaceship.h
    spaceship.cpp
    game.h
    game.cpp
    laser.h laser.cpp)

find_package(raylib REQUIRED)
target_link_libraries(SpaceInvaders PRIVATE raylib pthread GL m dl rt X11)

include(GNUInstallDirs)
install(TARGETS SpaceInvaders
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
