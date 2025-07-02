// #include "../include/VirtualProcess.h"
// #include "../include/Path.h"
// VirtualProcess VirtualProcess::instance;

// VirtualProcess::VirtualProcess()
// {
//     //TODO 需要初始化VirtualProcess
//     //strcpy(defaultUser.u_curdir, "/");
//     //defaultUser.u_curDir = Path("/");
//     defaultUser.curDirInodeId = 1;
// }

// VirtualProcess::~VirtualProcess()
// {
//     //TODO 需要初始化VirtualProcess
// }

// VirtualProcess *VirtualProcess::Instance()
// {
//     return &VirtualProcess::instance;
// }

// User &VirtualProcess::getUser()
// {
//     return defaultUser;
// }

// /* 获取用户ID，低16比特为真实用户ID(u_ruid)，高16比特为有效用户ID(u_uid) */
// short VirtualProcess::Getuid()
// {
//     return defaultUser.u_uid;
// }

// /* 获取组ID, 低16比特为真实组ID(u_rgid)，高16比特为有效组ID(u_gid) */
// short VirtualProcess::Getgid()
// {
//     return defaultUser.u_gid;
// }
#include "../include/VirtualProcess.h"
#include "../include/Path.h"
#include <iostream>

VirtualProcess VirtualProcess::instance;

VirtualProcess::VirtualProcess() {
    defaultUser.curDirInodeId = 1;
    // 默认使用uid/gid为1（未登录状态）
}

VirtualProcess::~VirtualProcess() {}

VirtualProcess *VirtualProcess::Instance() {
    return &instance;
}

User &VirtualProcess::getUser() {
    return defaultUser;
}

short VirtualProcess::Getuid() {
    return defaultUser.u_uid;
}

short VirtualProcess::Getgid() {
    return defaultUser.u_gid;
}

bool VirtualProcess::Login(const std::string &username, const std::string &password) {
    if (userManager.login(username, password)) {
        // 登录成功后，更新 defaultUser 的 UID、GID、RUID、RGID
        defaultUser.u_uid = userManager.getUid();
        defaultUser.u_gid = userManager.getGid();
        defaultUser.u_ruid = userManager.getUid();
        defaultUser.u_rgid = userManager.getGid();

        return true;
    }
    return false;
}


void VirtualProcess::Logout() {
    userManager.logout();
    *((short *)&defaultUser.u_uid) = 1;
    *((short *)&defaultUser.u_gid) = 1;
}

bool VirtualProcess::IsLoggedIn() {
    return userManager.isLoggedIn();
}

std::string VirtualProcess::GetCurrentUsername() {
    if (userManager.isLoggedIn()) {
        return userManager.getUsername();
    }
    return "anonymous";
}
UserManager& VirtualProcess::getUserManager() {
    return userManager;
}