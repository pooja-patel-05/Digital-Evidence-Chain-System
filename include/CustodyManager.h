#ifndef CUSTODY_MANAGER_H
#define CUSTODY_MANAGER_H

#include "CustodyRecord.h"

#include <string>
#include <vector>

class CustodyManager {
private:
    std::vector<CustodyRecord> transfers;
    std::string dataFile;

public:
    explicit CustodyManager(const std::string& dataFile = "data/custody.txt");

    bool transferEvidence(const CustodyRecord& record);
    void viewHistory(const std::string& evidenceId) const;
    bool loadTransfers();
    bool saveTransfer() const;
    std::string getCurrentCustodian(const std::string& evidenceId,
                                    const std::string& originalCustodian) const;
};

#endif
