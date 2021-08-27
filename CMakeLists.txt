cmake_minimum_required(VERSION 3.20)
project(Sandbox)

set(CMAKE_CXX_STANDARD 17)
add_definitions(-D_SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING=1)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

function(target_copy_assets target)
    foreach(INPUT_FILE IN ITEMS ${ARGN})
        set(REGEX_SPLIT_BY_FIRST_SLASH "([^\/]+)\/(.+)")
        string(REGEX REPLACE ${REGEX_SPLIT_BY_FIRST_SLASH} "\\2" OUTPUT_FILE ${INPUT_FILE})
        get_filename_component(INPUT_FILE ${INPUT_FILE} REALPATH BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
        get_filename_component(OUTPUT_FILE ${OUTPUT_FILE} REALPATH BASE_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
        add_custom_command(
            OUTPUT ${OUTPUT_FILE}
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${INPUT_FILE} ${OUTPUT_FILE}
            DEPENDS ${INPUT_FILE}
        )
        target_sources(${target} PRIVATE ${OUTPUT_FILE})
    endforeach()
endfunction()

add_subdirectory(ThirdParty)
add_subdirectory(Frameworks)
add_subdirectory(Sandbox)
add_subdirectory(Editor)
