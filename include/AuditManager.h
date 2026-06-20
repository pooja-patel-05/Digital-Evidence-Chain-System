#ifndef AUDIT_MANAGER_H
#define AUDIT_MANAGER_H

#include <string>

class AuditManager {
private:
    std::string logFile;

public:
    explicit AuditManager(const std::string& logFile = "data/audit.log");
    bool logAction(const std::string& action) const;
    void viewLogs() const;
};

#endif
