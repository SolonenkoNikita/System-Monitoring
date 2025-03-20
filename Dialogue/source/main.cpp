#include <parser/parser.hpp>

#include <chrono>
#include <thread>

int main() 
{ 
    int pid = 161812;
    while (true) 
    {
      std::string time_plus = get_process_uptime(pid);
      std::cout << "TIME+ процесса " << pid << ": " << time_plus << std::flush << '\n';

      
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}