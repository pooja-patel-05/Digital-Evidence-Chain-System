#include "CustodyRecord.h"

#include <iomanip>
#include <iostream>

CustodyRecord::CustodyRecord() = default;

CustodyRecord::CustodyRecord(const std::string& evidenceId,
                             const std::string& fromPerson,
                             const std::string& toPerson,
                             const std::string& transferDate)
    : evidenceId(evidenceId),
      fromPerson(fromPerson),
      toPerson(toPerson),
      transferDate(transferDate) {}

const std::string& CustodyRecord::getEvidenceId() const { return evidenceId; }
const std::string& CustodyRecord::getFromPerson() const { return fromPerson; }
const std::string& CustodyRecord::getToPerson() const { return toPerson; }
const std::string& CustodyRecord::getTransferDate() const { return transferDate; }

void CustodyRecord::display() const {
    std::cout << std::left
              << std::setw(12) << evidenceId
              << std::setw(20) << fromPerson
              << std::setw(20) << toPerson
              << transferDate << '\n';
}
