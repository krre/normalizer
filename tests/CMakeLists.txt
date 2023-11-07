find_package(Qt6 REQUIRED COMPONENTS Test)
include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(dialog)
add_subdirectory(widget)
add_subdirectory(common)
