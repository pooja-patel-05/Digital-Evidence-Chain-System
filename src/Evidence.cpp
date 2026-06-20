#include "Evidence.h"

#include <iomanip>
#include <iostream>

Evidence::Evidence() = default;

Evidence::Evidence(const std::string& evidenceId,
                   const std::string& fileName,
                   const std::string& uploadedBy,
                   const std::string& uploadDate,
                   const std::string& hashValue)
    : evidenceId(evidenceId),
      fileName(fileName),
      uploadedBy(uploadedBy),
      uploadDate(uploadDate),
      hashValue(hashValue) {}

const std::string& Evidence::getEvidenceId() const { return evidenceId; }
const std::string& Evidence::getFileName() const { return fileName; }
const std::string& Evidence::getUploadedBy() const { return uploadedBy; }
const std::string& Evidence::getUploadDate() const { return uploadDate; }
const std::string& Evidence::getHashValue() const { return hashValue; }

void Evidence::setEvidenceId(const std::string& value) { evidenceId = value; }
void Evidence::setFileName(const std::string& value) { fileName = value; }
void Evidence::setUploadedBy(const std::string& value) { uploadedBy = value; }
void Evidence::setUploadDate(const std::string& value) { uploadDate = value; }
void Evidence::setHashValue(const std::string& value) { hashValue = value; }

void Evidence::display() const {
    std::cout << std::left
              << std::setw(12) << evidenceId
              << std::setw(28) << fileName
              << std::setw(18) << uploadedBy
              << std::setw(16) << uploadDate
              << hashValue << '\n';
}
