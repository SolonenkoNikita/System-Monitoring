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
#include <thread>

unsigned get_uid(unsigned);

std::string get_user(unsigned);

std::vector<unsigned> get_pids();

std::string get_command(unsigned);

double get_ram(unsigned, const std::string&, size_t);

size_t get_total_processes();

size_t get_running_processes();

std::string get_process_uptime(unsigned);

char get_stat(unsigned);

int get_pri(unsigned);

double up_time();

double cpu_proc_utilization(unsigned);