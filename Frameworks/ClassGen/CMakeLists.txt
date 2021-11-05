set(SOURCES
    Classes/Declaration/BaseInfo.hpp
    Classes/Declaration/ClassInfo.hpp
    Classes/Declaration/EventInfo.hpp
    Classes/Declaration/FileInfo.hpp
    Classes/Declaration/FunctionInfo.hpp
    Classes/Declaration/ParameterInfo.hpp
    Classes/Declaration/PropertyInfo.hpp
    Classes/Declaration/TypeInfo.hpp
    Classes/Declaration/TypeInfoSerializer.hpp
    Classes/Editor/FileEditor.cpp
    Classes/Editor/FileEditor.hpp
    Classes/Extension/Class/ClassExtension.cpp
    Classes/Extension/Class/ClassExtension.hpp
    Classes/Extension/Class/ClassFileEditor.cpp
    Classes/Extension/Class/ClassFileEditor.hpp
    Classes/Extension/ExtensionInterface.cpp
    Classes/Extension/ExtensionInterface.hpp
    Classes/Extension/ExtensionLibrary.cpp
    Classes/Extension/ExtensionLibrary.hpp
    Classes/Graph/ConnectionInfo.hpp
    Classes/Graph/GraphInfo.hpp
    Classes/Graph/NodeInfo.hpp
    ClassGen.hpp
    ClassGenGlobals.hpp
)

add_library(ClassGen ${SOURCES})
target_precompile_headers(ClassGen PRIVATE ClassGen.hpp)
target_include_directories(ClassGen PUBLIC .)
target_link_libraries(ClassGen PUBLIC Utils)
