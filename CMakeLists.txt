cmake_minimum_required(VERSION 3.20)
project(win10d2d)

set(CMAKE_CXX_STANDARD 17)

add_executable(win10d2db WIN32 main.cpp basewindow.h mainwindow.cpp mainwindow.h utils.h)
