qt_add_executable(test_new_project TestNewProject.cpp)

target_link_libraries(test_new_project PRIVATE
    Qt6::Test
    common
)
