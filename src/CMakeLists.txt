find_package(Qt6 REQUIRED COMPONENTS
    Widgets
    3DCore
    3DRender
    3DInput
    3DLogic
    3DExtras
    3DAnimation
)

set(SRC
    core/Constants.h
    core/ObjectNames.h
    core/Settings.h
    ui/ActionBuilder.h ui/ActionBuilder.cpp
    ui/MainWindow.h ui/MainWindow.cpp
    ui/RenderView.h ui/RenderView.cpp
    ui/RecentProjectsMenu.h ui/RecentProjectsMenu.cpp
    ui/dialog/StandardDialog.h ui/dialog/StandardDialog.cpp
    ui/dialog/NewProject.h ui/dialog/NewProject.cpp
    ui/widget/BrowseLayout.h ui/widget/BrowseLayout.cpp
    ui/widget/Action.h
    ui/widget/Menu.h
    core/CommonTypes.h
    project/Project.h project/Project.cpp
    project/Session.h project/Session.cpp
)

add_library(common STATIC ${SRC})

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
