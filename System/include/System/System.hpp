#pragma once

#include <process/process.hpp>

#include <chrono>
#include <memory>
#include <thread>
#include <algorithm>
#include <unordered_set>

/**
 * @brief Represents the system and manages processes.
 *
 * This class is a singleton that provides access to the list of processes
 * running on the system. It allows updating the list of processes and
 * retrieving them in a sorted order.
 */
class System final
{
public:

    /**
     * @brief Returns the singleton instance of the `System` class.
     * @return A reference to the singleton instance.
     */
    [[nodiscard]] static System& get_instance() noexcept 
    {
        static System instance;
        return instance;
    }

    /**
     * @brief Returns the list of processes (const version).
     * @return A constant reference to the vector of processes.
     */
    [[nodiscard]] const std::vector<process>& get_processes() const noexcept;

    /**
     * @brief Returns the list of processes (non-const version).
     * @return A reference to the vector of processes.
     */
    [[nodiscard]] std::vector<process> &get_processes() noexcept;

    System(const System &) = delete;
    System& operator=(const System &) = delete;

    /**
     * @brief Updates the list of processes with the given PIDs.
     *
     * This method adds new processes to the list and sorts them by their state
     * (running processes first) and PID.
     *
     * @param pids_ A vector of process IDs (PIDs) to update the list with.
     */
    void update(const std::vector<unsigned>& pids_);

private:
    /**
     * @brief Private constructor to enforce singleton pattern.
     * 
     * Initializes the `System` object by retrieving the list of PIDs and creating
     * `process` objects for each PID.
     */
    System();
    std::vector<process> process_;
    std::unordered_set<unsigned> values_;
};