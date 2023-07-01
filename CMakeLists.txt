cmake_minimum_required(VERSION 3.22)

project(normalizer VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

add_subdirectory(app)
add_subdirectory(src)
add_subdirectory(tests)

target_link_libraries(normalizer PRIVATE common)
target_link_libraries(test_newproject PRIVATE common)

install(TARGETS normalizer
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_generate_deploy_app_script(
    TARGET normalizer
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)

qt_finalize_target(normalizer)

install(SCRIPT ${deploy_script})
