qt_add_executable(testSignUp
    tst_SignUp.cpp
)

target_link_libraries(testSignUp PRIVATE
    Qt6::Test
    Qt6::Widgets
    Qt6::Network
    common
    test_common
)

