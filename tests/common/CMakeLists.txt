add_library(testCommon STATIC
    TestSettings.cpp TestSettings.h
)

target_link_libraries(testCommon PUBLIC
    Qt6::Test
    common
)
