find_package(Qt6 REQUIRED COMPONENTS
    Widgets
    Network
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
    ui/editor/space/Space3d.h ui/editor/space/Space3d.cpp
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
    ui/dialog/account/RegisterAccountDialog.h ui/dialog/account/RegisterAccountDialog.cpp
    core/async/Task.h
    core/async/NetworkAccessManager.h core/async/NetworkAccessManager.cpp
    core/async/Awaiter.h
    external/settings/Settings.h
    external/settings/FileSettings.h external/settings/FileSettings.cpp
    external/network/http/HttpRestApi.h external/network/http/HttpRestApi.cpp
    ui/dialog/account/LoginDialog.cpp ui/dialog/account/LoginDialog.h
    ui/dialog/account/AccountDialog.h ui/dialog/account/AccountDialog.cpp
    external/network/http/HttpRequest.h external/network/http/HttpRequest.cpp
    external/network/http/HttpRequestAttributes.h
    ui/dialog/DialogMessages.h
    ui/dialog/account/ChangePasswordDialog.h ui/dialog/account/ChangePasswordDialog.cpp
    core/Utils.h core/Utils.cpp
    external/network/controller/account/Account.cpp
    external/network/controller/account/Account.h
    external/network/controller/project/Project.h
    external/network/controller/project/Project.cpp
    external/network/controller/RestController.h external/network/controller/RestController.cpp
    ui/widget/TableWidget.h ui/widget/TableWidget.cpp
    ui/editor/node/NodeTree.h ui/editor/node/NodeTree.cpp
    ui/editor/CodeEditor.h ui/editor/CodeEditor.cpp
    ui/editor/node/NodeProperties.h ui/editor/node/NodeProperties.cpp
    ui/editor/node/NodeTreeView.h ui/editor/node/NodeTreeView.cpp
    ui/editor/node/NodeContextMenu.h ui/editor/node/NodeContextMenu.cpp
    external/network/RestApi.h
    external/network/controller/module/Module.h external/network/controller/module/Module.cpp
    ui/editor/model/NodeModel.cpp ui/editor/model/NodeModel.h
    ui/editor/NodeManager.h ui/editor/NodeManager.cpp
)

set_target_properties(common PROPERTIES OUTPUT_NAME normalizer)

target_link_libraries(common PRIVATE
    Qt6::Widgets
    Qt6::Network
    Qt6::3DCore
    Qt6::3DRender
    Qt6::3DInput
    Qt6::3DLogic
    Qt6::3DExtras
    Qt6::3DAnimation
)

target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
