cmake_minimum_required(VERSION 3.26)
project(ProjetoIIA C)

set(CMAKE_C_STANDARD 17)

add_executable(ProjetoIIA main.c
        evolutivo.h
        evolutivo.c
        trepaColinas.c
        trepaColinas.h
        utils.c
        utils.h
        hibrido.h
        hibrido.c)
