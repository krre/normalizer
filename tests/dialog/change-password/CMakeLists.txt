qt_add_executable(test_change_password
    tst_change_password.cpp
)

target_link_libraries(test_change_password PRIVATE
    Qt6::Test
    Qt6::Widgets
    Qt6::Network
    common
    test_common
)

