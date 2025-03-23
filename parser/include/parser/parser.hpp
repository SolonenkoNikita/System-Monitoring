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

/**
 * @brief Retrieves the UID (User ID) of a process by its PID.
 * @param pid The process ID (PID).
 * @return The UID of the process, or `std::numeric_limits<unsigned>::max()` on error.
 */
unsigned get_uid(unsigned);

/**
 * @brief Retrieves the username associated with a process by its PID.
 * @param pid The process ID (PID).
 * @return The username, or an empty string on error.
 */
std::string get_user(unsigned);

/**
 * @brief Retrieves a list of all PIDs (Process IDs) in the system.
 * @return A vector of PIDs.
 */
std::vector<unsigned> get_pids();

/**
 * @brief Retrieves the command that started a process.
 * @param pid The process ID (PID).
 * @return The command, or an empty string on error.
 */
std::string get_command(unsigned);

/**
 * @brief Retrieves the RAM usage of a process.
 * @param pid The process ID (PID).
 * @param type The type of RAM to retrieve (e.g., "VmSize" or "VmRSS").
 * @return The RAM usage in bytes, or std::numeric_limits<double>::max() on error.
 */
double get_ram(unsigned, const std::string&);

/**
 * @brief Retrieves the total number of processes in the system.
 * @return The total number of processes, or std::numeric_limits<size_t>::max() on error.
 */
size_t get_total_processes();

/**
 * @brief Retrieves the number of running processes in the system.
 * @return The number of running processes, or std::numeric_limits<size_t>::max() on error.
 */
size_t get_running_processes();

/**
 * @brief Retrieves the uptime of a process in the format "HH:MM:SS.MS".
 * @param pid The process ID (PID).
 * @return The uptime as a formatted string, or "0:00:00.00" on error.
 */
std::string get_process_uptime(unsigned);

/**
 * @brief Retrieves the state of a process (e.g., 'R' for running, 'S' for sleeping).
 * @param pid The process ID (PID).
 * @return The process state, or '?' on error.
 */
char get_stat(unsigned);

/**
 * @brief Retrieves the priority of a process.
 * @param pid The process ID (PID).
 * @return The process priority, or std::numeric_limits<int>::min() on error.
 */
int get_pri(unsigned);

/**
 * @brief Retrieves the system uptime in seconds.
 * @return The system uptime, or `std::numeric_limits<double>::min()` on error.
 */
double up_time();

/**
 * @brief Calculates the CPU utilization of a process.
 * @param pid The process ID (PID).
 * @return The CPU utilization as a percentage, or std::numeric_limits<double>::min() on error.
 */
double cpu_proc_utilization(unsigned);

/**
 * @brief Retrieves the operating system name.
 * @return The OS name, or an empty string on error.
 */
std::string get_os();

/**
 * @brief Retrieves the kernel version.
 * @return The kernel version, or an empty string on error.
 */
std::string get_kernel();

namespace used_memory 
{
    struct memory_info 
    {
        double used_;
        double total_;
        double percent_;
    };
}

/**
 * @brief Retrieves memory usage information.
 * @return A memory_info struct containing used, total, and percentage of memory.
 */
used_memory::memory_info get_memory();

namespace cpu
{
    struct cpu_usage 
    {
        long user_;       
        long nice_;      
        long system_;    
        long idle_;      
        long iowait_;   
        long irq_;      
        long softirq_;  
        long steal_;     
        long guest_;     
        long guest_nice_;
    };
}

/**
 * @brief Retrieves CPU usage information.
 * @return A cpu_usage struct containing CPU usage data.
 * @throws std::runtime_error if the CPU data cannot be read.
 */
cpu::cpu_usage get_cpu();
