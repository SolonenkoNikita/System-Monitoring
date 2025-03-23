#include "Display/Display.hpp"

void display_processes(std::vector<process>& processes, WINDOW *window) 
{
    int row {0};
    const int pid_column {2};
    const int user_column {9};
    const int pri_colomn {22};
    const int virt_colomn {26};
    const int res_colomn {40};
    const int s_colomn {52};
    const int cpu_column {55};
    const int time_column {63};
    const int command_column {75};
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
        processes.erase(std::remove_if(processes.begin(), processes.end(), [](const process &p) 
                            {
                                return !std::filesystem::exists( proc 
                                + std::to_string(p.get_pid()) + stat); 
                            }), processes.end());
        
        mvwprintw(window, ++row, pid_column, "%s", std::to_string(processes[i].get_pid()).c_str());
        mvwprintw(window, row, user_column, "%s", processes[i].user().c_str());
        mvwprintw(window, row, pri_colomn,  "%s", std::to_string(processes[i].pri()).c_str());
        mvwprintw(window, row, virt_colomn, "%s", format_memory(processes[i].get_virt()).c_str());
        mvwprintw(window, row, res_colomn, "%s", format_memory(processes[i].get_res()).c_str());
        mvwprintw(window, row, s_colomn, "%s", std::string(1, processes[i].stat()).c_str());
        double cpu = processes[i].cpu();
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
    const int total_proc {1};
    const int run_proc {1};
    const int up_times {1};
    const int memory_colomn {1};
    const int os_column {1};
    wattron(window, COLOR_PAIR(1));
    mvwprintw(window, ++row, os_colomn, "%s", std::string("OS: " + get_os()).c_str());
    mvwprintw(window, ++row, os_colomn, "%s", std::string("VERSION: " + get_kernel()).c_str());

    used_memory::memory_info memory = get_memory();
    std::string memory_bar = generate_bar(memory.percent_);
    std::string memory_text = fmt::format("{:.1f} GB / {:.1f} GB {}", memory.used_ / 1024 / 1024,
                    memory.total_ / 1024 / 1024, memory_bar);
    if (memory.percent_ > 80) 
      wattron(window, COLOR_PAIR(3)); 
    else
      wattron(window, COLOR_PAIR(2)); 
    mvwprintw(window, ++row, memory_colomn, "%s", ("MEMORY: " + memory_text).c_str());
    try 
    {
        cpu::cpu_usage prev_usage = get_cpu();
        cpu::cpu_usage curr_usage = get_cpu();

        double cpu_percent = calculate_cpu_usage(prev_usage, curr_usage);
        std::string cpu_bar = generate_bar(cpu_percent);
        std::string cpu_text = fmt::format("CPU: {:.1f}% {}", cpu_percent, cpu_bar);

        if (cpu_percent > 80)
            wattron(window, COLOR_PAIR(3));
        else
            wattron(window, COLOR_PAIR(2));
        mvwprintw(window, ++row, os_column, "%s", cpu_text.c_str());

        wattroff(window, COLOR_PAIR(3));
        wattroff(window, COLOR_PAIR(2));
    } 
    catch (const std::exception &e) 
    {
        mvwprintw(window, ++row, os_column, "Error reading CPU usage: %s", e.what());
    }
    wattron(window, COLOR_PAIR(1));
    mvwprintw(window, ++row, total_proc, "%s", 
            ("TOTAL PROCESSES: " + std::to_string(get_total_processes())).c_str());
    mvwprintw(window, ++row, run_proc, "%s",
            ("RINNING PROCESSES: " + std::to_string(get_running_processes())).c_str());
    mvwprintw(window, ++row, up_times, "%s", 
            ("UP TIME: " + return_correct_time(up_time())).c_str());
    wattroff(window, COLOR_PAIR(1));
}

void run(System &system)
{
    initscr();
    noecho();
    cbreak();
    start_color();
    int x_max{getmaxx(stdscr)};
    WINDOW *system_window = newwin(9, x_max - 1, 0, 0);
    WINDOW *process_window = newwin(3 + system.get_processes().size(), x_max - 1, system_window->_maxy + 1, 0);
    while (true) 
    {
        std::vector<unsigned> pids = get_pids();
        system.update(pids);
        init_pair(1, COLOR_WHITE, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
        int max_visible_rows = process_window->_maxy - 1;
        werase(system_window);
        werase(process_window);

        box(system_window, 0, 0);
        box(process_window, 0, 0);
        display_system_info(system_window);
        display_processes(system.get_processes(), process_window);
        wrefresh(system_window);
        wrefresh(process_window);
        refresh();

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    endwin();
}
