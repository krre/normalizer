qt_add_executable(test_login
    tst_login.cpp
)

target_link_libraries(test_login PRIVATE
    Qt6::Test
    Qt6::Widgets
    Qt6::Network
    common
    test_common
)

