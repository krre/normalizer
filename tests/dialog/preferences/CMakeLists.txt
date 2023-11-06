qt_add_executable(test_preferences
    tst_preferences.cpp
)

target_link_libraries(test_preferences PRIVATE
    Qt6::Test
    Qt6::Widgets
    Qt6::Network
    common
)
