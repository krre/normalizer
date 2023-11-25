#pragma once

namespace Const {

namespace App {
    constexpr auto Organization = "Norm Group";
    constexpr auto Name = "Normalizer";
    constexpr auto Version = "0.1.0";
    constexpr auto URL = "https://github.com/krre/normalizer";
    constexpr auto CopyrightYear = "2022-2023";
    constexpr auto BuildDate = __DATE__;
    constexpr auto BuildTime = __TIME__;
}

namespace Norm {
    constexpr auto Magic = "norm";
    constexpr auto Version = "0.1";
}

namespace HttpStatus {
    constexpr auto BadRequest = 400;
    constexpr auto Unauthorized = 401;
    constexpr auto NotFound = 404;
    constexpr auto Conflict = 409;
}

}
