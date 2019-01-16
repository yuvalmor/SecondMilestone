cmake_minimum_required(VERSION 3.12)
project(SecondMilestone)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)
add_executable(SecondMilestone
        main.cpp
        ServerSide.h
        MySerialServer.h
        MySerialServer.cpp
        ClientHandler.h
        MyClientHandler.h
        MyClientHandler.cpp
        CacheManager.h
        State.h
        Solution.h
        BestFirstSearch.h
        MyParallelServer.h
        MyParallelServer.cpp
        Solver.h
        MySolver.h
        GeneralServer.h
        GeneralServer.cpp
        MatricesProblem.h
        DepthFirstSearch.h
        BreadthFirstSearch.h
        Astar.h
        FileCacheManager.h
        FileCacheManager.cpp
        )

