#include "../include/User.h"
//#include "User.h"
User::User()
{
    u_uid = 0;
    u_gid = 0;
    u_ruid = 0;
    u_rgid = 0;

    u_cdir = nullptr;
    u_pdir = nullptr;
    // 其他初始化
}
