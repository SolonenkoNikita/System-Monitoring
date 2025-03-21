#pragma once

#include <parser/parser.hpp>

#include <array>

class process final
{
public:
    process(unsigned);

    [[nodiscard]] unsigned get_pid() const noexcept;

    [[nodiscard]] const std::string& command() const noexcept;

    [[nodiscard]] std::string& command() noexcept;

    [[nodiscard]] const std::string& user() const noexcept;

    [[nodiscard]] std::string& user() noexcept;

    [[nodiscard]] double get_virt() const noexcept;

    [[nodiscard]] double get_res() const noexcept;

    [[nodiscard]] char stat() const noexcept;

    [[nodiscard]] int pri() const noexcept;

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