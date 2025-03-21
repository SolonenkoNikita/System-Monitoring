#pragma once

#include <cmath>
#include <iomanip>
#include <sstream>
#include <string>

#include <parser/parser.hpp>

std::string format_memory(double);

std::string return_correct_time(double);

double calculate_cpu_usage(const cpu::cpu_usage&, const cpu::cpu_usage&);
