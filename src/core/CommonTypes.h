#pragma once
#include <QFlags>

enum FileFormat {
    BinaryFormat,
    JsonFormat
};

Q_DECLARE_FLAGS(FileFormats, FileFormat)
Q_DECLARE_OPERATORS_FOR_FLAGS(FileFormats)
