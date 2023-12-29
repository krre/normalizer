find_package(Qt6 REQUIRED COMPONENTS
    Widgets
    Network
    WebEngineWidgets
)

add_library(common STATIC
    core/Constants.h
    ui/ActionBuilder.h ui/ActionBuilder.cpp
    ui/MainWindow.h ui/MainWindow.cpp
    ui/editor/RenderView.h ui/editor/RenderView.cpp
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
    settings/Settings.h
    settings/FileSettings.h settings/FileSettings.cpp
    network/http/HttpNetwork.h network/http/HttpNetwork.cpp
    ui/dialog/account/LoginDialog.cpp ui/dialog/account/LoginDialog.h
    ui/dialog/account/AccountDialog.h ui/dialog/account/AccountDialog.cpp
    network/http/HttpRequest.h network/http/HttpRequest.cpp
    network/http/HttpRequestAttributes.h
    ui/dialog/DialogMessages.h
    ui/dialog/account/ChangePasswordDialog.h ui/dialog/account/ChangePasswordDialog.cpp
    core/Utils.h core/Utils.cpp
    network/controller/account/UserAccount.cpp network/controller/account/UserAccount.h
    network/controller/account/Account.h
    network/controller/project/Project.h
    network/controller/project/NormProject.h network/controller/project/NormProject.cpp
    network/controller/HttpController.h network/controller/HttpController.cpp
    ui/widget/TableWidget.h ui/widget/TableWidget.cpp
    ui/editor/TreeView.h ui/editor/TreeView.cpp
    ui/editor/View.h ui/editor/View.cpp
)

set_target_properties(common PROPERTIES OUTPUT_NAME normalizer)

target_link_libraries(common PRIVATE
    Qt6::Widgets
    Qt6::Network
    Qt6::WebEngineWidgets
)

target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
