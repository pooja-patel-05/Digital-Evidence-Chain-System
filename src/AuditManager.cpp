#include "AuditManager.h"

#include <chrono>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace {
std::string currentDate() {
    const std::time_t currentTime =
        std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    const std::tm* localTime = std::localtime(&currentTime);
    if (localTime == nullptr) {
        return "Unknown Date";
    }

    std::ostringstream date;
    date << std::put_time(localTime, "%d-%m-%Y");
    return date.str();
}
}

AuditManager::AuditManager(const std::string& logFile)
    : logFile(logFile) {}

bool AuditManager::logAction(const std::string& action) const {
    std::ofstream output(logFile, std::ios::app);
    if (!output) {
        return false;
    }

    output << '[' << currentDate() << "]\n"
           << action << "\n\n";
    return output.good();
}

void AuditManager::viewLogs() const {
    std::ifstream input(logFile);
    if (!input) {
        std::cout << "No audit log is available.\n";
        return;
    }

    std::string line;
    bool hasContent = false;
    while (std::getline(input, line)) {
        std::cout << line << '\n';
        hasContent = true;
    }

    if (!hasContent) {
        std::cout << "Audit log is empty.\n";
    }
}
