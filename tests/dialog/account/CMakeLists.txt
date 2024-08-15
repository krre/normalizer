qt_add_executable(TestAccount
    TestAccount.cpp
)

target_link_libraries(TestAccount PRIVATE
    testCommon
)
