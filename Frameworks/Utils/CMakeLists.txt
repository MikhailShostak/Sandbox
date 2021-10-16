set(SOURCES
    Containers/Array.hpp
    Containers/List.hpp
    Containers/Map.hpp
    Containers/Queue.hpp
    Containers/Set.hpp
    Containers/SortedMap.hpp
    Containers/SortedSet.hpp
    Containers/StaticArray.hpp
    DateTime/Counter.hpp
    DateTime/Date.hpp
    DateTime/Duration.hpp
    DateTime/Stopwatch.hpp
    DateTime/Time.hpp
    DateTime/Timer.hpp
    Memory/Allocation.hpp
    Memory/InplaceStorage.hpp
    Meta/Aliases.hpp
    Meta/Inheritance.hpp
    Meta/Substitution.hpp
    Reflection/Reflection.hpp
    Serialization/Serialization.hpp
    Serialization/Serializer.hpp
    Serialization/Storage.hpp
    System/Filesystem.hpp
    System/Process.hpp
    Text/String.hpp
    Utils.hpp
)

add_library(Utils INTERFACE ${SOURCES})
target_include_directories(Utils INTERFACE .)
target_link_libraries(Utils INTERFACE ThirdParty)
