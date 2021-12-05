#include "OSCTaskDataInstance.h"

enum SettingsField
{
    Label = 0,
    Value = 1,
};

OSCCompilerSettingsDataObject::Data OSCTaskSettings::getResolvedCompilerSettings() const
{
    OSCCompilerSettingsDataObject::Data data;
    data.compiler = getItemValue(0, 0, Value);
    data.defineFlag = getItemValue(0, 1, Value);
    data.includeFlag = getItemValue(0, 2, Value);
    data.includePathFlag = getItemValue(0, 3, Value);
    data.outputFileFlag = getItemValue(0, 4, Value);
    data.compilationFlag = getItemValue(0, 5, Value);
    data.flags = getItemValue(0, 6, Value);
    return data;
}

OSCCompilationSettingsDataObject::Data OSCTaskSettings::getResolvedCompilationSettings() const
{
    OSCCompilationSettingsDataObject::Data data;
    data.defines = getItemValue(1, 0, Value);
    data.includes = getItemValue(1, 1, Value);
    data.includePaths = getItemValue(1, 2, Value);
    return data;
}

OSCArchiverSettingsDataObject::Data OSCTaskSettings::getResolvedArchiverSettings() const
{
    OSCArchiverSettingsDataObject::Data data;
    data.archiver = getItemValue(2, 0, Value);
    data.outputFileFlag = getItemValue(2, 1, Value);
    data.flags = getItemValue(2, 2, Value);
    return data;
}

OSCLinkerSettingsDataObject::Data OSCTaskSettings::getResolvedLinkerSettings() const
{
    OSCLinkerSettingsDataObject::Data data;
    data.linker = getItemValue(3, 0, Value);
    data.libraryFlag = getItemValue(3, 1, Value);
    data.libraryPathFlag = getItemValue(3, 2, Value);
    data.outputFileFlag = getItemValue(3, 3, Value);
    data.libraryFlags = getItemValue(3, 4, Value);
    data.applicationFlags = getItemValue(3, 5, Value);
    data.flags = getItemValue(3, 6, Value);
    return data;
}

OSCLinkageSettingsDataObject::Data OSCTaskSettings::getResolvedLinkageSettings() const
{
    OSCLinkageSettingsDataObject::Data data;
    data.libraries = getItemValue(4, 0, Value);
    data.libraryPaths = getItemValue(4, 1, Value);
    data.frameworks = getItemValue(4, 2, Value);
    return data;
}

OSCFilesSettingsDataObject::Data OSCTaskSettings::getResolvedFilesSettings() const
{
    OSCFilesSettingsDataObject::Data data;
    data.objectFileName = getItemValue(5, 0, Value);
    data.staticLibraryFileName = getItemValue(5, 1, Value);
    data.dynamicLibraryFileName = getItemValue(5, 2, Value);
    data.applicationFileName = getItemValue(5, 3, Value);
    data.debugSymbolsFileName = getItemValue(5, 4, Value);
    return data;
}

OSCTaskSettings::SizeType OSCTaskSettings::getGroupsCount() const
{
    return 6;
}

String OSCTaskSettings::getGroupTitle(SizeType groupIndex) const
{
    switch(groupIndex)
    {
    case 0:
        return "Compiler Settings";
    case 1:
        return "Compilation Settings";
    case 2:
        return "Archiver Settings";
    case 3:
        return "Linker Settings";
    case 4:
        return "Linkage Settings";
    case 5:
        return "Files Settings";
    }

    return String();
}

OSCTaskSettings::SizeType OSCTaskSettings::getRowsCount(SizeType groupIndex) const
{
    switch(groupIndex)
    {
    case 0:
        return 7;
    case 1:
        return 3;
    case 2:
        return 3;
    case 3:
        return 7;
    case 4:
        return 3;
    case 5:
        return 5;
    }

    return 0;
}

OSCTaskSettings::SizeType OSCTaskSettings::getColumnsCount(SizeType groupIndex) const
{
    return 2;
}

