#pragma once

#include <Experimental>

#include "Core/BaseCGType.h"
#include <functional>

#include "MetaObject.h"

#include <yaml-cpp/yaml.h>

namespace YAML
{

template<typename Type>
void decode_helper(const Node& node, Type& value);

template <typename T>
struct as_if<T, std::optional<T> >
{
    explicit as_if(const Node& node_) : node(node_) {}
    const Node& node;

    const std::optional<T> operator()() const
    {
        std::optional<T> val;
        T t;
        if (node.m_pNode && convert<T>::decode(node, t))
            val = std::move(t);

        return val;
    }
};

// There is already a std::string partial specialisation, so we need a full specialisation here
template <>
struct as_if<std::string, std::optional<std::string> >
{
    explicit as_if(const Node& node_) : node(node_) {}
    const Node& node;

    const std::optional<std::string> operator()() const
    {
        std::optional<std::string> val;
        std::string t;
        if (node.m_pNode && convert<std::string>::decode(node, t))
            val = std::move(t);

        return val;
    }
};
    
template<>
struct convert<AJSONArray>
{
    inline static Node encode(const AJSONArray& j)
    {
        Node node;
        if(j.empty())
        {
            return Node(std::vector<int>());
        }
        for(const auto &v : j)
        {
            if(v.isObject())
            {
                node.push_back(v.asObject());
            }
            else if(v.isArray())
            {
                node.push_back(v.asArray());
            }
            else if(v.isString())
            {
                node.push_back(v.asString());
            }
            else if(v.isNumber())
            {
                node.push_back(v.asNumber());
            }
            else if(v.isBoolean())
            {
                node.push_back(v.asBoolean());
            }
        }
        
        return node;
    }

    inline static bool decode(const Node& node, AJSONArray& rhs) {
        
        if(node.IsSequence())
        {
            for (YAML::const_iterator it = node.begin(); it != node.end(); ++it)
            {
                if(it->IsSequence())
                {
                    AJSONArray array;
                    decode(*it, array);
                    rhs.push_back(array);
                }
                else if (it->IsMap())
                {
                    AJSONObject object;
                    decode_helper(*it, object);
                    rhs.push_back(object);
                }
                else if (it->IsNull())
                {
                    rhs.push_back(AJSONValue());
                }
                else
                {
                    std::optional<std::string> as_string = YAML::as_if<std::string, std::optional<std::string> >(*it)();
                    std::optional<double> as_double      = YAML::as_if<double, std::optional<double> >(*it)();
                    std::optional<int> as_int            = YAML::as_if<int, std::optional<int> >(*it)();
                    std::optional<bool> as_bool          = YAML::as_if<bool, std::optional<bool> >(*it)();
                    if(as_string)
                    {
                        rhs.push_back(as_string.value().data());
                    }
                    else if (as_double)
                    {
                        rhs.push_back(as_double.value());
                    }
                    else if (as_int)
                    {
                        rhs.push_back(as_int.value());
                    }
                    else if (as_bool)
                    {
                        rhs.push_back(as_bool.value());
                    }
                }
            }
        }

        return true;
    }
};

template<>
struct convert<AJSONObject>
{
    inline static Node encode(const AJSONObject& j)
    {
        if(j.isEmpty())
        {
            return Node(std::map<const char *, int>());
        }
        Node node;
        for(const auto &p : j)
        {
            const auto &v = p.second;
            if(v.isObject())
            {
                node[(const char *)p.first.data()] = v.asObject();
            }
            else if(v.isArray())
            {
                node[(const char *)p.first.data()] = v.asArray();
            }
            else if(v.isString())
            {
                node[(const char *)p.first.data()] = v.asString();
            }
            else if(v.isNumber())
            {
                node[(const char *)p.first.data()] = v.asNumber();
            }
            else if(v.isBoolean())
            {
                node[(const char *)p.first.data()] = v.asBoolean();
            }
        }
        return node;
    }

    inline static bool decode(const Node& node, AJSONObject& rhs) {
        if(node.IsMap())
        {
            for (YAML::const_iterator it = node.begin(); it != node.end(); ++it)
            {
                const auto &k = it->first.as<std::string>();
                if(it->second.IsSequence())
                {
                    AJSONArray array;
                    decode_helper(it->second, array);
                    rhs.insert(k.data(), array, false);
                }
                else if (it->second.IsMap())
                {
                    AJSONObject object;
                    decode(it->second, object);
                    rhs.insert(k.data(), object, false);
                }
                else if (it->second.IsNull())
                {
                    rhs.insert(k.data(), AJSONValue(), false);
                }
                else
                {
                    std::optional<std::string> as_string = YAML::as_if<std::string, std::optional<std::string> >(it->second)();
                    std::optional<double> as_double      = YAML::as_if<double, std::optional<double> >(it->second)();
                    std::optional<int> as_int            = YAML::as_if<int, std::optional<int> >(it->second)();
                    std::optional<bool> as_bool          = YAML::as_if<bool, std::optional<bool> >(it->second)();
                    if(as_string)
                    {
                        rhs.insert(k.data(), as_string.value().data());
                    }
                    else if (as_double)
                    {
                        rhs.insert(k.data(), as_double.value());
                    }
                    else if (as_int)
                    {
                        rhs.insert(k.data(), as_int.value());
                    }
                    else if (as_bool)
                    {
                        rhs.insert(k.data(), as_bool.value());
                    }
                }
            }
        }      
        return true;
    }
};

template<typename Type>
inline void decode_helper(const Node& node, Type& value)
{
    convert<Type>::decode(node, value);
}

}

