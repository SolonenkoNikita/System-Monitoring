#pragma once

#include <Directories/Directories.hpp>

#include <algorithm>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>

unsigned get_uid(unsigned);

std::string get_user(unsigned);

std::vector<unsigned> get_pids();

std::string get_command(unsigned);

size_t get_ram(unsigned, const std::string&);

size_t get_total_processes();

size_t get_running_processes();

std::string get_process_uptime(unsigned);