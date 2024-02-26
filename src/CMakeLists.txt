find_package(Qt6 REQUIRED COMPONENTS
    Widgets
    Network
    Sql
    3DCore
    3DRender
    3DInput
    3DLogic
    3DExtras
    3DAnimation
)

add_library(common STATIC
    ui/ActionBuilder.h ui/ActionBuilder.cpp
    ui/MainWindow.h ui/MainWindow.cpp
    ui/editor/3d/View3D.h ui/editor/3d/View3D.cpp
    ui/dialog/StandardDialog.h ui/dialog/StandardDialog.cpp
    ui/widget/BrowseLayout.h ui/widget/BrowseLayout.cpp
    ui/widget/Action.h
    ui/widget/Menu.h
    core/CommonTypes.h
    core/Application.h core/Application.cpp
    core/Exception.h core/Exception.cpp
    core/Format.h
    ui/dialog/PreferencesDialog.h ui/dialog/PreferencesDialog.cpp
    ui/widget/project/ProjectTable.h ui/widget/project/ProjectTable.cpp
    ui/widget/project/ProjectEditor.h ui/widget/project/ProjectEditor.cpp
    ui/dialog/account/SignUpDialog.h ui/dialog/account/SignUpDialog.cpp
    core/async/Task.h
    core/async/NetworkAccessManager.h core/async/NetworkAccessManager.cpp
    core/async/Awaiter.h
    external/settings/Settings.h
    external/settings/FileSettings.h external/settings/FileSettings.cpp
    external/repository/network/http/HttpRestApi.h external/repository/network/http/HttpRestApi.cpp
    ui/dialog/account/SignInDialog.cpp ui/dialog/account/SignInDialog.h
    ui/dialog/account/AccountDialog.h ui/dialog/account/AccountDialog.cpp
    external/repository/network/http/HttpRequest.h external/repository/network/http/HttpRequest.cpp
    external/repository/network/http/HttpRequestAttributes.h
    ui/dialog/DialogMessages.h
    ui/dialog/account/ChangePasswordDialog.h ui/dialog/account/ChangePasswordDialog.cpp
    core/Utils.h core/Utils.cpp
    external/repository/network/controller/account/Account.cpp
    external/repository/network/controller/account/Account.h
    external/repository/network/controller/project/Project.h
    external/repository/network/controller/project/Project.cpp
    external/repository/network/controller/RestController.h external/repository/network/controller/RestController.cpp
    ui/widget/TableWidget.h ui/widget/TableWidget.cpp
    ui/editor/tree/NodeTree.h ui/editor/tree/NodeTree.cpp
    ui/editor/CodeEditor.h ui/editor/CodeEditor.cpp
    ui/editor/tree/NodeProperties.h ui/editor/tree/NodeProperties.cpp
    ui/editor/tree/NodeTreeView.h ui/editor/tree/NodeTreeView.cpp
    external/repository/network/RestApi.h
    external/repository/network/controller/module/Module.h external/repository/network/controller/module/Module.cpp
    ui/editor/model/NodeModel.cpp ui/editor/model/NodeModel.h
    ui/editor/NodeManager.h ui/editor/NodeManager.cpp
    ui/editor/NodeContextMenu.h ui/editor/NodeContextMenu.cpp
    ui/editor/3d/Window3D.h ui/editor/3d/Window3D.cpp
    ui/dialog/project/NewProjectDialog.h ui/dialog/project/NewProjectDialog.cpp
    program/Project.h program/Project.cpp
    external/repository/Repository.h external/repository/Repository.cpp
    external/repository/DatabaseRepository.h external/repository/DatabaseRepository.cpp
    external/repository/database/Database.h external/repository/database/Database.cpp
    external/repository/NetworkRepository.h external/repository/NetworkRepository.cpp
    external/controller/AbstractController.h external/controller/AbstractController.cpp
    external/process/Process.h external/process/Process.cpp
    external/process/NormProcess.h external/process/NormProcess.cpp
)

set_target_properties(common PROPERTIES OUTPUT_NAME normalizer)

target_link_libraries(common PRIVATE
    Qt6::Widgets
    Qt6::Network
    Qt6::Sql
    Qt6::3DCore
    Qt6::3DRender
    Qt6::3DInput
    Qt6::3DLogic
    Qt6::3DExtras
    Qt6::3DAnimation
)

target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
