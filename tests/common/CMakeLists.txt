add_library(testCommon STATIC
    TestSettings.cpp TestSettings.h
)

target_link_libraries(testCommon PRIVATE
    Qt6::Test
    Qt6::Widgets
    Qt6::Network
    common
)
