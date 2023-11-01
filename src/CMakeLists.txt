find_package(Qt6 REQUIRED COMPONENTS
    Widgets
    3DCore
    3DRender
    3DInput
    3DLogic
    3DExtras
    3DAnimation
)

add_library(common STATIC
    core/Constants.h
    core/ObjectNames.h
    core/Settings.h
    ui/ActionBuilder.h ui/ActionBuilder.cpp
    ui/MainWindow.h ui/MainWindow.cpp
    ui/RenderView.h ui/RenderView.cpp
    ui/dialog/StandardDialog.h ui/dialog/StandardDialog.cpp

    ui/widget/BrowseLayout.h ui/widget/BrowseLayout.cpp
    ui/widget/Action.h
    ui/widget/Menu.h

    core/CommonTypes.h
    project/Project.h project/Project.cpp
    project/Session.h project/Session.cpp
    core/Application.h core/Application.cpp
    norm/Project.h norm/Project.cpp
    norm/FileReader.h norm/FileReader.cpp
    norm/FileWriter.h norm/FileWriter.cpp
    norm/Token.h norm/Token.cpp
    core/Exception.h core/Exception.cpp
    core/Format.h
    norm/TokenType.h
    ui/dialog/PreferencesDialog.h ui/dialog/PreferencesDialog.cpp
    ui/widget/project/ProjectTable.h ui/widget/project/ProjectTable.cpp
    ui/widget/project/ProjectEditor.h ui/widget/project/ProjectEditor.cpp
    ui/dialog/account/RegisterAccountDialog.h ui/dialog/account/RegisterAccountDialog.cpp
    core/async/Task.h core/async/Task.cpp
    core/async/NetworkAccessManager.h core/async/NetworkAccessManager.cpp
    core/async/Awaiter.h
    manager/settings/AbstractSettingsManager.h
    manager/settings/SettingsManager.h manager/settings/SettingsManager.cpp
)

set_target_properties(common PROPERTIES OUTPUT_NAME normalizer)

target_link_libraries(common PRIVATE
    Qt6::Widgets
    Qt6::3DCore
    Qt6::3DRender
    Qt6::3DInput
    Qt6::3DLogic
    Qt6::3DExtras
    Qt6::3DAnimation
)

target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
