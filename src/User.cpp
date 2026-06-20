#include "User.h"

#include <fstream>
#include <sstream>

User::User() = default;

User::User(const std::string& username,
           const std::string& password,
           const std::string& role)
    : username(username), password(password), role(role) {}

const std::string& User::getUsername() const { return username; }
const std::string& User::getPassword() const { return password; }
const std::string& User::getRole() const { return role; }

void User::setUsername(const std::string& value) { username = value; }
void User::setPassword(const std::string& value) { password = value; }
void User::setRole(const std::string& value) { role = value; }

std::vector<User> User::loadUsers(const std::string& filePath) {
    std::vector<User> users;
    std::ifstream input(filePath);
    std::string line;

    while (std::getline(input, line)) {
        if (line.empty()) {
            continue;
        }

        std::stringstream stream(line);
        std::string name;
        std::string pass;
        std::string userRole;

        if (std::getline(stream, name, ',') &&
            std::getline(stream, pass, ',') &&
            std::getline(stream, userRole)) {
            users.emplace_back(name, pass, userRole);
        }
    }
    return users;
}

bool User::authenticate(const std::vector<User>& users,
                        const std::string& name,
                        const std::string& pass,
                        User& authenticatedUser) {
    for (const User& user : users) {
        if (user.username == name && user.password == pass) {
            authenticatedUser = user;
            return true;
        }
    }
    return false;
}
