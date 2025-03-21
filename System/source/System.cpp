#include "System/System.hpp"

System::System()
{
    std::vector<unsigned> pids = get_pids();
    for(auto num : pids)
        process_.emplace_back(std::move(process(num)));
}

void System::run() const noexcept
{
    while(true)
    {
        /*for(auto pr : process_)
        {
            std::cout << "PID: " << pr.get_pid() << " RES " << pr.get_rams() << " Command " << pr.command() << "\n\n";
        }*/
        //std::this_thread::sleep_for(std::chrono::seconds(10));
    }
}