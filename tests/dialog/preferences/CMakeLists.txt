qt_add_executable(TestPreferences
    TestPreferences.cpp
)

target_link_libraries(TestPreferences PRIVATE
    testCommon
)
