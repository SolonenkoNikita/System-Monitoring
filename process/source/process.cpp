#include "process/process.hpp"
#include <string>

process::process(unsigned pid) : pid_(pid) 
{
    cpu_ = cpu_proc_utilization(pid);
    command_ = get_command(pid);
    user_ = get_user(pid);
    rams_[0] = get_ram(pid, "VmSize:", 1024 * 1024);
    rams_[1] = get_ram(pid, "VmRSS:", 1024);
    rams_[2] = get_ram(pid, "VmData:", 1);
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

[[nodiscard]] const std::array<double, 3>& process::get_rams() const noexcept 
{
  return rams_;
}

[[nodiscard]] std::array<double, 3>& process::get_rams() noexcept 
{
  return rams_;
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