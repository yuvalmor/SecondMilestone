cmake_minimum_required(VERSION 3.12)
project(SecondMilestone)

set(CMAKE_CXX_STANDARD 14)

add_executable(SecondMilestone
        main.cpp
        MySerialServer.h
        MySerialServer.cpp
        Searcher.h
        Searchable.h
        PriorityQueue.h
        State.h
        Solution.h
        ClientHandler.h
        MyClientHandler.h
        MyClientHandler.cpp
        MyParallelServer.h
        MyParallelServer.cpp
        CacheManager.h
        )

