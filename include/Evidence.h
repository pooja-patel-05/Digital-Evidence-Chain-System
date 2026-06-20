#ifndef EVIDENCE_H
#define EVIDENCE_H

#include <string>

class Evidence {
private:
    std::string evidenceId;
    std::string fileName;
    std::string uploadedBy;
    std::string uploadDate;
    std::string hashValue;

public:
    Evidence();
    Evidence(const std::string& evidenceId,
             const std::string& fileName,
             const std::string& uploadedBy,
             const std::string& uploadDate,
             const std::string& hashValue);

    const std::string& getEvidenceId() const;
    const std::string& getFileName() const;
    const std::string& getUploadedBy() const;
    const std::string& getUploadDate() const;
    const std::string& getHashValue() const;

    void setEvidenceId(const std::string& evidenceId);
    void setFileName(const std::string& fileName);
    void setUploadedBy(const std::string& uploadedBy);
    void setUploadDate(const std::string& uploadDate);
    void setHashValue(const std::string& hashValue);

    void display() const;
};

#endif
