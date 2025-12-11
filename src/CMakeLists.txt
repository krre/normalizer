configure_file(config.h.in config.h @ONLY)

qt_add_library(common STATIC
    core/Application.cpp core/Application.h
    ui/MainWindow.cpp ui/MainWindow.h
    settings/FileSettings.cpp settings/FileSettings.h
    settings/Settings.cpp settings/Settings.h
    ui/dialog/StandardDialog.cpp ui/dialog/StandardDialog.h
    ui/widget/BrowseLayout.cpp ui/widget/BrowseLayout.h
    ui/dialog/NewProject.cpp ui/dialog/NewProject.h
    ui/dialog/Preferences.cpp ui/dialog/Preferences.h
    project/Project.h project/Project.cpp
    ui/editor/CodeEditor.h ui/editor/CodeEditor.cpp
    network/WebSocketClient.h network/WebSocketClient.cpp
    network/api/Network.h network/ApiNetwork.cpp
    network/api/Controller.h network/api/Controller.cpp
    network/api/common/Server.h network/api/common/Server.cpp
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
