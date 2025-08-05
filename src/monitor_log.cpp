#include "draw.hpp"
#include "monitor_log.hpp"

#include <conio.h>
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

void MonitorLog::updateLog(){
    for (const std::string& line : readLog()){
        double amount {extractAmount(line)};
        if (amount > 0){                
            gained_amount = amount;
            total_amount += amount;            
        }
    }
}

void MonitorLog::exitFileNotFound(){
    fmt::print("\033[H\033[0JFile not found.. press any key to exit\n");
    _getch();
    std::exit(EXIT_FAILURE);
}

std::vector<std::string> MonitorLog::readLog(){
    static std::streampos last_pos {};
    static bool is_end {false};

    if (!mainTimer().isTimerRunning()){
        is_end = true;
        return {};
    }

    std::ifstream file {logpath, std::ios::ate};
    if (!file) exitFileNotFound();

    std::streampos pos {file.tellg()};

    if (is_end){
        if (pos != -1) last_pos = pos;
        is_end = false;
    }
    if (pos == last_pos) return {};

    if (last_pos == 0 || pos < last_pos){
        if (pos != -1) last_pos = pos;
        return {};
    }
    file.seekg(last_pos);

    std::vector<std::string> lines {};
    std::string newline {};

    while (std::getline(file, newline)){
        if (newline.find(parse_line) != std::string::npos){
            std::string after {newline.substr(newline.find(parse_line) + parse_line.size())};
            lines.push_back(after);                
        }
        if (file.tellg() != -1) last_pos = file.tellg();            
    }
    return lines;
}

std::string MonitorLog::addComma(double d) {
    std::ostringstream oss {};
    oss << std::fixed << std::setprecision(2) << d;
    std::string s {oss.str()};

    for (std::size_t pos {s.find('.')}; pos > 3; pos -= 3){ 
        if (pos == 4 && s[0] == '-') break;
        s.insert(pos-3, ",");
    }
    s.insert(s.begin(), '$');
    return s;
}

double MonitorLog::extractAmount(const std::string& s) const{  
    return std::stod(s);
}

double MonitorLog::ratePerHr() const{
    int64_t elapsed_sec {mainTimer().getTimeMs() / 1000};
    if (elapsed_sec == 0) return {};
    return (total_amount / static_cast<double>(elapsed_sec)) * 3600;
}

double MonitorLog::ratePerMin() const{
    int64_t elapsed_sec {mainTimer().getTimeMs() / 1000};
    if (elapsed_sec == 0) return {};
    return (total_amount / static_cast<double>(elapsed_sec)) * 60;
}

double MonitorLog::getGainedAmount() const{ return gained_amount; }

double MonitorLog::getTotalAmount() const{ return total_amount; }

void MonitorLog::setFilePath(const std::filesystem::path& p){
    if (std::filesystem::is_regular_file(p)){
        logpath = p;
    }
    else exitFileNotFound();
}