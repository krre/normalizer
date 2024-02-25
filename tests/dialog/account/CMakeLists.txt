qt_add_executable(TestAccount
    tst_account.cpp
)

target_link_libraries(TestAccount PRIVATE
    Qt6::Test
    Qt6::Widgets
    Qt6::Network
    common
    testCommon
)

