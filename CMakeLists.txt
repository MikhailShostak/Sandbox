cmake_minimum_required(VERSION 3.20)
project(Sandbox)

set(CMAKE_CXX_STANDARD 20)

set(DEFAULT_APP_DEPENDENCIES
    ThirdParty
)

add_subdirectory(ThirdParty)
add_subdirectory(Sandbox)
