cmake_minimum_required(VERSION 3.18)
project(LinuxHunter LANGUAGES CXX VERSION 1.0)
#This is kind of a hack, as the project shouldn't set this directly,
#but who actually sets this manually?
set(CURSES_USE_NCURSES TRUE)
set(CURSES_NEED_WIDE TRUE)
find_package(Curses REQUIRED)
find_package(fmt REQUIRED)

add_subdirectory(src)
