cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(JMetaVisitor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(depend MetaVisitor.hpp ClassicalVisitor.hpp FuncTraits.hpp TypeList.hpp UID.hpp VTable.hpp)

add_executable(${PROJECT_NAME} main.cpp ${depend})