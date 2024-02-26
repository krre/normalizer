qt_add_executable(TestChangePassword
    TestChangePassword.cpp
)

target_link_libraries(TestChangePassword PRIVATE
    Qt6::Test
    Qt6::Widgets
    Qt6::Network
    common
    testCommon
)

