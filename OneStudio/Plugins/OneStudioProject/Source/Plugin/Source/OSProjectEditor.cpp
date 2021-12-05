#include "OSProjectEditor.h"
#include "Main.h"

void OneStudioProject::ProjectEditor::onLoad(const SharedReference<OSProject> &project, const SharedReference<OSFileSystemItem> &item, const SharedReference<UI::View> &view, const String &identifier)
{
    ProjectContext->loadProject(project);
    item->setText(project->getBaseName());

    Array<APathInfo> projects;
    Array<APathInfo> entries;

    for(auto &projectEntry : project->getEntries())
    {
        APathInfo pathInfo = APathInfo(projectEntry.resolveWithDirectory(project->getDirectory()));
        if(!pathInfo.isExists())
        {
            continue;
        }

        if(pathInfo.extension() == "osproject")
        {
            projects.emplaceBack(std::move(pathInfo));
        }
        else
        {
            entries.emplaceBack(std::move(pathInfo));
        }
    }

    std::sort(projects.begin(), projects.end(), [](const APathInfo &a, const APathInfo &b){ return a.baseName() < b.baseName(); });
    std::sort(entries.begin(), entries.end(), [](const APathInfo &a, const APathInfo &b){ return a.baseName() < b.baseName(); });

    if(projects)
    {
        SharedReference<OSFileSystemItem> dependencies = createNew<OSFileSystemItem>();
        dependencies->setText("Dependencies");
        //dependencies->setImage(QFileIconProvider().icon(QFileIconProvider::Folder));
        item->addItem(dependencies);

        for(const APathInfo &projectPathInfo : projects)
        {
            SharedReference<OSFileSystemItem> projectEntryItem = createNew<OSFileSystemItem>();
            projectEntryItem->setText(projectPathInfo.baseName());
            projectEntryItem->setPath(projectPathInfo.path());
            //projectEntryItem->setImage(QFileIconProvider().icon(QFileInfo((projectPathInfo.path()).toString().toUtf8().data())));
            if(projectPathInfo && projectPathInfo.isDirectory())
            {
                projectEntryItem->setItems(processDirectory(std::move(projectPathInfo)));
            }
            dependencies->addItem(projectEntryItem);
            OneStudioPlatform::FileContext::getInstance().loadFileSystemItem(projectEntryItem);
        }
    }

    for(const APathInfo &entryPathInfo : entries)
    {
        SharedReference<OSFileSystemItem> projectEntryItem = createNew<OSFileSystemItem>();
        projectEntryItem->setText(entryPathInfo.name());
        projectEntryItem->setPath(entryPathInfo.path());
        //projectEntryItem->setImage(QFileIconProvider().icon(QFileInfo((entryPathInfo.path()).toString().toUtf8().data())));
        projectEntryItem->setItems(processDirectory(std::move(entryPathInfo)));
        OneStudioPlatform::FileContext::getInstance().loadFileSystemItem(projectEntryItem);
        item->addItem(projectEntryItem);
    }

    if(onLoadCallback)
    {
        onLoadCallback(getLoadedData());
    }
    auto projectSettingsView = view.as<OneStudioProject::ProjectSettingsView>();
    projectSettingsView->setProject(project);
    projectSettingsView->setTasks(ProjectContext->targetTasks);

    indexProject(project);
}

void OneStudioProject::ProjectEditor::onSave(const SharedReference<OSProject> &project, const SharedReference<OSFileSystemItem> &item)
{

}

void OneStudioProject::ProjectEditor::indexProject(const SharedReference<OSProject> &project)
{
    static Map<void *, bool> indexStatus;

    if(indexStatus[project.data()])
    {
        return;
    }

    indexStatus[project.data()] = true;

    auto targetData = project->getTargetData();
    for(const OneStudioProject2::Target &t : targetData)
    {
        String sources = t.settings.at("com.InsaneTeam.OneStudio.General").as<OSBuildTaskSettings>()->getItemValue(0, 1, 1);
        for(auto &source : sources.split(';'))
        {
            APathInfo pathInfo(source);
            if(pathInfo.isDirectory())
            {
                auto filePaths = ADirectory(pathInfo).findRecursively("cpp", AFindFilter::Files);
                for(auto &filePath : filePaths)
                {
                    AFile file;
                    if(file.open(filePath.path(), AFileOpenMode::ReadBinary))
                    {
                        while(!file.atEnd())
                        {
                            if(file.take() == ':' && !file.atEnd() && file.take() == ':' && !file.atEnd())
                            {
                                uint8_t symbol = file.take();
                                String name;
                                while(std::isalpha(symbol) && !file.atBegin())
                                {
                                    name.append(char(symbol));
                                    symbol = file.take();
                                }
                                if(symbol == '(' && !file.atBegin())
                                {
                                    symbol = file.take();
                                    while(symbol != ')' && !file.atBegin())
                                    {
                                        symbol = file.take();
                                    }
                                    symbol = file.take();
                                    if(!file.atBegin())
                                    {
                                        while(std::isspace(symbol) && !file.atBegin())
                                        {
                                            symbol = file.take();
                                        }
                                        if(symbol == '{')
                                        {
                                            String filename = file.path().name();
                                            filename = filename.left(filename.indexOf('.'));
                                            //DefinitionsView->addDefinition(/*project->getBaseName() + "/" + t.Name + "/" + */filename + "/" + name, "test");
                                        }
                                    }
                                 }
                            }
                        }
                    }
                }
            }
        }
    }
}

Array<SharedReference<OSFileSystemItem>> OneStudioProject::ProjectEditor::processDirectory(const ADirectory &directory)
{
    Array<SharedReference<OSFileSystemItem>> fileSystemItems;
    for(auto &entry : directory)
    {
        if(entry == "" || entry == "." || entry == "..")
        {
            continue;
        }
        SharedReference<OSFileSystemItem> fileSystemItem = createNew<OSFileSystemItem>();
        fileSystemItem->setText(entry);
        //fileSystemItem->setImage(QFileIconProvider().icon(QFileInfo((directory.path() + entry).toString().toUtf8().data())));

        APathInfo pathInfo(directory.path() + entry);
        fileSystemItem->setPath(pathInfo.path());
        if(pathInfo.isDirectory())
        {
            fileSystemItem->setItems(processDirectory(ADirectory(pathInfo)));
        } else if(pathInfo.isFile()) {
            //TODO
            /*QObject::connect(fileSystemItem.data(), &OSFileSystemItem::selected, [this, pathInfo](){

            });*/
        }
        OneStudioPlatform::FileContext::getInstance().loadFileSystemItem(fileSystemItem);
        fileSystemItems.append(fileSystemItem);
    }
    return fileSystemItems;
}
