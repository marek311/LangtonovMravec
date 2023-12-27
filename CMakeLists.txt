cmake_minimum_required(VERSION 3.26)
project(LangtonovMravec)

set(CMAKE_CXX_STANDARD 17)

add_executable(LangtonovMravec main.cpp
        Mravec.cpp
        Mravec.h
        Simulacia.cpp
        Simulacia.h
        Pole.cpp
        Pole.h
        Plocha.cpp
        Plocha.h)