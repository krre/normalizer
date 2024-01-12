find_package(Qt6 REQUIRED COMPONENTS Test)

add_library(test_common STATIC

)

target_link_libraries(test_common PRIVATE
    Qt6::Test
    Qt6::Widgets
    Qt6::Network
    common
)
