cmake_minimum_required(VERSION 3.12)
project(SecondMilestone)

set(CMAKE_CXX_STANDARD 14)

add_executable(SecondMilestone
        main.cpp
        Searcher.h
        Searchable.h
        PriorityQueue.h
        State.h
        )