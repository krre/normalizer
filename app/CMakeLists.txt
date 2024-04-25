add_executable(normalizer main.cpp)

target_link_libraries(normalizer PRIVATE
    common
)

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
