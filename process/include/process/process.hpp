#pragma once

#include <parser/parser.hpp>

#include <array>

/**
 * @brief Represents a process in the system.
 *
 * This class encapsulates information about a process, such as its PID, CPU
 * usage, command, user, memory usage, state, and priority.
 */
class process final
{
public:
    /**
     * @brief Constructs a `process` object for the given PID.
     * @param pid The process ID (PID) of the process.
     */
    process(unsigned);

    /**
     * @brief Returns the PID of the process.
     * @return The process ID (PID).
     */
    [[nodiscard]] unsigned get_pid() const noexcept;

    /**
     * @brief Returns the command that started the process (const version).
     * @return The command as a constant reference to a string.
     */
    [[nodiscard]] const std::string& command() const noexcept;

    /**
     * @brief Returns the command that started the process (non-const version).
     * @return The command as a reference to a string.
     */
    [[nodiscard]] std::string& command() noexcept;

    /**
     * @brief Returns the username of the process owner (const version).
     * @return The username as a constant reference to a string.
     */
    [[nodiscard]] const std::string& user() const noexcept;

    /**
     * @brief Returns the username of the process owner (non-const version).
     * @return The username as a reference to a string.
     */
    [[nodiscard]] std::string& user() noexcept;

    /**
     * @brief Returns the virtual memory usage of the process.
     * @return The virtual memory usage in bytes.
     */
    [[nodiscard]] double get_virt() const noexcept;

    /**
     * @brief Returns the resident memory usage of the process.
     * @return The resident memory usage in bytes.
     */
    [[nodiscard]] double get_res() const noexcept;

    /**
     * @brief Returns the current state of the process.
     * @return The process state as a character (e.g., 'R' for running, 'S' for sleeping).
     */
    [[nodiscard]] char stat() const noexcept;

    /**
     * @brief Returns the priority of the process.
     * @return The process priority.
     */
    [[nodiscard]] int pri() const noexcept;

    /**
     * @brief Returns the CPU usage of the process.
     * @return The CPU usage as a percentage.
     */
    [[nodiscard]] double cpu() const noexcept;

private:
    unsigned pid_;
    double cpu_;
    std::string command_;
    std::string user_;
    double virt_;
    double res_; 
    char stat_;
    int pri_;
};