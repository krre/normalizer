qt_add_executable(TestSignIn
    TestSignIn.cpp
)

target_link_libraries(TestSignIn PRIVATE
    Qt6::Test
    Qt6::Widgets
    Qt6::Network
    common
    testCommon
)

