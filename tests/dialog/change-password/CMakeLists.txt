qt_add_executable(TestChangePassword
    TestChangePassword.cpp
)

target_link_libraries(TestChangePassword PRIVATE
    testCommon
)
