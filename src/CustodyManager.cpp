#include "CustodyManager.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

CustodyManager::CustodyManager(const std::string& dataFile)
    : dataFile(dataFile) {
    loadTransfers();
}

bool CustodyManager::transferEvidence(const CustodyRecord& record) {
    if (record.getEvidenceId().empty() ||
        record.getFromPerson().empty() ||
        record.getToPerson().empty() ||
        record.getTransferDate().empty()) {
        return false;
    }

    transfers.push_back(record);
    if (!saveTransfer()) {
        transfers.pop_back();
        return false;
    }
    return true;
}

void CustodyManager::viewHistory(const std::string& evidenceId) const {
    bool found = false;

    std::cout << std::left
              << std::setw(12) << "Evidence ID"
              << std::setw(20) << "From"
              << std::setw(20) << "To"
              << "Transfer Date\n";
    std::cout << std::string(68, '-') << '\n';

    for (const CustodyRecord& record : transfers) {
        if (record.getEvidenceId() == evidenceId) {
            record.display();
            found = true;
        }
    }

    if (!found) {
        std::cout << "No custody history found for evidence " << evidenceId << ".\n";
    }
}

bool CustodyManager::loadTransfers() {
    std::ifstream input(dataFile);
    if (!input) {
        return false;
    }

    transfers.clear();
    std::string line;
    while (std::getline(input, line)) {
        if (line.empty()) {
            continue;
        }

        std::stringstream stream(line);
        std::string evidenceId;
        std::string fromPerson;
        std::string toPerson;
        std::string transferDate;

        if (std::getline(stream, evidenceId, ',') &&
            std::getline(stream, fromPerson, ',') &&
            std::getline(stream, toPerson, ',') &&
            std::getline(stream, transferDate)) {
            transfers.emplace_back(evidenceId, fromPerson, toPerson, transferDate);
        }
    }
    return true;
}

bool CustodyManager::saveTransfer() const {
    std::ofstream output(dataFile, std::ios::trunc);
    if (!output) {
        return false;
    }

    for (const CustodyRecord& record : transfers) {
        output << record.getEvidenceId() << ','
               << record.getFromPerson() << ','
               << record.getToPerson() << ','
               << record.getTransferDate() << '\n';
    }
    return output.good();
}

std::string CustodyManager::getCurrentCustodian(
    const std::string& evidenceId,
    const std::string& originalCustodian) const {
    std::string currentCustodian = originalCustodian;
    for (const CustodyRecord& record : transfers) {
        if (record.getEvidenceId() == evidenceId) {
            currentCustodian = record.getToPerson();
        }
    }
    return currentCustodian;
}
