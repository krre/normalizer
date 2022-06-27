#pragma once

namespace Const {

namespace App {
    constexpr auto Organization = "Norm";
    constexpr auto Name = "Normalizer";
    constexpr auto Version = "0.1.0";
    constexpr auto Status = ""; // Release, Beta, Alpha
    constexpr auto Url = "https://github.com/krre/normalizer";
    constexpr auto CopyrightYear = "2022";
    constexpr auto BuildDate = __DATE__;
    constexpr auto BuildTime = __TIME__;
}

namespace Norm {
    constexpr auto Name = "Norm";
    constexpr auto Extension = ".norm";
}

namespace Settings {
    namespace MainWindow {
        constexpr auto Geometry = "MainWindow/geometry";
    }

    namespace Project {
        constexpr auto Workspace = "Project/workspace";
    }

    namespace Session {
        constexpr auto Group = "Session";
        constexpr auto Restore = "Session/restore";
        constexpr auto Tab = "Session/tab";
    }

    namespace SessionList {
        constexpr auto Group = "SessionList";
        constexpr auto Path = "path";
    }
}

namespace Project {
    constexpr auto WorkspaceDir = "NormProjects";
    constexpr auto DataDir = ".norm";
    constexpr auto SessionFile = "session.json";
}

}
