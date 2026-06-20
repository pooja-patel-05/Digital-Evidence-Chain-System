#include "AuditManager.h"
#include "CustodyManager.h"
#include "CustodyRecord.h"
#include "Evidence.h"
#include "EvidenceManager.h"
#include "HashManager.h"
#include "User.h"

#include <exception>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

namespace {
std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string value;
    std::getline(std::cin, value);
    return value;
}

int readChoice() {
    int choice = 0;
    std::cout << "Enter choice: ";
    if (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return -1;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return choice;
}

void showMainMenu() {
    std::cout << "\n========== Digital Evidence Chain System ==========\n";
    std::cout << "1. Login\n"
              << "2. Exit\n";
}

void showSystemMenu(const User& currentUser) {
    std::cout << "\n========== Evidence Management Menu ==========\n"
              << "Logged in: " << currentUser.getUsername()
              << " (" << currentUser.getRole() << ")\n"
              << "1. Add Evidence\n"
              << "2. View Evidence\n"
              << "3. Search Evidence\n"
              << "4. Transfer Evidence\n"
              << "5. View Evidence History\n"
              << "6. Verify Integrity\n"
              << "7. View Audit Logs\n"
              << "8. Logout\n";
}

bool canAddEvidence(const User& user) {
    return user.getRole() == "Admin" || user.getRole() == "Officer";
}

bool canTransferEvidence(const User& user) {
    return user.getRole() == "Admin" ||
           user.getRole() == "Officer" ||
           user.getRole() == "LabStaff";
}
}

int main() {
    EvidenceManager evidenceManager;
    CustodyManager custodyManager;
    HashManager hashManager;
    AuditManager auditManager;
    const std::vector<User> users = User::loadUsers();

    User currentUser;
    while (true) {
        showMainMenu();
        const int mainChoice = readChoice();

        try {
            if (mainChoice == 1) {
                const std::string username = readLine("Username: ");
                const std::string password = readLine("Password: ");

                if (User::authenticate(users, username, password, currentUser)) {
                    std::cout << "Login successful. Welcome, "
                              << currentUser.getUsername() << ".\n";
                    auditManager.logAction("User Login: " + currentUser.getUsername());
                } else {
                    std::cout << "Invalid username or password.\n";
                    auditManager.logAction("Failed Login Attempt: " + username);
                    continue;
                }

                bool sessionActive = true;
                while (sessionActive) {
                    showSystemMenu(currentUser);
                    const int choice = readChoice();

                    if (choice == 1) {
                        if (!canAddEvidence(currentUser)) {
                            std::cout << "Your role cannot add evidence.\n";
                            continue;
                        }

                        const std::string evidenceId = readLine("Evidence ID: ");
                        const std::string enteredFileName =
                            readLine("Evidence file name or path: ");
                        const std::string uploadDate = readLine("Upload date (DD-MM-YYYY): ");
                        const std::string fileName =
                            hashManager.prepareEvidenceFile(enteredFileName);
                        const std::string hashValue =
                            hashManager.generateHash(fileName);

                        const Evidence evidence(
                            evidenceId,
                            fileName,
                            currentUser.getUsername(),
                            uploadDate,
                            hashValue);

                        if (evidenceManager.addEvidence(evidence)) {
                            std::cout << "Evidence added successfully.\n"
                                      << "Stored at: " << fileName << '\n'
                                      << "Generated hash: " << hashValue << '\n';
                            auditManager.logAction("Evidence Added: " + evidenceId);
                        } else {
                            std::cout << "Could not add evidence. Check for an empty or duplicate ID.\n";
                        }
                    } else if (choice == 2) {
                        evidenceManager.viewAllEvidence();
                        auditManager.logAction("All Evidence Viewed By: " +
                                               currentUser.getUsername());
                    } else if (choice == 3) {
                        const std::string evidenceId = readLine("Evidence ID: ");
                        const Evidence* evidence = evidenceManager.searchEvidence(evidenceId);
                        if (evidence == nullptr) {
                            std::cout << "Evidence not found.\n";
                        } else {
                            evidence->display();
                        }
                        auditManager.logAction("Evidence Searched: " + evidenceId);
                    } else if (choice == 4) {
                        if (!canTransferEvidence(currentUser)) {
                            std::cout << "Your role cannot transfer evidence.\n";
                            continue;
                        }

                        const std::string evidenceId = readLine("Evidence ID: ");
                        const Evidence* evidence = evidenceManager.searchEvidence(evidenceId);
                        if (evidence == nullptr) {
                            std::cout << "Evidence not found.\n";
                            continue;
                        }

                        const std::string currentCustodian =
                            custodyManager.getCurrentCustodian(
                                evidenceId,
                                evidence->getUploadedBy());
                        std::cout << "Current custodian: " << currentCustodian << '\n';

                        const std::string toPerson = readLine("Transfer to: ");
                        const std::string transferDate =
                            readLine("Transfer date (DD-MM-YYYY): ");
                        const CustodyRecord record(
                            evidenceId,
                            currentCustodian,
                            toPerson,
                            transferDate);

                        if (custodyManager.transferEvidence(record)) {
                            std::cout << "Evidence transferred successfully.\n";
                            auditManager.logAction("Evidence Transferred: " + evidenceId);
                        } else {
                            std::cout << "Could not save the custody transfer.\n";
                        }
                    } else if (choice == 5) {
                        const std::string evidenceId = readLine("Evidence ID: ");
                        custodyManager.viewHistory(evidenceId);
                        auditManager.logAction("Evidence History Viewed: " + evidenceId);
                    } else if (choice == 6) {
                        const std::string evidenceId = readLine("Evidence ID: ");
                        const Evidence* evidence = evidenceManager.searchEvidence(evidenceId);
                        if (evidence == nullptr) {
                            std::cout << "Evidence not found.\n";
                            continue;
                        }

                        if (hashManager.verifyHash(
                                evidence->getFileName(),
                                evidence->getHashValue())) {
                            std::cout << "Integrity verified: file is unchanged.\n";
                            auditManager.logAction("Integrity Verified: " + evidenceId);
                        } else {
                            std::cout << "Integrity warning: file has been modified.\n";
                            auditManager.logAction("Integrity Check Failed: " + evidenceId);
                        }
                    } else if (choice == 7) {
                        if (currentUser.getRole() != "Admin") {
                            std::cout << "Only an Admin can view audit logs.\n";
                            continue;
                        }
                        auditManager.viewLogs();
                    } else if (choice == 8) {
                        auditManager.logAction("User Logout: " +
                                               currentUser.getUsername());
                        std::cout << "Logged out successfully.\n";
                        sessionActive = false;
                    } else {
                        std::cout << "Invalid choice. Select a number from 1 to 8.\n";
                    }
                }
            } else if (mainChoice == 2) {
                std::cout << "Exiting system.\n";
                break;
            } else {
                std::cout << "Invalid choice. Select 1 or 2.\n";
            }
        } catch (const std::exception& error) {
            std::cout << "Error: " << error.what() << '\n';
        }
    }

    return 0;
}