OSCTaskSettings::ItemType OSCTaskSettings::getItem(SizeType groupIndex, SizeType rowIndex, SizeType columnIndex) const
{
    if (columnIndex == Label || columnIndex - 100000 == Label)
    {
        switch (groupIndex)
        {
        case 0:
            return OSCCompilerSettingsDataObjectEntity::getStaticProperties()[rowIndex];
        case 1:
            return OSCCompilationSettingsDataObjectEntity::getStaticProperties()[rowIndex];
        case 2:
            return OSCArchiverSettingsDataObjectEntity::getStaticProperties()[rowIndex];
        case 3:
            return OSCLinkerSettingsDataObjectEntity::getStaticProperties()[rowIndex];
        case 4:
            return OSCLinkageSettingsDataObjectEntity::getStaticProperties()[rowIndex];
        case 5:
            return OSCFilesSettingsDataObjectEntity::getStaticProperties()[rowIndex];
        }
    }

    if (columnIndex >= 100000)
    {
        columnIndex -= 100000;

        switch (groupIndex)
        {
        case 0:
            return getData()->getCompilerSettings()->getDataProperty(OSCCompilerSettingsDataObjectEntity::getStaticProperties()[rowIndex]).asValue<String>();
        case 1:
            return getData()->getCompilationSettings()->getDataProperty(OSCCompilationSettingsDataObjectEntity::getStaticProperties()[rowIndex]).asValue<String>();
        case 2:
            return getData()->getArchiverSettings()->getDataProperty(OSCArchiverSettingsDataObjectEntity::getStaticProperties()[rowIndex]).asValue<String>();
        case 3:
            return getData()->getLinkerSettings()->getDataProperty(OSCLinkerSettingsDataObjectEntity::getStaticProperties()[rowIndex]).asValue<String>();
        case 4:
            return getData()->getLinkageSettings()->getDataProperty(OSCLinkageSettingsDataObjectEntity::getStaticProperties()[rowIndex]).asValue<String>();
        case 5:
            return getData()->getFilesSettings()->getDataProperty(OSCFilesSettingsDataObjectEntity::getStaticProperties()[rowIndex]).asValue<String>();
        }
    }

    const char **labels = nullptr;
    String *data = nullptr;

    static const char *CompilerSettingsLabels[] = {
        "Compiler",
        "Define flag",
        "Include flag",
        "Include path flag",
        "Output file flag",
        "Compilation flag",
        "Flags",
    };

    static const char *CompilationSettingsLabels[] = {
        "Defines",
        "Includes",
        "Include paths",
    };

    static const char *ArchiverSettingsLabels[] = {
        "Archiver",
        "Output file flag",
        "Flags",
    };

    static const char *LinkerSettingsLabels[] = {
        "Linker",
        "Library flag",
        "Library path flag",
        "Output file flag",
        "Library linkage flags",
        "Application linkage flags",
        "Flags",
    };

    static const char *LinkageSettingsLabels[] = {
        "Libraries",
        "Library paths",
        "Frameworks",
    };

    static const char *FilesSettingsLabels[] = {
        "Object file name",
        "Static library file name",
        "Dynamic library file name",
        "Application file name",
        "Debug symbols file name",
    };

    switch (groupIndex)
    {
    case 0:
        labels = CompilerSettingsLabels;
        data = &getData()->CompilerSettings.Compiler;
        break;
    case 1:
        labels = CompilerSettingsLabels;
        data = &getData()->CompilationSettings.Defines;
        break;
    case 2:
        labels = ArchiverSettingsLabels;
        data = &getData()->ArchiverSettings.Archiver;
        break;
    case 3:
        labels = LinkerSettingsLabels;
        data = &getData()->LinkerSettings.Linker;
        break;
    case 4:
        labels = LinkageSettingsLabels;
        data = &getData()->LinkageSettings.Libraries;
        break;
    case 5:
        labels = FilesSettingsLabels;
        data = &getData()->FilesSettings.ObjectFileName;
        break;
    }

    return columnIndex == Label ? labels[rowIndex] : data[rowIndex];

    //return ItemType();
}

void OSCTaskSettings::onItemChange(SizeType groupIndex, SizeType rowIndex, SizeType columnIndex, const ItemType &item)
{
    String *data = nullptr;

    switch (groupIndex)
    {
    case 0:
        data = &getData()->CompilerSettings.Compiler;
        break;
    case 1:
        data = &getData()->CompilationSettings.Defines;
        break;
    case 2:
        data = &getData()->ArchiverSettings.Archiver;
        break;
    case 3:
        data = &getData()->LinkerSettings.Linker;
        break;
    case 4:
        data = &getData()->LinkageSettings.LibraryPaths;
        break;
    case 5:
        data = &getData()->FilesSettings.ObjectFileName;
        break;
    }

    data[rowIndex] = item;
}
