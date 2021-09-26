set(SOURCES
    Classes.hpp
    Classes/BaseInfo.hpp
    Classes/ClassInfo.hpp
    Classes/FileInfo.hpp
    Classes/FunctionInfo.hpp
    Classes/Graph/ConnectionInfo.hpp
    Classes/Graph/GraphInfo.hpp
    Classes/Graph/NodeInfo.hpp
    Classes/ParameterInfo.hpp
    Classes/PropertyInfo.hpp
    Classes/TypeInfo.hpp
    Classes/TypeInfoSerializer.hpp
)

add_library(ClassGen INTERFACE ${SOURCES})
target_include_directories(ClassGen INTERFACE .)
target_link_libraries(ClassGen INTERFACE Utils)
