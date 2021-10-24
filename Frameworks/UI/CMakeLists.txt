set(SOURCES
    UI.hpp
    View/Button.cpp
    View/Button.hpp
    View/Label.cpp
    View/Label.hpp
    View/TextField.cpp
    View/TextField.hpp
    View/View.cpp
    View/View.hpp
)

add_library(UI ${SOURCES})
target_precompile_headers(UI PRIVATE UI.hpp)
target_include_directories(UI PUBLIC .)
target_link_libraries(UI PUBLIC Utils)
