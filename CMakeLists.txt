cmake_minimum_required(VERSION 3.26)
project(filozof)

set(CMAKE_CXX_STANDARD 17)

add_executable(filozof
        Fork.cpp
        Fork.h
        Philosopher.cpp
        Philosopher.h
        Table.cpp
        Table.h
        Config.h
        Utils.cpp
        Utils.h
        NaivePhilosopher.cpp
        NaivePhilosopher.h
        main.cpp
        WaiterPhilosopher.cpp
        WaiterPhilosopher.h
)
