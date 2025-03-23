#pragma once

#include <cmath>
#include <iomanip>
#include <sstream>
#include <string>

#include <parser/parser.hpp>

/**
 * @brief Formats a memory size in bytes into a human-readable string.
 *
 * This function converts a memory size in bytes to a more readable format,
 * such as KB, MB, GB, or TB, depending on the size.
 *
 * @param bytes The memory size in bytes.
 * @return A formatted string representing the memory size (e.g., "1.23 GB").
 */
std::string format_memory(double);

/**
 * @brief Converts a time duration in seconds into a human-readable string.
 * 
 * This function converts a time duration in seconds into a string that includes
 * days, hours, minutes, and seconds.
 * 
 * @param seconds The time duration in seconds.
 * @return A formatted string representing the time duration (e.g., "1 day 2 hours 30 minutes").
 */
std::string return_correct_time(double);

/**
 * @brief Calculates the CPU usage percentage between two CPU usage snapshots.
 *
 * This function calculates the CPU usage percentage by comparing two snapshots
 * of CPU usage data (e.g., from `/proc/stat`).
 *
 * @param prev The previous CPU usage snapshot.
 * @param curr The current CPU usage snapshot.
 * @return The CPU usage as a percentage (e.g., 25.5 for 25.5%).
 */
double calculate_cpu_usage(const cpu::cpu_usage&, const cpu::cpu_usage&);
