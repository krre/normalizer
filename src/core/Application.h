#pragma once
#include "src/config.h"
#include <QGuiApplication>

class Application : public QGuiApplication {
    Q_OBJECT
    Q_PROPERTY(QString name READ name CONSTANT)
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
    QString name() const { return Name; }
};
