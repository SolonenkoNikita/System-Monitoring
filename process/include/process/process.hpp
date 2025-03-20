#pragma once

class process {
public:
    process(unsigned);

    unsigned get_pid() const noexcept;

private:
    unsigned pid_;
    double cpu_;
};