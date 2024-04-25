qt_add_executable(TestSignIn
    TestSignIn.cpp
)

target_link_libraries(TestSignIn PRIVATE
    testCommon
)
