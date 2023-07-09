find_package(Qt6 REQUIRED COMPONENTS Test Widgets)

qt_add_executable(test_recentmenu
    tst_recentmenu.cpp
)

target_link_libraries(test_recentmenu PRIVATE
    Qt6::Test
    Qt6::Widgets
)
