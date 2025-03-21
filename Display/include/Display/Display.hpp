#pragma once

#include <System/System.hpp>
#include <Utils/Utils.hpp>

#include <curses.h>

void display_processes(const std::vector<process>&, WINDOW*);

void display_system_info(WINDOW*);