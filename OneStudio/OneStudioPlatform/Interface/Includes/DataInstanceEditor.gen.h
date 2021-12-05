#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Serializable.h"
#include "Math"

//CLASSGEN END REGION
#include "Includes/EditorInstance.gen.h"

//CLASSGEN GENERATED REGION: NamespaceBegin
//CLASSGEN END REGION

#include <Foundation>

template<typename FileDataInstanceType, typename ViewType>
class OSFileDataInstanceEditor : public OneStudioPlatform::EditorInstance
{

    String currentPath;

    Map<String, APair<SharedReference<FileDataInstanceType>, SharedReference<ViewType>>> dataInstances;

    SharedReference<FileDataInstanceType> currentDataInstance;

protected:

    Array<SharedReference<FileDataInstanceType>> getDataInstances() const
    {
        Array<SharedReference<FileDataInstanceType>> list;
        for(auto pair : dataInstances)
        {
            list.push_back(pair.second.first);
        }
        return list;
    }

    SharedReference<ViewType> findView(const SharedReference<FileDataInstanceType> &dataInstance)
    {
        AAssert(dataInstance, "dataInstance should be valid");
        auto it = dataInstances.find(dataInstance->getPath());
        if(it == dataInstances.end())
        {
            return nullptr;
        }

        return it->second.second;
    }


public:

    /*SharedReference<FileDataInstanceType> getCurrentDataInstance() const
    {
        return currentDataInstance;
    }

    SharedReference<ViewType> getView() const
    {
        if(!this->view)
        {
            //TODO: remove const cast
            const_cast<OSFileDataInstanceEditor<FileDataInstanceType, ViewType> *>(this)->view = allocateView();
            const_cast<OSFileDataInstanceEditor<FileDataInstanceType, ViewType> *>(this)->onViewCreate(this->view);
        }
        return this->view;
    }*/

    SharedReference<UI::View> loadFile(const SharedReference<OSFileSystemItem> &item, const String &identifier) override
    {
        auto &path = item->getPath();
        auto dataInstance = allocateDataInstance(path);
        dataInstance->setPath(path);
        onCreate(dataInstance, item);
        if(!dataInstance->load())
        {
            return nullptr;
        }

        auto view = allocateView();
        dataInstances[path.toString()] = {dataInstance, view};
        onLoad(dataInstance, item, view, identifier);
        return view;
    }

    /*bool openFile(const SharedReference<OSFileSystemItem> &item)
    {
        auto &path = item->getPath();
        auto it = dataInstances.find(path.toString());
        if(it == dataInstances.end())
        {
            return false;
        }

        currentDataInstance = it->second;
        onUpdate(it->second, item);

        return true;
    }*/

    bool saveFile(const SharedReference<OSFileSystemItem> &item)
    {
        auto &path = item->getPath();
        auto it = dataInstances.find(path.toString());
        if(it == dataInstances.end())
        {
            return false;
        }

        onSave(it->second.first, item);

        return it->second.first->save();
    }

    void closeFile(const SharedReference<OSFileSystemItem> &item) override
    {
        auto &path = item->getPath();
        dataInstances.erase(path.toString());
    }

protected:

    virtual SharedReference<ViewType> allocateView() const
    {
        return CreateShared<ViewType>();
    }

    virtual SharedReference<FileDataInstanceType> allocateDataInstance(const APath &path) const
    {
        return CreateShared<FileDataInstanceType>();
    }

    virtual void onViewCreate(const SharedReference<ViewType> &view) {}

    virtual void onCreate(const SharedReference<FileDataInstanceType> &dataInstance, const SharedReference<OSFileSystemItem> &item) {}
    virtual void onLoad(const SharedReference<FileDataInstanceType> &dataInstance, const SharedReference<OSFileSystemItem> &item, const SharedReference<UI::View> &view, const String &identifier) {}
    virtual void onSave(const SharedReference<FileDataInstanceType> &dataInstance, const SharedReference<OSFileSystemItem> &item) {}

};

//CLASSGEN GENERATED REGION: NamespaceEnd
//CLASSGEN END REGION
