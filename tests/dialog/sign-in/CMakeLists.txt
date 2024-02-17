qt_add_executable(TestSignIn
    tst_SignIn.cpp
)

target_link_libraries(TestSignIn PRIVATE
    Qt6::Test
    Qt6::Widgets
    Qt6::Network
    common
    test_common
)

