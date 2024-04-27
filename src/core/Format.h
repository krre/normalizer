#pragma once
#include <format>
#include <QString>

// template <>
// struct std::formatter<QString> : std::formatter<std::string_view> {
//     template<class FormatContext>
//     auto format(const QString& str, FormatContext& fc) const {
//         return std::formatter<std::string_view>::format(str.toStdString(), fc);
//     }
// };
