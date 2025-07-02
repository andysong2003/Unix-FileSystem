#include "../include/UserAccount.h"
#include <iostream>

UserManager::UserManager() {
    users = {
        {"root", "root123", 0, 0},
        {"user", "123456", 1, 1},
        {"guest", "guest", 2, 2}
    };
}

bool UserManager::login(const std::string &username, const std::string &password) {
    for (const auto &u : users) {
        if (u.username == username && u.password == password) {
            current_user = u;
            logged_in = true;
            std::cout << "Login success. Welcome, " << u.username << "!" << std::endl;
            return true;
        }
    }
    std::cout << "Login failed. Invalid username or password.\n";
    return false;
}

void UserManager::logout() {
    logged_in = false;
    std::cout << "Logout success.\n";
}

bool UserManager::isLoggedIn() const {
    return logged_in;
}

short UserManager::getUid() const {
    return current_user.uid;
}

short UserManager::getGid() const {
    return current_user.gid;
}

std::string UserManager::getUsername() const {
    return current_user.username;
}
