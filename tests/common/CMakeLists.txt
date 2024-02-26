find_package(Qt6 REQUIRED COMPONENTS Test)

add_library(testCommon STATIC
    TestSettings.cpp TestSettings.h
    TestProcess.h TestProcess.cpp
)

target_link_libraries(testCommon PRIVATE
    Qt6::Test
    Qt6::Widgets
    Qt6::Network
    common
)
