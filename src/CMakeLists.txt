configure_file(config.h.in config.h @ONLY)

add_library(common STATIC
    core/Application.h core/Application.cpp
    core/CommonTypes.h
    core/Exception.h core/Exception.cpp
    core/Format.h
    core/Utils.h core/Utils.cpp
    core/async/Awaiter.h
    core/async/NetworkAccessManager.h core/async/NetworkAccessManager.cpp
    core/async/Task.h
    external/network/RestApi.h
    external/network/controller/RestController.h external/network/controller/RestController.cpp
    external/network/controller/account/Account.cpp
    external/network/controller/account/Account.h
    external/network/controller/module/Module.h external/network/controller/module/Module.cpp
    external/network/controller/project/Project.cpp
    external/network/controller/project/Project.h
    external/network/http/HttpRequest.h external/network/http/HttpRequest.cpp
    external/network/http/HttpRequestAttributes.h
    external/network/http/HttpRestApi.h external/network/http/HttpRestApi.cpp
    external/settings/FileSettings.h external/settings/FileSettings.cpp
    external/settings/Settings.h
    program/Project.h program/Project.cpp
    ui/ActionBuilder.h ui/ActionBuilder.cpp
    ui/MainWindow.h ui/MainWindow.cpp
    ui/dialog/DialogMessages.h
    ui/dialog/PreferencesDialog.h ui/dialog/PreferencesDialog.cpp
    ui/dialog/StandardDialog.h ui/dialog/StandardDialog.cpp
    ui/dialog/account/AccountDialog.h ui/dialog/account/AccountDialog.cpp
    ui/dialog/account/ChangePasswordDialog.h ui/dialog/account/ChangePasswordDialog.cpp
    ui/dialog/account/SignInDialog.cpp ui/dialog/account/SignInDialog.h
    ui/dialog/account/SignUpDialog.h ui/dialog/account/SignUpDialog.cpp
    ui/editor/3d/View3D.h ui/editor/3d/View3D.cpp
    ui/editor/CodeEditor.h ui/editor/CodeEditor.cpp
    ui/editor/NodeContextMenu.h ui/editor/NodeContextMenu.cpp
    ui/editor/NodeManager.h ui/editor/NodeManager.cpp
    ui/editor/model/NodeModel.cpp ui/editor/model/NodeModel.h
    ui/editor/tree/NodeProperties.h ui/editor/tree/NodeProperties.cpp
    ui/editor/tree/NodeTree.h ui/editor/tree/NodeTree.cpp
    ui/editor/tree/NodeTreeView.h ui/editor/tree/NodeTreeView.cpp
    ui/widget/Action.h
    ui/widget/BrowseLayout.h ui/widget/BrowseLayout.cpp
    ui/widget/Menu.h
    ui/widget/TableWidget.h ui/widget/TableWidget.cpp
    ui/widget/project/ProjectEditor.h ui/widget/project/ProjectEditor.cpp
    ui/widget/project/ProjectTable.h ui/widget/project/ProjectTable.cpp
    ui/editor/3d/VulkanWindow.h ui/editor/3d/VulkanWindow.cpp
    ui/editor/3d/VulkanRenderer.h ui/editor/3d/VulkanRenderer.cpp
    gfx/vulkan/device/PhysicalDevice.h gfx/vulkan/device/PhysicalDevice.cpp
    gfx/vulkan/Handle.h
)

# For visibility in IDE (e.g., Qt Creator)
add_custom_target(custom
    SOURCES
    config.h.in
)

set_target_properties(common PROPERTIES OUTPUT_NAME normalizer)

target_link_libraries(common PUBLIC
    Qt6::Widgets
    Qt6::Network
)

target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
