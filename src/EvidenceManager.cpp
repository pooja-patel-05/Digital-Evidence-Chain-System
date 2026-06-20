#include "EvidenceManager.h"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

EvidenceManager::EvidenceManager(const std::string& dataFile)
    : dataFile(dataFile) {
    loadEvidence();
}

bool EvidenceManager::addEvidence(const Evidence& evidence) {
    if (evidence.getEvidenceId().empty() ||
        evidence.getFileName().empty() ||
        searchEvidence(evidence.getEvidenceId()) != nullptr) {
        return false;
    }

    evidenceList.push_back(evidence);
    if (!saveEvidence()) {
        evidenceList.pop_back();
        return false;
    }
    return true;
}

void EvidenceManager::viewAllEvidence() const {
    if (evidenceList.empty()) {
        std::cout << "No evidence records found.\n";
        return;
    }

    std::cout << std::left
              << std::setw(12) << "ID"
              << std::setw(28) << "File Name"
              << std::setw(18) << "Uploaded By"
              << std::setw(16) << "Upload Date"
              << "Hash Value\n";
    std::cout << std::string(100, '-') << '\n';

    for (const Evidence& evidence : evidenceList) {
        evidence.display();
    }
}

const Evidence* EvidenceManager::searchEvidence(const std::string& evidenceId) const {
    const auto found = std::find_if(
        evidenceList.begin(),
        evidenceList.end(),
        [&](const Evidence& evidence) {
            return evidence.getEvidenceId() == evidenceId;
        });

    return found == evidenceList.end() ? nullptr : &(*found);
}

bool EvidenceManager::deleteEvidence(const std::string& evidenceId) {
    const std::vector<Evidence> backup = evidenceList;
    const auto found = std::remove_if(
        evidenceList.begin(),
        evidenceList.end(),
        [&](const Evidence& evidence) {
            return evidence.getEvidenceId() == evidenceId;
        });

    if (found == evidenceList.end()) {
        return false;
    }

    evidenceList.erase(found, evidenceList.end());
    if (!saveEvidence()) {
        evidenceList = backup;
        return false;
    }
    return true;
}

bool EvidenceManager::loadEvidence() {
    std::ifstream input(dataFile);
    if (!input) {
        return false;
    }

    evidenceList.clear();
    std::string line;
    while (std::getline(input, line)) {
        if (line.empty()) {
            continue;
        }

        std::stringstream stream(line);
        std::string id;
        std::string fileName;
        std::string uploadedBy;
        std::string uploadDate;
        std::string hashValue;

        if (std::getline(stream, id, ',') &&
            std::getline(stream, fileName, ',') &&
            std::getline(stream, uploadedBy, ',') &&
            std::getline(stream, uploadDate, ',') &&
            std::getline(stream, hashValue)) {
            evidenceList.emplace_back(id, fileName, uploadedBy, uploadDate, hashValue);
        }
    }
    return true;
}

bool EvidenceManager::saveEvidence() const {
    std::ofstream output(dataFile, std::ios::trunc);
    if (!output) {
        return false;
    }

    for (const Evidence& evidence : evidenceList) {
        output << evidence.getEvidenceId() << ','
               << evidence.getFileName() << ','
               << evidence.getUploadedBy() << ','
               << evidence.getUploadDate() << ','
               << evidence.getHashValue() << '\n';
    }
    return output.good();
}

const std::vector<Evidence>& EvidenceManager::getAllEvidence() const {
    return evidenceList;
}
