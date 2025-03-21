#include "System/System.hpp"

System::System()
{
    std::vector<unsigned> pids = get_pids();
    for(auto num : pids)
        process_.emplace_back(std::move(process(num)));
    
    std::sort(process_.begin(), process_.end(), [](const process& a, const process&b) 
    {
        if (a.stat() == 'R' && b.stat() != 'R') 
            return true;
        if (b.stat() == 'R' && a.stat() != 'R') 
            return false;
        return a.get_pid() < b.get_pid();
    });
}

[[nodiscard]] const std::vector<process>& System::get_processes() const noexcept
{
    return process_;
}

[[nodiscard]] std::vector<process>& System::get_processes() noexcept
{
    return process_;
}