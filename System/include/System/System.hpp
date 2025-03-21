#pragma once

#include <process/process.hpp>

#include <chrono>
#include <memory>
#include <thread>

class System final
{
public:
    [[nodiscard]] static System& get_instance() noexcept 
    {
        static System instance;
        return instance;
    }

    [[nodiscard]] const std::vector<process>& get_processes() const noexcept;

    [[nodiscard]] std::vector<process> &get_processes()noexcept;

    System(const System &) = delete;
    System& operator=(const System &) = delete;

    void run() const noexcept;
private:
    System();
    std::vector<process> process_;
};