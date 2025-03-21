#include "Utils/Utils.hpp"

std::string format_memory(double bytes) 
{
    const char *units[] = {"B", "KB", "MB", "GB", "TB"};
    int unit_index = 0;

    while (bytes >= 1024 && unit_index < 4) 
    {
        bytes /= 1024;
        ++unit_index;
    }

    std::ostringstream oss;
    if (bytes == std::floor(bytes))
        oss << std::fixed << std::setprecision(0) << bytes << " "
            << units[unit_index];
    else
        oss << std::fixed << std::setprecision(2) << bytes << " "
            << units[unit_index];
    return oss.str();
}