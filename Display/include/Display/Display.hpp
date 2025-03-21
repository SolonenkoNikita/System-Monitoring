#pragma once

#include <System/System.hpp>
#include <Utils/Utils.hpp>

#include <curses.h>
#include <fmt/core.h>

inline std::string generate_bar(double percent, int bar_length = 20)
{
    int filled = static_cast<int>(percent / 100 * bar_length);
    int empty = bar_length - filled;

    std::string bar(filled, '|');
    bar += std::string(empty, ' ');

    return "[" + bar + "]";
}

void display_processes(const std::vector<process> &, WINDOW *);

void display_system_info(WINDOW*);

void run(const System&);