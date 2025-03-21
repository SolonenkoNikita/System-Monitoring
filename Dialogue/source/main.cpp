#include <process/process.hpp>
#include <parser/parser.hpp>
//#include <System/System.hpp>
#include <Display/Display.hpp>

int main() 
{
    System &system = System::get_instance();
    initscr(); 
    noecho();  
    cbreak();
    //keypad(stdscr, TRUE);
    start_color();
    int x_max{getmaxx(stdscr)};
    WINDOW *system_window = newwin(9, x_max - 1, 0, 0);
    WINDOW *process_window = newwin(3 + system.get_processes().size(), x_max - 1,
                                    system_window->_maxy + 1, 0);
    int scroll_offset = 0;
    while (true) 
    {
        init_pair(1, COLOR_MAGENTA, COLOR_BLACK);
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

        /*int ch = getch();
        if (ch == KEY_UP) {
            if (scroll_offset > 0) {
            --scroll_offset; // Прокрутка вверх
            }
        } else if (ch == KEY_DOWN) {
            if (scroll_offset <
                system.get_processes().size() - max_visible_rows) {
            ++scroll_offset; // Прокрутка вниз
            }
        }*/

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    endwin();

    /*process pr(1);
    for(int  i = 0; i < 10; ++i)
    {
        std::cout << "PID: " << pr.get_pid() << " USER " << pr.user() << " PRI "
                << pr.pri() << " VIRT " << pr.get_rams()[0] << " RES "
                << pr.get_rams()[1] << " S " << pr.stat() << " CPU% "
                << pr.cpu();
        std::cout << "\n\n";
        //std::this_thread::sleep_for(std::chrono::seconds(1));
    }*/

    /*System &system = System::get_instance();

    system.run();*/
    return 0;
}