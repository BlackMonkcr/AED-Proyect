cmake_minimum_required(VERSION 3.26)
project(AED_Proyect)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(AED_Proyect
        HashTable_OpenAddressing.h
        main.cpp
        ForwardList.h
        HashCommonFunctions.cpp)
