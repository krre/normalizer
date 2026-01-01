#pragma once
#include "src/config.h"
#include <QApplication>

class Application : public QApplication {
public:
    static constexpr auto Name = "Normalizer";
    static constexpr auto Organization = "Norm Group";
    static constexpr auto WorkspaceName = "Norm Projects";
    static constexpr auto Version = PROJECT_VERSION;
    static constexpr auto Url = "https://github.com/krre/normalizer";
    static constexpr auto Years = "2015-2026";
    static constexpr auto BuildDate = __DATE__;
    static constexpr auto BuildTime = __TIME__;

    Application(int& argc, char* argv[]);
};
