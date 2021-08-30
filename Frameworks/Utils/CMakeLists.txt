set(SOURCES
    Memory/InplaceStorage.hpp
    Utils.hpp
)

add_library(Utils INTERFACE ${SOURCES})
target_include_directories(Utils INTERFACE .)
target_link_libraries(Utils INTERFACE ThirdParty)
