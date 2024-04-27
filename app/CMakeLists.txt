add_executable(normalizer main.cpp)

qt_add_qml_module(normalizer
    URI normalizerqml
    NO_RESOURCE_TARGET_PATH

    QML_FILES
        Main.qml
)

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
