set(SOURCES
    Classes/Declaration/BaseInfo.hpp
    Classes/Declaration/ClassInfo.hpp
    Classes/Declaration/FileInfo.hpp
    Classes/Declaration/FunctionInfo.hpp
    Classes/Declaration/ParameterInfo.hpp
    Classes/Declaration/PropertyInfo.hpp
    Classes/Declaration/TypeInfo.hpp
    Classes/Declaration/TypeInfoSerializer.hpp
    Classes/Graph/ConnectionInfo.hpp
    Classes/Graph/GraphInfo.hpp
    Classes/Graph/NodeInfo.hpp
    ClassGen.hpp
)

add_library(ClassGen INTERFACE ${SOURCES})
target_include_directories(ClassGen INTERFACE .)
target_link_libraries(ClassGen INTERFACE Utils)
