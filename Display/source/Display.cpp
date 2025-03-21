#include "Display/Display.hpp"

void display_processes(const std::vector<process>& processes, WINDOW *window) 
{
    int row {0};
    const int pid_column {2};
    const int user_column {9};
    const int pri_colomn {22};
    const int virt_colomn {26};
    const int res_colomn {40};
    const int s_colomn {52};
    const int cpu_column {57};
    const int time_column {66};
    const int command_column {79};
    wattron(window, COLOR_PAIR(2));
    mvwprintw(window, ++row, pid_column, "PID");
    mvwprintw(window, row, user_column, "USER");
    mvwprintw(window, row, pri_colomn, "PRI");
    mvwprintw(window, row, virt_colomn, "VIRT");
    mvwprintw(window, row, res_colomn, "RES");
    mvwprintw(window, row, s_colomn, "S");
    mvwprintw(window, row, cpu_column, "CPU[%%]");
    mvwprintw(window, row, time_column, "TIME+");
    mvwprintw(window, row, command_column, "COMMAND");
    wattroff(window, COLOR_PAIR(2));
    for (unsigned i = 0; i < processes.size(); ++i) 
    {
        mvwprintw(window, ++row, pid_column, "%s", std::to_string(processes[i].get_pid()).c_str());
        mvwprintw(window, row, user_column, "%s", processes[i].user().c_str());
        mvwprintw(window, row, pri_colomn,  "%s", std::to_string(processes[i].pri()).c_str());
        mvwprintw(window, row, virt_colomn, "%s", format_memory(processes[i].get_virt()).c_str());
        mvwprintw(window, row, res_colomn, "%s", format_memory(processes[i].get_res()).c_str());
        mvwprintw(window, row, s_colomn, "%s", std::string(1, processes[i].stat()).c_str());
        double cpu = processes[i].cpu() * 100;
        mvwprintw(window, row, cpu_column, "%s", std::to_string(cpu).substr(0, 4).c_str());
        mvwprintw(window, row, time_column, "%s", get_process_uptime(processes[i].get_pid()).c_str());
        mvwprintw(window, row, command_column, "%s",
                    processes[i].command().substr(0, window->_maxx - 46).c_str());
    }
}

void display_system_info(WINDOW* window) 
{
    int row {0};
    const int os_colomn {1};
    const int kernel_colomn {1};
    wattron(window, COLOR_PAIR(1));
    mvwprintw(window, ++row, os_colomn, "%s", std::string("OS: " + get_os()).c_str());
    mvwprintw(window, ++row, os_colomn, "%s", std::string("VERSION: " + get_kernel()).c_str());
    wattroff(window, COLOR_PAIR(1));
}