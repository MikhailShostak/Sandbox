cmake_minimum_required(VERSION 3.20)
project(Sandbox)

set(CMAKE_CXX_STANDARD 20)
add_definitions(-D_SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING=1)


add_subdirectory(ThirdParty)
add_subdirectory(Frameworks)
add_subdirectory(Sandbox)