namespace LegacyClassGen
{

class ClassManager : public ASingleton<ClassManager>
{
    //AFactoryMap<String, BaseCGType> types;
    Map<String, MetaObject *> types;
    Map<MetaObject *, ADelegate<void(const APath &source)>> delegates;
    Map<MetaObject *, CGTypeGroup> groups;
    Map<String, SharedReference<BaseCGType>> loadedTypes;
public:
    const Map<String, SharedReference<BaseCGType>> &getLoadedTypes() const { return loadedTypes; }

    ADelegate<void(const SharedReference<BaseCGType> &type)> typeLoaded;
    ADelegate<void(const SharedReference<BaseCGType> &type)> typeUnloaded;

    void registerType(MetaObject &type, const String &name, CGTypeGroup group)
    {
        //types.insert<Type>(name);
        types.insert({ name, &type });
        groups.insert({ &type, group });
    }

    //template<typename Type>
    //void registerType(const String &name, CGTypeGroup group, const std::function<void(const Array<SharedReference<Type>> &types, const APath &source)> &delegate = nullptr)

    template<typename Type>
    void registerType(MetaObject &type, const String &name, CGTypeGroup group, void (*delegate)(const Array<SharedReference<Type>> &, const APath &))
    {
        //types.insert<Type>(name);
        types.insert({ name, &type });
        groups.insert({ &type, group });

        delegates.insert(&type, [this, delegate](const APath &source) {
            Array<SharedReference<Type>> filteredTypes;
            for (auto &pair : loadedTypes)
            {
                if (AMeta::getDynamicTypeHash(*pair.second) == AMeta::getStaticTypeHash<Type>())
                {
                    filteredTypes.append(pair.second.as<Type>());
                }
            }
            if (filteredTypes)
            {
                delegate(filteredTypes, source);
            }
        });
    }

    void unregisterType(MetaObject &type)
    {
        Array<SharedReference<BaseCGType>> typesForUnloading;
        for (auto[n, t] : loadedTypes)
        {
            if (AMeta::getDynamicTypeHash(*t.get()) == type.hash)
            {
                typesForUnloading.push_back(t);
            }
        }
        for (auto &t : typesForUnloading)
        {
            unload(t);
        }
        auto it = rng::find_if(types, [&](const auto &v) { return v.second == &type; });
        if (it != types.end())
        {
            types.erase(it);
            groups.erase(&type);
            delegates.erase(&type);
        }
    }

    void unregisterType(const String &name)
    {
        //TODO: implement
    }

    ClassManager();

    void processTypes(const APath &source)
    {
        for (auto &typeAndDelegate : delegates)
        {
            typeAndDelegate.second(source);
        }
    }

    SharedReference<BaseCGType> load(const APath &path, const String &package = String())
    {
        AJSONObject object = YAML::LoadFile(path.toString()).as<AJSONObject>();
        //AJSONObject object = AJSON::valueFromFile(path).toObject();

        String name = path.baseName();

        String fullname;
        String namespaceName;
        if (object.read("Namespace", namespaceName))
        {
            fullname = namespaceName + ".";
        }
        fullname.append(name);
        auto it = loadedTypes.find(fullname);
        if (it != loadedTypes.end())
        {
            return it->second;
        }

        SharedReference<BaseCGType> type;
        String typeName;
        if (object && object.read("Type", typeName))
        {
            auto it = types.find(typeName);
            if (it == types.end())
            {
                return type;
            }

            MetaObject *metaobject = it->second;
            type = SharedReference<BaseCGType>(DynamicCast<BaseCGType>(metaobject->constructor()));
            type->group = groups[metaobject];
            type->package = package;
            type->path = path;
            type->data = object;
            loadedTypes.insert({ fullname, type });
            if (typeLoaded)
            {
                typeLoaded(type);
            }
        }
        return type;
    }

    void unload(const SharedReference<BaseCGType> &type)
    {
        auto it = rng::find_if(loadedTypes, [&](auto &v) { return v.second == type; });
        if (it != loadedTypes.end())
        {
            loadedTypes.erase(it);

            if (typeUnloaded)
            {
                typeUnloaded(type);
            }
        }
    }

    AError importFiles(const Array<APathInfo> &files, const String &package = String())
    {
        for (const auto &file : files)
        {
            if (!load(file.path(), package))
            {
                return AError(-1, fmt::format("Failed to load file: {}", file.path()));
            }
        }

        return AError::getEmptyError();
    }

    AError importPath(const APathInfo &pathInfo, const String &package = String())
    {
        if (!pathInfo.isExists())
        {
            return AError(-1, fmt::format("Path doesn't exist: {}", pathInfo.path()));
        }

        if (pathInfo.isDirectory())
        {
            const auto &files = ADirectory(pathInfo).findRecursively("cg", AFindFilter::AllFiles);
            if (AError error = importFiles(files, package))
            {
                return error;
            }
        }
        else
        {
            if (!load(pathInfo.path(), package))
            {
                return AError(-1, fmt::format("Failed to load file: {}", pathInfo.path()));
            }
        }

        return AError::getEmptyError();
    }
};

}
