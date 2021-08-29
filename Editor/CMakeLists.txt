set(SOURCES
    ClassGen/ClassGenSettings.cpp
    ClassGen/ClassGenSettings.hpp
    Data/Config.hpp
    Data/Extensions.cpp
    Data/Extensions.hpp
    Data/Workspace.cpp
    Data/Workspace.hpp
    Editors/BinaryEditor.cpp
    Editors/BinaryEditor.hpp
    Editors/ClassGenEditor.cpp
    Editors/ClassGenEditor.hpp
    Editors/Editor.cpp
    Editors/Editor.hpp
    Editors/TextEditor.cpp
    Editors/TextEditor.hpp
    Views/File/FileDialogs.cpp
    Views/MainMenu.cpp
    Views/Other/FileBrowser.cpp
    Views/Other/UtilsViews.cpp
    Views/Other/WelcomePageView.cpp
    Views/RootView.cpp
    Views/Settings/ClassGen.cpp
    Views/Settings/EnvironmentView.cpp
    Views/Settings/ExtensionsView.cpp
    Views/Settings/FileTypesView.cpp
    Views/Settings/GeneralSettingsView.cpp
    Views/Settings/SettingsView.cpp
    Views/View/ConsoleView.cpp
    Views/Views.hpp
    main.cpp
)

set(ASSETS
    Assets/config.yaml
    Assets/Extensions/Anonymous.HelloWorld/.extension.yaml
)

add_executable(Editor ${SOURCES})
target_copy_assets(Editor ${ASSETS})
target_link_libraries(Editor Frameworks)
