#ifndef EVIDENCE_MANAGER_H
#define EVIDENCE_MANAGER_H

#include "Evidence.h"

#include <string>
#include <vector>

class EvidenceManager {
private:
    std::vector<Evidence> evidenceList;
    std::string dataFile;

public:
    explicit EvidenceManager(const std::string& dataFile = "data/evidence.txt");

    bool addEvidence(const Evidence& evidence);
    void viewAllEvidence() const;
    const Evidence* searchEvidence(const std::string& evidenceId) const;
    bool deleteEvidence(const std::string& evidenceId);
    bool loadEvidence();
    bool saveEvidence() const;
    const std::vector<Evidence>& getAllEvidence() const;
};

#endif
