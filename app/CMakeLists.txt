set(SOURCES main.cpp)
add_executable(normalizer ${SOURCES})

target_link_libraries(normalizer PRIVATE Qt6::Widgets)
