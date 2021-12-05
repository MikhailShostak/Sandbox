file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS *.h *.hpp *.cpp)

MACRO(HEADER_DIRECTORIES return_list)
    FILE(GLOB_RECURSE new_list *.h)
    SET(dir_list "")
    FOREACH(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()

HEADER_DIRECTORIES(PRIVATE_HEADERS)

add_library(Legacy ${SOURCES})
target_compile_definitions(Legacy PUBLIC "_WIN32_WINNT=0x0602" "_ALLOW_COROUTINE_ABI_MISMATCH=1" "CLASSGEN_GENERATED_REGION_META_OBJECT=" "CLASSGEN_GENERATED_REGION_OBJECT=" "METAOBJECT_SUPPORT=1" "REFLECTION_SUPPORT=1" "CLASSGEN_END_REGION=" "UNICODE=1")
target_compile_options(Legacy PUBLIC "/wd4838")
target_precompile_headers(Legacy PUBLIC Legacy.pch.hpp)
target_include_directories(Legacy PUBLIC ${PRIVATE_HEADERS})
target_include_directories(Legacy PUBLIC
    .
    Assets/Interface
    Assets2/Interface
    BuildSystem/Interface
    Console/Interface
    Core/Interface
    Data
    Data/Interface
    Experimental
    Experimental/Interface
    ExperimentalClasses
    ExperimentalClasses/Interface
    Extensions/Interface
    Flow/Interface
    Fonts/Interface
    Foundation/Interface
    Graphics/Interface
    ImageFormats/Interface
    LegacyIncludes
    Math/Interface
    Network/Interface
    Platform/Interface
    Plugins/Interface
    System/Interface
    UI/Interface
    UI2/Interface
    UIDarkTheme/Interface
)
target_link_libraries(Legacy Frameworks Userenv)
