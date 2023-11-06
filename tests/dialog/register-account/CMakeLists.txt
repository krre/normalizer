qt_add_executable(test_register_account
    tst_register_account.cpp
)

target_link_libraries(test_register_account PRIVATE
    Qt6::Test
    Qt6::Widgets
    Qt6::Network
    common
)
