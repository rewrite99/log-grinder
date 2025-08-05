#pragma once

#include <filesystem>
#include <fmt/core.h>
#include <string>
#include <vector>

class MonitorLog{
public:
    MonitorLog() = default;
    void updateLog();
    void exitFileNotFound();
    std::vector<std::string> readLog();
    std::string addComma(double d);
    double extractAmount(const std::string& s) const;
    double ratePerHr() const;
    double ratePerMin() const;
    double getGainedAmount() const;
    double getTotalAmount() const;
    void setFilePath(const std::filesystem::path& p);

private:
    std::string parse_line {"[CHAT] You got: $"};
    std::filesystem::path logpath {};
    double total_amount {};
    double gained_amount {};
};