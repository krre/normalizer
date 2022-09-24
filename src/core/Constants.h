#pragma once
#include <QString>
#include <QObject>

namespace Const {

namespace App {
    constexpr auto Organization = "Norm Group";
    constexpr auto Name = "Normalizer";
    constexpr auto Version = "0.1.0";
    constexpr auto Status = ""; // Release, Beta, Alpha
    constexpr auto Url = "https://github.com/krre/normalizer";
    constexpr auto CopyrightYear = "2022";
    constexpr auto BuildDate = __DATE__;
    constexpr auto BuildTime = __TIME__;
}

namespace Window {
    constexpr int MaxRecentFiles = 10;
}

namespace Project {
    constexpr auto WorkspaceDir = "NormProjects";
    constexpr auto DataDir = ".normalizer";
    constexpr auto OutputDir = "output";
    constexpr auto SettingsFile = "settings.json";
    constexpr auto SessionFile = "session.json";

    namespace Target {
        namespace Application {
            const QString Name = QObject::tr("Application");
            constexpr auto Source = "app.norm";
        }

        namespace Library {
            const QString Name = QObject::tr("Library");
            constexpr auto Source = "lib.norm";
        }
    }
}

namespace Norm {
    constexpr auto Version = "0.1.0";
}

}
