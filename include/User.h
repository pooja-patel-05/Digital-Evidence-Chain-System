#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

class User {
private:
    std::string username;
    std::string password;
    std::string role;

public:
    User();
    User(const std::string& username,
         const std::string& password,
         const std::string& role);

    const std::string& getUsername() const;
    const std::string& getPassword() const;
    const std::string& getRole() const;

    void setUsername(const std::string& username);
    void setPassword(const std::string& password);
    void setRole(const std::string& role);

    static std::vector<User> loadUsers(const std::string& filePath = "data/users.txt");
    static bool authenticate(const std::vector<User>& users,
                             const std::string& username,
                             const std::string& password,
                             User& authenticatedUser);
};

#endif
