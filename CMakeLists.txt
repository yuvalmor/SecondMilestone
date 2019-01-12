cmake_minimum_required(VERSION 3.12)
project(SecondMilestone)

set(CMAKE_CXX_STANDARD 14)

add_executable(SecondMilestone
        main.cpp
        ServerSide.h
        MySerialServer.h
        MySerialServer.cpp
        ClientHandler.h
        MyClientHandler.h
        MyClientHandler.cpp
        CacheManager.h
        Matrices.h
        State.h
        Solution.h
        BestFirstSearch.h
        )

