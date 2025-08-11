#pragma once

#include <filesystem>
#include <string>
#include <vector>

class MoneyLog{
public:
    static MoneyLog& Get();

    void updateLog();
    void resetLog();
    void exitFileNotFound() const;
    std::vector<std::string> readLog();
    std::string addComma(double d);
    double extractAmount(const std::string& s) const;
    double ratePerHr() const;
    double ratePerMin() const;
    double gainedAmount() const;
    double totalAmount() const;
    bool refresh();
    void setFilePath(const std::filesystem::path& p);

private:
    std::string search_str {"[CHAT] You got: $"};
    std::filesystem::path logpath {};
    double total_amount {};
    double gained_amount {};
    bool update {false};

    MoneyLog() = default;
    ~MoneyLog() = default;
};