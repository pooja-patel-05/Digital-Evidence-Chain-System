#ifndef CUSTODY_RECORD_H
#define CUSTODY_RECORD_H

#include <string>

class CustodyRecord {
private:
    std::string evidenceId;
    std::string fromPerson;
    std::string toPerson;
    std::string transferDate;

public:
    CustodyRecord();
    CustodyRecord(const std::string& evidenceId,
                  const std::string& fromPerson,
                  const std::string& toPerson,
                  const std::string& transferDate);

    const std::string& getEvidenceId() const;
    const std::string& getFromPerson() const;
    const std::string& getToPerson() const;
    const std::string& getTransferDate() const;

    void display() const;
};

#endif
