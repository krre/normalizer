qt_add_executable(test_account
    tst_account.cpp
)

target_link_libraries(test_account PRIVATE
    Qt6::Test
    Qt6::Widgets
    Qt6::Network
    common
    test_common
)

