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
    ui/ActionBuilder.h ui/ActionBuilder.cpp
    ui/MainWindow.h ui/MainWindow.cpp
    ui/RenderView.h ui/RenderView.cpp
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
