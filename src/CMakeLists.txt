configure_file(config.h.in config.h @ONLY)

qt_add_library(common STATIC
    core/Application.cpp core/Application.h
    core/async/Awaiter.h core/async/Task.h
    network/Network.h network/Network.cpp
    network/api/Controller.h network/api/Controller.cpp
    network/api/common/Server.h network/api/common/Server.cpp
    network/api/common/Workspace.cpp network/api/common/Workspace.h
    project/Project.h project/Project.cpp
    settings/FileSettings.cpp settings/FileSettings.h
    settings/Settings.cpp settings/Settings.h
    ui/MainWindow.cpp ui/MainWindow.h
    ui/dialog/NewProject.cpp ui/dialog/NewProject.h
    ui/dialog/NewWorkspace.cpp ui/dialog/NewWorkspace.h
    ui/dialog/Preferences.cpp ui/dialog/Preferences.h
    ui/dialog/StandardDialog.cpp ui/dialog/StandardDialog.h
    ui/editor/CodeEditor.h ui/editor/CodeEditor.cpp
    ui/widget/BrowseLayout.cpp ui/widget/BrowseLayout.h
)

# For visibility in IDE (e.g., Qt Creator)
add_custom_target(custom
    SOURCES
    config.h.in
)

target_link_libraries(common PUBLIC
    Qt6::Widgets
    Qt6::WebSockets
)

target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
