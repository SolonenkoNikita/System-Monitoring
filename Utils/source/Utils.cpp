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

std::string return_correct_time(double seconds) 
{
    int total_seconds = static_cast<int>(seconds);

    int days = total_seconds / 86400; 
    total_seconds %= 86400;

    int hours = total_seconds / 3600; 
    total_seconds %= 3600;

    int minutes = total_seconds / 60; 
    int secs = total_seconds % 60;

    std::ostringstream oss;
    if (days > 0) 
        oss << days << " day ";
    if (hours > 0) 
        oss << hours << " hour ";
    if (minutes > 0) 
        oss << minutes << " minutes ";
    if (secs > 0 || (days == 0 && hours == 0 && minutes == 0)) 
        oss << secs << " seconds ";

  return oss.str();
}

double calculate_cpu_usage(const cpu::cpu_usage& prev, const cpu::cpu_usage& curr) 
{
    long prev_total = prev.user_ + prev.nice_ + prev.system_ + prev.idle_ + prev.iowait_ 
                        + prev.irq_ + prev.softirq_ + prev.steal_ + prev.guest_ + prev.guest_nice_;

    long curr_total = curr.user_ + curr.nice_ + curr.system_ + curr.idle_ + curr.iowait_ + curr.irq_ 
                        + curr.softirq_ + curr.steal_ + curr.guest_ + curr.guest_nice_;

    long total_diff = curr_total - prev_total;
    long idle_diff = curr.idle_ - prev.idle_;

    if (total_diff == 0) 
        return 0.0; 
    return 100.0 * (total_diff - idle_diff) / total_diff;
}