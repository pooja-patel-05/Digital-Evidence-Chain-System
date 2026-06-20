#ifndef HASH_MANAGER_H
#define HASH_MANAGER_H

#include <string>

class HashManager {
public:
    std::string prepareEvidenceFile(const std::string& fileName) const;
    std::string generateHash(const std::string& fileName) const;
    bool verifyHash(const std::string& fileName,
                    const std::string& storedHash) const;
};

#endif
