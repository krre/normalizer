qt_add_executable(TestChangePassword
    tst_change_password.cpp
)

target_link_libraries(TestChangePassword PRIVATE
    Qt6::Test
    Qt6::Widgets
    Qt6::Network
    common
    test_common
)

