#include "parser/parser.hpp"

unsigned get_uid(unsigned pid)
{
    const std::string file_path = proc + std::to_string(pid) + status;
    std::ifstream file_stream(file_path);
    if (!file_stream.is_open()) 
    {
        std::cerr << "Open file error: " << file_path << '\n';
        return std::numeric_limits<unsigned>::max(); 
    }
    std::string line;
    while (std::getline(file_stream, line)) 
    {
        if (line.find("Uid:") == 0) 
        {
            std::istringstream iss(line);
            std::string key;
            unsigned uid;
            iss >> key >> uid; 
            file_stream.close();
            return uid; 
        }
    }
    file_stream.close();
    std::cerr << "Uid has not found at " << file_path << '\n';
    return std::numeric_limits<unsigned>::max();
}

std::string get_user(unsigned pid)
{
    std::ifstream file_stream(passwd);
    if(!file_stream)
    {
        std::cerr << "Open file error: " << passwd << '\n';
        return "";
    }
    unsigned Uid = get_uid(pid), id;
    if(Uid == std::numeric_limits<unsigned>::max())
    {
        std::cerr << "Error Uid\n";
        return "";
    }
    std::string line, user;
    while (std::getline(file_stream, line))
    {
        std::replace(line.begin(), line.end(), ':', ' ');
        std::istringstream iss(line);
        char x;
        iss >> user >> x >> id;
        if(Uid == id)
        {
            file_stream.close();
            return user;
        }
    }
    file_stream.close();
    return "";
}

std::vector<unsigned> get_pids() 
{ 
    std::vector<unsigned> pids;
    for (const auto &entry : std::filesystem::directory_iterator(proc)) 
    {
        const auto &name = entry.path().filename().string();

        if (std::all_of(name.begin(), name.end(), ::isdigit)) 
            pids.emplace_back(std::stoul(name));   
    }
    return pids;
}

std::string get_command(unsigned pid)
{
    std::string line;
    const std::string file_path = proc + std::to_string(pid) + cmdline;
    std::ifstream file_stream(file_path);
    if (!file_stream.is_open()) 
    {
      std::cerr << "Open file error: " << file_path << '\n';
      return "";
    }
    std::getline(file_stream, line);
    file_stream.close();
    return line;
}

size_t get_ram(unsigned pid, const std::string& type)
{
    std::string file_path = proc + std::to_string(pid) + status;
    std::ifstream file_stream(file_path);
    if (!file_stream.is_open()) 
    {
        std::cerr << "Open file error: " << file_path << '\n';
        return std::numeric_limits<size_t>::max();
    }
    std::string line;
    while (std::getline(file_stream, line)) 
    {
        if (line.find(type)) 
        {
            std::istringstream iss(line);
            std::string key;
            size_t ram;

            iss >> key >> ram;
            file_stream.close();
            return ram;
        }
    }
    file_stream.close();
    std::cerr << "Type " << type << " hasn't found at" <<  file_path << '\n';
    return std::numeric_limits<size_t>::max();
}

size_t get_total_processes() 
{
    const std::string file_path = proc + stat;
    std::ifstream file_stream(file_path);
    if (!file_stream.is_open()) 
    {
        std::cerr << "Open file error: " << file_path << '\n';
        return std::numeric_limits<size_t>::max();
    }
    std::string line, key;
    size_t value;
    if (file_stream.is_open()) 
    {
        while (std::getline(file_stream, line)) 
        {
            std::istringstream iss(line);
            iss >> key >> value;
            if (key == "processes") 
            {
                file_stream.close();
                return value;
            }
        }
    }
    file_stream.close();
    std::cerr << "Total process hasn't found at" << file_path << '\n';
    return std::numeric_limits<size_t>::max();
}

size_t get_running_processes()
{
    const std::string file_path = proc + stat;
    std::ifstream file_stream(file_path);
    if (!file_stream.is_open()) 
    {
        std::cerr << "Open file error: " << file_path << '\n';
        return std::numeric_limits<size_t>::max();
    }
    std::string line, key;
    size_t value;
    if (file_stream.is_open()) 
    {
        while (std::getline(file_stream, line)) 
        {
            std::istringstream iss(line);
            iss >> key >> value;
            if (key == "procs_running") 
            {
                file_stream.close();
                return value;
            }
        }
    }
    file_stream.close();
    std::cerr << "Information about running process hasn't found at" << file_path << '\n';
    return std::numeric_limits<size_t>::max();
}

std::string get_process_uptime(unsigned pid) 
{
    const std::string file_path = proc + std::to_string(pid) + stat;
    std::ifstream file_stream(file_path);
    if (!file_stream.is_open()) 
    {
        std::cerr << "Open file error: " << file_path << '\n';
        return "0:00:00.00";
    }
    std::string line;
    if (!std::getline(file_stream, line)) 
    {
        std::cerr << "Couldn't read the file " << file_path << '\n';
        file_stream.close();
        return "0:00:00.00";
    }
    file_stream.close();
    std::istringstream iss(line);
    std::string token;

    for (unsigned short i = 0; i < 13; ++i) 
    {
        if (!(iss >> token)) 
        {
            std::cerr << "Error parsing from " << file_path << '\n';
            return "0:00:00.00";
        }
    }
    unsigned long user_time, system_time;
    if (!(iss >> user_time >> system_time)) 
    {
        std::cerr << "Error read UpTime from " << file_path << '\n';
        return "0:00:00.00";
    }
    unsigned long total_time = user_time + system_time;

    double total_seconds = static_cast<double>(total_time) / sysconf(_SC_CLK_TCK);
    int hours = static_cast<int>(total_seconds / 3600);
    int minutes = static_cast<int>(std::fmod(total_seconds / 60, 60));
    int seconds = static_cast<int>(total_seconds) % 60;
    int hundredths = static_cast<int>((total_seconds - static_cast<int>(total_seconds)) * 100);
    std::ostringstream oss;
    oss << hours << ":" << std::setfill('0') << std::setw(2) << minutes << ":"
        << std::setw(2) << seconds << "." << std::setw(2) << hundredths;
    return oss.str();
}