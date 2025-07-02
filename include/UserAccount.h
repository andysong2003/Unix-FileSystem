#ifndef USER_ACCOUNT_H
#define USER_ACCOUNT_H

#include <string>
#include <vector>

struct UserAccount {
    std::string username;
    std::string password;
    short uid;
    short gid;
};

class UserManager {
private:
    std::vector<UserAccount> users;
    UserAccount current_user;
    bool logged_in = false;

public:
    UserManager();
    bool login(const std::string &username, const std::string &password);
    void logout();

    bool isLoggedIn() const;
    short getUid() const;
    short getGid() const;
    std::string getUsername() const;
};

#endif
