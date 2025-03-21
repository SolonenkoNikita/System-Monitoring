#include "process/process.hpp"
#include <parser/parser.hpp>

#include <System/System.hpp>

int main() 
{
    process pr(1);
    for(int  i = 0; i < 10; ++i) 
    {
        std::cout << "PID: " << pr.get_pid() << " USER " << pr.user() << " PRI "
                << pr.pri() << " VIRT " << pr.get_rams()[0] << " RES "
                << pr.get_rams()[1] << " S " << pr.stat() << " CPU% "
                << pr.cpu();
        std::cout << "\n\n";
        //std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    
              
    /*System &system = System::get_instance();

    system.run();*/
    return 0;
}