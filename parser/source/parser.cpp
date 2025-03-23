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

double get_ram(unsigned pid, const std::string& type)
{
    std::string file_path = proc + std::to_string(pid) + status;
    std::ifstream file_stream(file_path);
    if (!file_stream.is_open()) 
    {
        std::cerr << "Open file error: " << file_path << '\n';
        return std::numeric_limits<double>::max();
    }
    std::string line;
    while (std::getline(file_stream, line)) 
    {
        if (line.find(type) != std::string::npos) 
        {
            std::istringstream iss(line);
            std::string key;
            double ram;

            iss >> key >> ram;
            file_stream.close();

            return ram * 1024;
        }
    }
    file_stream.close();
    std::cerr << "Type " << type << " hasn't found at" <<  file_path << '\n';
    return std::numeric_limits<double>::max();
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

char get_stat(unsigned pid) 
{
    std::string file_path = proc + std::to_string(pid) + stat;
    std::ifstream file_stream(file_path);
    if (!file_stream.is_open()) 
    {
        std::cerr << "Open file error: " << file_path << '\n';
        return '?'; 
    }

    std::string line;
    if (!std::getline(file_stream, line)) 
    {
        std::cerr << "Couldn't read the file " << file_path << '\n';
        file_stream.close();
        return '?';
    }
    file_stream.close();

    std::istringstream iss(line);
    std::string token;

    for (unsigned short i = 0; i < 2; ++i) 
    {
        if (!(iss >> token)) 
        {
        std::cerr << "Error parsing from " << file_path << '\n';
        return '?';
        }
    }

    char state;
    if (!(iss >> state)) 
    {
        std::cerr << "Error reading state from " << file_path << '\n';
        return '?';
    }

    return state;
}

int get_pri(unsigned pid) 
{
    std::string file_path = proc + std::to_string(pid) + stat;
    std::ifstream file_stream(file_path);
    if (!file_stream.is_open()) 
    {
        std::cerr << "Open file error: " << file_path << '\n';
        return std::numeric_limits<int>::min(); 
    }

    std::string line;
    if (!std::getline(file_stream, line)) 
    {
        std::cerr << "Couldn't read the file " << file_path << '\n';
        file_stream.close();
        return std::numeric_limits<int>::min();
    }
    file_stream.close();

    std::istringstream iss(line);
    std::string token;

    for (unsigned short i = 0; i < 17; ++i) 
    {
        if (!(iss >> token)) 
        {
            std::cerr << "Error parsing from " << file_path << '\n';
            return std::numeric_limits<int>::min();
        }
    }

    int priority;
    if (!(iss >> priority)) 
    {
        std::cerr << "Error reading priority from " << file_path << '\n';
        return std::numeric_limits<int>::min();
    }

    int nice;
    if (!(iss >> nice)) 
    {
        std::cerr << "Error reading nice from " << file_path << '\n';
        return std::numeric_limits<int>::min();
    }

    int pri;
    if (priority < 100) 
        pri = priority;
    else 
        pri = -20 + nice;
    return pri;
}

double up_time() 
{
    double time;
    const std::string path = proc + uptime;
    std::ifstream file_stream(path);
    if (!file_stream.is_open()) 
    {
      std::cerr << "Open file error: " << path << '\n';
      return std::numeric_limits<double>::min();
    }
    std::string line;
    std::getline(file_stream, line);
    std::istringstream iss(line);
    iss >> time;
    file_stream.close();
    return time;
}

double cpu_proc_utilization(unsigned pid) 
{
    std::vector<std::string> utilization;
    const std::string path = proc + std::to_string(pid) + stat;
    std::ifstream file_stream(path);
    if (!file_stream.is_open()) 
    {
        std::cerr << "Open file error: " << path << '\n';
        return std::numeric_limits<double>::min();
    }
    std::string line, value;
    std::getline(file_stream, line);
    std::istringstream iss(line);

    int count = 0;
    while (count < 22) 
    {
        iss >> value;
        utilization.emplace_back(std::move(value));
        ++count;
    }

    double utime = stod(utilization[13]);
    double stime = stod(utilization[14]);
    double cutime = stod(utilization[15]);
    double cstime = stod(utilization[16]);
    double starttime = stod(utilization[21]);

    double Hertz = sysconf(_SC_CLK_TCK);
    double uptime = up_time();

    double total_time = utime + stime + cutime + cstime;
    double seconds = uptime - (starttime / Hertz);
    double cpu_usage = ((total_time / Hertz) / seconds);

    return cpu_usage;
}

std::string get_os()
{
    std::string line, key, value;
    std::ifstream file_stream(os_release);
    if (!file_stream.is_open()) 
    {
        std::cerr << "Open file error: " << os_release << '\n';
        return "";
    }
    while (std::getline(file_stream, line)) 
    {
        std::replace(line.begin(), line.end(), ' ', '_');
        std::replace(line.begin(), line.end(), '=', ' ');
        std::replace(line.begin(), line.end(), '"', ' ');
        std::istringstream iss(line);
        while (iss >> key >> value) 
        {
            if (key == "PRETTY_NAME") 
            {
                std::replace(value.begin(), value.end(), '_', ' ');
                file_stream.close();
                return value;
            }
        }
    }
    file_stream.close();
    return "";
}

std::string get_kernel() 
{
    std::string line;
    std::ifstream file_stream(proc + version);
    if (!file_stream.is_open()) 
    {
        std::cerr << "Open file error: " << proc + version << '\n';
        return "";
    }
    std::getline(file_stream, line);
    std::string os, ver, kernel;
    std::istringstream iss(line);
    iss >> os >> ver >> kernel;
    file_stream.close();
    return kernel;
}

used_memory::memory_info get_memory() 
{
    std::ifstream file_stream(proc + meminfo);
    if (!file_stream.is_open()) 
    {
        std::cerr << "Open file error: " << proc + version << '\n';
        return {0, 0, 0};
    }
    double mem_total, mem_free, value;
    std::string line, key;
    while (std::getline(file_stream, line)) 
    {
        std::istringstream iss(line);
        while (iss >> key >> value) 
        {
            if (key == "MemTotal:") 
                mem_total = value;
            else if (key == "MemFree:") 
                mem_free = value;
        }
    }
    file_stream.close();
    double used = mem_total - mem_free;
    double percent = (used / mem_total) * 100;
    return { used, mem_total, percent };
}

cpu::cpu_usage get_cpu()
{
    std::ifstream file_stream(proc + stat);
    if (!file_stream.is_open()) 
        throw std::runtime_error("Failed to open /proc/stat");
    std::string line;
    while (std::getline(file_stream, line)) 
    {
        if (line.compare(0, 3, "cpu") == 0) 
        { 
            std::istringstream iss(line);
            std::string cpu;
            iss >> cpu; 

            cpu::cpu_usage usage;
            iss>> usage.user_ >> usage.nice_ >> usage.system_ >> usage.idle_ >>
                usage.iowait_ >> usage.irq_ >> usage.softirq_ >> usage.steal_ >>
                usage.guest_ >> usage.guest_nice_;

            file_stream.close();
            return usage;
        }
    }
    file_stream.close();
    throw std::runtime_error("CPU utilization data not found in /proc/stat");
}
