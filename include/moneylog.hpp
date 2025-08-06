#pragma once

#include <filesystem>
#include <string>
#include <vector>

class MoneyLog{
public:
    static MoneyLog& Get();

    void updateLog();
    void exitFileNotFound() const;
    std::vector<std::string> readLog();
    std::string addComma(double d);
    double extractAmount(const std::string& s) const;
    double ratePerHr() const;
    double ratePerMin() const;
    double gainedAmount() const;
    double totalAmount() const;
    void setFilePath(const std::filesystem::path& p);

private:
    std::string search_str {"[CHAT] You got: $"};
    std::filesystem::path logpath {};
    double total_amount {};
    double gained_amount {};

    MoneyLog() = default;
    ~MoneyLog() = default;
};