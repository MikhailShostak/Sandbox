#pragma once

#include <OneStudioPlatform>
#include <OneStudioProjectLibrary>

#include "Views/ProjectSettingsView.gen.h"

namespace OneStudioProject
{

template<typename DataType, typename ViewType>
class EditorTemplate : public OneStudioPlatform::EditorInstance
{
    String currentPath;
    Map<String, APair<SharedReference<DataType>, SharedReference<ViewType>>> loadedData;
    SharedReference<DataType> currentDataInstance;
protected:

    Array<SharedReference<DataType>> getLoadedData() const
    {
        Array<SharedReference<DataType>> list;
        for (auto pair : loadedData)
        {
            list.append(pair.second.first);
        }
        return list;
    }

    SharedReference<ViewType> findView(const SharedReference<DataType> &data)
    {
        AAssert(data, "Data is not set");
        auto it = data.find(data->getPath());
        if (it == data.end())
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
        auto data = allocateData(path);

        data->setPath(path);
        onCreate(data, item);
        data->load(path);

        auto view = allocateView();
        loadedData[path.toString()] = { data, view };
        onLoad(data, item, view, identifier);
        return view;
    }

    /*bool openFile(const SharedReference<OSFileSystemItem> &item)
    {
        auto &path = item->getPath();
        auto it = loadedData.find(path.toString());
        if(it == loadedData.end())
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
        auto it = loadedData.find(path.toString());
        if (it == loadedData.end())
        {
            return false;
        }

        onSave(it->second.first, item);
        return it->second.first->save(path);
    }

    void closeFile(const SharedReference<OSFileSystemItem> &item) override
    {
        auto &path = item->getPath();
        loadedData.remove(path.toString());
    }

protected:

    virtual SharedReference<ViewType> allocateView() const
    {
        return Create<ViewType>();
    }

    virtual SharedReference<DataType> allocateData(const APath &path) const
    {
        return createNew<DataType>();
    }

    virtual void onViewCreate(const SharedReference<ViewType> &view) {}

    virtual void onCreate(const SharedReference<DataType> &data, const SharedReference<OSFileSystemItem> &item) {}
    virtual void onLoad(const SharedReference<DataType> &data, const SharedReference<OSFileSystemItem> &item, const SharedReference<UI::View> &view, const String &identifier) {}
    virtual void onSave(const SharedReference<DataType> &data, const SharedReference<OSFileSystemItem> &item) {}

};

class ProjectEditor : public EditorTemplate<OSProject, OneStudioProject::ProjectSettingsView>
{
public:
    ADelegate<void(const Array<SharedReference<OSProject>> &projects)> onLoadCallback;

    void onLoad(const SharedReference<OSProject> &project, const SharedReference<OSFileSystemItem> &item, const SharedReference<UI::View> &view, const String &identifier) override;
    void onSave(const SharedReference<OSProject> &project, const SharedReference<OSFileSystemItem> &item) override;

    void loadFile(const SharedReference<OSFileSystemItem> &item);

private:
    void indexProject(const SharedReference<OSProject> &project);
    Array<SharedReference<OSFileSystemItem>> processDirectory(const ADirectory &directory);
};

}
