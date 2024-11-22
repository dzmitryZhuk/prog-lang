#pragma once

#include <string>

namespace utils
{
    enum class ARCH
    {
        arm,
        arm64,
        x86,
        x64
    };

    enum class OS
    {
        win,
        linux,
        mac
    };

    std::string getTimestamp();   
} // namespace utils
