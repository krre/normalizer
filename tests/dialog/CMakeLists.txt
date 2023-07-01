find_package(Qt6 REQUIRED COMPONENTS Test Widgets)

qt_add_executable(test_newproject tst_newproject.cpp)

target_link_libraries(test_newproject PRIVATE
    Qt6::Test
    Qt6::Widgets
)
