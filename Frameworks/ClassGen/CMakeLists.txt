set(SOURCES
    Classes.hpp
    Classes/BaseInfo.hpp
    Classes/ClassInfo.hpp
    Classes/FileInfo.hpp
    Classes/PropertyInfo.hpp
    Classes/TypeInfo.hpp
    Classes/TypeInfoSerializer.hpp
)

add_library(ClassGen INTERFACE ${SOURCES})
target_include_directories(ClassGen INTERFACE .)
target_link_libraries(ClassGen INTERFACE Utils)
