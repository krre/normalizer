find_package(Qt6 REQUIRED COMPONENTS
    Widgets
    Network
    WebEngineWidgets
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
    external/network/http/HttpNetwork.h external/network/http/HttpNetwork.cpp
    ui/dialog/account/LoginDialog.cpp ui/dialog/account/LoginDialog.h
    ui/dialog/account/AccountDialog.h ui/dialog/account/AccountDialog.cpp
    external/network/http/HttpRequest.h external/network/http/HttpRequest.cpp
    external/network/http/HttpRequestAttributes.h
    ui/dialog/DialogMessages.h
    ui/dialog/account/ChangePasswordDialog.h ui/dialog/account/ChangePasswordDialog.cpp
    core/Utils.h core/Utils.cpp
    external/network/controller/account/UserAccount.cpp external/network/controller/account/UserAccount.h
    external/network/controller/account/Account.h
    external/network/controller/project/Project.h
    external/network/controller/project/NormProject.h external/network/controller/project/NormProject.cpp
    external/network/controller/HttpController.h external/network/controller/HttpController.cpp
    ui/widget/TableWidget.h ui/widget/TableWidget.cpp
    ui/editor/node/NodeTree.h ui/editor/node/NodeTree.cpp
    ui/editor/CodeEditor.h ui/editor/CodeEditor.cpp
    external/network/http/HttpStatus.h
    ui/editor/node/NodeProperties.h ui/editor/node/NodeProperties.cpp
    ui/editor/node/NodeTreeWidget.h ui/editor/node/NodeTreeWidget.cpp
    ui/editor/node/NodeContextMenu.h ui/editor/node/NodeContextMenu.cpp
)

set_target_properties(common PROPERTIES OUTPUT_NAME normalizer)

target_link_libraries(common PRIVATE
    Qt6::Widgets
    Qt6::Network
    Qt6::WebEngineWidgets
)

target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
