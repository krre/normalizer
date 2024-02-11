#pragma once
#include "config.h"
#include <QApplication>

class Application : public QApplication {
public:
    static constexpr auto Organization = "Norm";
    static constexpr auto Name = "Normalizer";
    static constexpr auto Version = PROJECT_VERSION;
    static constexpr auto Url = "https://github.com/krre/normalizer";
    static constexpr auto CopyrightYear = "2022-2024";
    static constexpr auto BuildDate = __DATE__;
    static constexpr auto BuildTime = __TIME__;

    Application(int& argc, char* argv[]);
    bool notify(QObject* receiver, QEvent* event) override;

private:
    void showErrorMessage(const QString& message) const;
};
