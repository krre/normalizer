qt_add_executable(normalizer main.cpp)

qt_add_qml_module(normalizer
    URI normalizerqml
    NO_RESOURCE_TARGET_PATH

    QML_FILES
        qml/Main.qml
        qml/toolbar/AppToolBar.qml
        qml/toolbar/menu/AboutDialog.qml
        qml/toolbar/menu/AppMenu.qml
        qml/toolbar/account/AccountPopup.qml
        qml/toolbar/account/SignInDialog.qml
        qml/toolbar/account/SignUpDialog.qml
        QML_FILES qml/dialog/ErrorDialog.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(normalizer PROPERTIES
    OUTPUT_NAME "Normalizer"
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appmemo
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    # QT_ANDROID_PACKAGE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/android
)

target_link_libraries(normalizer PRIVATE
    common
)

include(GNUInstallDirs)

install(TARGETS normalizer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
