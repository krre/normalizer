#pragma once
#include <QString>
#include <QObject>
#include "CommonTypes.h"

namespace Const {

namespace App {
    constexpr auto Organization = "Norm Group";
    constexpr auto Name = "Normalizer";
    constexpr auto Status = ""; // Release, Beta, Alpha
    constexpr auto Url = "https://github.com/krre/normalizer";
    constexpr auto CopyrightYear = "2022";
    constexpr auto BuildDate = __DATE__;
    constexpr auto BuildTime = __TIME__;
}

namespace Window {
    constexpr int MaxRecentFiles = 10;
    constexpr auto BackgroundColor = 0x4d4d4f;
}

namespace Project {
    constexpr auto WorkspaceDir = "NormProjects";
    constexpr auto DataDir = ".normalizer";
    constexpr auto OutputDir = "output";
    constexpr auto SettingsFile = "settings.json";
    constexpr auto SessionFile = "session.json";

    namespace Extension {
        constexpr auto Binary = ".norm";
    }

    namespace Target {
        namespace Application {
            const QString Name = QObject::tr("Application");
            constexpr auto Source = "app";
        }

        namespace Library {
            const QString Name = QObject::tr("Library");
            constexpr auto Source = "lib";
        }
    }
}

namespace Norm {
    namespace Token {
        using namespace ::Norm;

        constexpr Code Project        = 0x00;
        constexpr Code Version        = 0x01;
        constexpr Code Name           = 0x02;
        constexpr Code Module         = 0x03;
        constexpr Code Function       = 0x04;
        constexpr Code Parameter      = 0x05;
        constexpr Code Math           = 0x06;
        constexpr Code StringLiteral  = 0x07;
        constexpr Code NumberLiteral  = 0x08;
        constexpr Code BooleanLiteral = 0x09;
    }
}

}
