#include "moneylog.hpp"
#include "timer.hpp"

#include <conio.h>
#include <cstddef>
#include <filesystem>
#include <fmt/core.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

MoneyLog& MoneyLog::Get(){
    static MoneyLog mlog {};
    return mlog;
}

void MoneyLog::updateLog(){
    for (const std::string& line : readLog()){
        double amount {extractAmount(line)};
        if (amount > 0){ 
            gained_amount = amount;
            total_amount += amount;
            update = true;
        }
    }
}

void MoneyLog::resetLog(){
    gained_amount = total_amount = 0.0;
}

void MoneyLog::exitFileNotFound() const{
    fmt::print("\033[H\033[0JFile not found.. press any key to exit\n");
    _getch();
    std::exit(EXIT_FAILURE);
}

std::vector<std::string> MoneyLog::readLog(){
    static std::streampos last_pos {};
    static bool is_end {false};

    if (!Timer::MainTimer().isTimerRunning()){
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
    std::string line {};

    while (std::getline(file, line)){
        if (line.find(search_str) != std::string::npos){
            std::string amount_str {line.substr(line.find(search_str) + search_str.size())};
            lines.push_back(amount_str);                
        }
        if (file.tellg() != -1) last_pos = file.tellg();            
    }
    return lines;
}

std::string MoneyLog::addComma(double d) {
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

double MoneyLog::extractAmount(const std::string& s) const{  
    return std::stod(s);
}

double MoneyLog::ratePerHr() const{
    int64_t elapsed_sec {Timer::MainTimer().timeMs() / 1000};
    if (elapsed_sec == 0) return {};
    return (total_amount / static_cast<double>(elapsed_sec)) * 3600;
}

double MoneyLog::ratePerMin() const{
    int64_t elapsed_sec {Timer::MainTimer().timeMs() / 1000};
    if (elapsed_sec == 0) return {};
    return (total_amount / static_cast<double>(elapsed_sec)) * 60;
}

double MoneyLog::gainedAmount() const{ return gained_amount; }

double MoneyLog::totalAmount() const{ return total_amount; }

bool MoneyLog::refresh(){
    if (update){
        update = false;
        return true;
    }
    return false;
}

void MoneyLog::setFilePath(const std::filesystem::path& p){
    if (std::filesystem::is_regular_file(p)){
        logpath = p;
    }
    else exitFileNotFound();
}