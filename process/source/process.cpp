#include "process/process.hpp"

process::process(unsigned pid) : pid_(pid) {}

unsigned process::get_pid() const noexcept 
{ 
    return pid_; 
}