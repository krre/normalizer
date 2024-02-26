qt_add_executable(TestNewProject
    TestNewProject.cpp
)

target_link_libraries(TestNewProject PRIVATE
    Qt6::Test
    Qt6::Widgets
    common
    testCommon
)
