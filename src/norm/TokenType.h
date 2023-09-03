#pragma once
#include <stdint.h>

namespace Norm {

using TokenId = uint16_t;
using TokenSize = uint16_t;

enum class TokenType : uint8_t {
    Invalid,
    Project
};

}
