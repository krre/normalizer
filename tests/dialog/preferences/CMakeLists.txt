qt_add_executable(TestPreferences
    tst_preferences.cpp
)

target_link_libraries(TestPreferences PRIVATE
    Qt6::Test
    Qt6::Widgets
    Qt6::Network
    common
    testCommon
)
