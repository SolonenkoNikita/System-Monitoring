#pragma once

#include <System/System.hpp>
#include <Utils/Utils.hpp>

#include <curses.h>
#include <fmt/core.h>

/**
 * @brief Generates a progress bar string based on a percentage.
 *
 * This function creates a visual representation of a percentage using a bar
 * filled with `|` characters. The length of the bar can be customized.
 *
 * @param percent The percentage to represent (0 to 100).
 * @param bar_length The length of the bar (default is 20).
 * @return A string representing the progress bar (e.g., "[|||||     ]").
 */
inline std::string generate_bar(double percent, int bar_length = 20)
{
    int filled = static_cast<int>(percent / 100 * bar_length);
    int empty = bar_length - filled;

    std::string bar(filled, '|');
    bar += std::string(empty, ' ');

    return "[" + bar + "]";
}

/**
 * @brief Displays the list of processes in a curses window.
 *
 * This function renders the list of processes in a curses window, showing
 * details such as PID, user, priority, memory usage, CPU usage, and more.
 *
 * @param processes The list of processes to display.
 * @param window The curses window where the processes will be displayed.
 */
void display_processes(std::vector<process> &, WINDOW *);

/**
 * @brief Displays system information in a curses window.
 *
 * This function renders system information such as OS, kernel version, memory
 * usage, CPU usage, and process statistics in a curses window.
 *
 * @param window The curses window where the system information will be
 * displayed.
 */
void display_system_info(WINDOW*);

/**
 * @brief Runs the main loop of the system monitoring application.
 *
 * This function initializes the curses environment, creates windows for
 * displaying system information and processes, and continuously updates the
 * display.
 *
 * @param system The `System` object containing the list of processes.
 */
void run(System&);