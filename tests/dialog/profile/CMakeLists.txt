qt_add_executable(test_profile
    tst_profile.cpp
)

target_link_libraries(test_profile PRIVATE
    Qt6::Test
    Qt6::Widgets
    Qt6::Network
    common
    test_common
)

