cmake_minimum_required(VERSION 3.20)
project(Sandbox)

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/release/0.17/conan.cmake"
        "${CMAKE_BINARY_DIR}/conan.cmake"
        EXPECTED_HASH SHA256=3bef79da16c2e031dc429e1dac87a08b9226418b300ce004cc125a82687baeef
        TLS_VERIFY ON
    )
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_run(REQUIRES
    assimp/5.1.0
    DiligentEngine/2.5
    boost/1.77.0
    fmt/8.0.1
    glfw/3.3.4
    hlslpp/3.1
    imgui/1.84.0-ext
    range-v3/0.11.0
    stb/cci.20210713
    utfcpp/3.2.1
    yaml-cpp/0.7.0
    BUILD missing
    BASIC_SETUP
)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()


set(CMAKE_CXX_STANDARD 17)
add_definitions(-D_SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING=1)


function(target_copy_assets target)
    foreach(INPUT_FILE IN ITEMS ${ARGN})
        set(REGEX_SPLIT_BY_FIRST_SLASH "([^\\/]+)\\/(.+)")
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
