qt_add_executable(TestSignUp
    TestSignUp.cpp
)

target_link_libraries(TestSignUp PRIVATE
    Qt6::Test
    Qt6::Widgets
    Qt6::Network
    common
    testCommon
)

