qt_add_executable(TestSignUp
    tst_SignUp.cpp
)

target_link_libraries(TestSignUp PRIVATE
    Qt6::Test
    Qt6::Widgets
    Qt6::Network
    common
    testCommon
)

