#include "System/System.hpp"

System::System()
{
    std::vector<unsigned> pids = get_pids();
    for(auto num : pids)
    {
        values_.emplace(num);
        process_.emplace_back(std::move(process(num)));
    }
}

void System::update(const std::vector<unsigned>& pids_)
{
    for(auto i : pids_)
    {
        auto it = values_.find(i);
        if(it == values_.cend())
        {
            values_.emplace(i);
            process_.emplace_back(std::move(process(i)));
        }
    }
    std::string current_user = getenv("USER");
    std::sort(process_.begin(), process_.end(), [&current_user](const process& a, const process&b) 
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