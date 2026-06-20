#include "HashManager.h"

#include <cerrno>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iterator>
#include <sstream>
#include <stdexcept>

#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#endif

namespace {
const char* EVIDENCE_DIRECTORY = "evidence_files";

void ensureEvidenceDirectory() {
#ifdef _WIN32
    const int result = _mkdir(EVIDENCE_DIRECTORY);
#else
    const int result = mkdir(EVIDENCE_DIRECTORY, 0755);
#endif
    if (result != 0 && errno != EEXIST) {
        throw std::runtime_error("Unable to create evidence_files folder.");
    }
}

std::string baseName(const std::string& path) {
    const std::string::size_type position = path.find_last_of("/\\");
    return position == std::string::npos ? path : path.substr(position + 1);
}
}

std::string HashManager::prepareEvidenceFile(const std::string& fileName) const {
    if (fileName.empty()) {
        throw std::runtime_error("Evidence file name cannot be empty.");
    }

    ensureEvidenceDirectory();
    const std::string name = baseName(fileName);
    if (name.empty()) {
        throw std::runtime_error("Invalid evidence file name.");
    }

    const std::string storedPath =
        std::string(EVIDENCE_DIRECTORY) + "/" + name;
    std::ifstream existingStoredFile(storedPath, std::ios::binary);
    if (existingStoredFile) {
        return storedPath;
    }

    std::ifstream source(fileName, std::ios::binary);
    if (source) {
        std::ofstream destination(storedPath, std::ios::binary);
        if (!destination) {
            throw std::runtime_error("Unable to store evidence file: " + storedPath);
        }
        destination << source.rdbuf();
        if (!destination.good()) {
            throw std::runtime_error("Unable to copy evidence file: " + fileName);
        }
    } else {
        std::ofstream newFile(storedPath, std::ios::binary);
        if (!newFile) {
            throw std::runtime_error("Unable to create evidence file: " + storedPath);
        }
    }

    return storedPath;
}

std::string HashManager::generateHash(const std::string& fileName) const {
    std::ifstream input(fileName, std::ios::binary);
    if (!input) {
        throw std::runtime_error("Unable to open file: " + fileName);
    }

    const std::string contents(
        (std::istreambuf_iterator<char>(input)),
        std::istreambuf_iterator<char>());
    const std::size_t value = std::hash<std::string>{}(contents);

    std::ostringstream hash;
    hash << std::uppercase << std::hex << value;
    return hash.str();
}

bool HashManager::verifyHash(const std::string& fileName,
                             const std::string& storedHash) const {
    return generateHash(fileName) == storedHash;
}
