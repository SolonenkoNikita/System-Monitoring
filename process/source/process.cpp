#include "process/process.hpp"

#include <string>

process::process(unsigned pid) : pid_(pid) 
{
    cpu_ = cpu_proc_utilization(pid);
    command_ = get_command(pid);
    user_ = get_user(pid);
    virt_ = get_ram(pid, "VmSize:");
    res_ = get_ram(pid, "VmRSS:");
    stat_ = get_stat(pid);
    pri_ = get_pri(pid);
}

[[nodiscard]] unsigned process::get_pid() const noexcept 
{ 
    return pid_; 
}

[[nodiscard]] const std::string& process::command() const noexcept 
{
    return command_;
}

[[nodiscard]] std::string &process::command() noexcept 
{ 
    return command_; 
}

[[nodiscard]] double process::get_virt() const noexcept
{
    return virt_;
}

[[nodiscard]] double process::get_res() const noexcept 
{ 
    return res_; 
}

[[nodiscard]] const std::string& process::user() const noexcept 
{
    return user_;
}

[[nodiscard]] std::string& process::user() noexcept 
{ 
    return user_; 
}

[[nodiscard]] char process::stat() const noexcept
{
    return stat_;
}

[[nodiscard]] int process::pri() const noexcept
{
    return pri_;
}

[[nodiscard]] double process::cpu() const noexcept
{
    return cpu_;
}