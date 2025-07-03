// #include "../include/Shell.h"
// #include "../include/VirtualProcess.h"
// #include "../include/Kernel.h"

// FileName fileName;

// void Shell::help()
// {

//     system("cat help");
// };

// int Shell::readUserInput()
// {
//     Logcat::log("建议先输入help指令，查看使用说明");
//     while (true)
//     {
//         putchar('$');
//         putchar(' ');
//         std::cin.getline(tty_buffer, MAX_CMD_LEN, '\n');
//         for (char *checker = strrchr(tty_buffer, '\t'); checker != NULL; checker = strrchr(checker, '\t'))
//         {
//             *checker = ' ';
//         }
//         char *dupl_tty_buffer = strdup(tty_buffer);
//         memset(split_cmd, 0x0, sizeof(split_cmd));
//         int cmd_param_seq = 0;
//         for (char *p = strtok(dupl_tty_buffer, " "); p != nullptr; p = strtok(NULL, " "), cmd_param_seq++)
//         {
//             strcpy(split_cmd[cmd_param_seq], p);
//         }
//         param_num = cmd_param_seq;
// #ifdef IS_DEBUG
//         for (int i = 0; i < param_num; i++)
//         {
//             std::cout << "看一下刚输入的参数：" << split_cmd[i] << ' ';
//         }
//         std::cout << std::endl;
// #endif
//         //TODO

//         //Step4:解析执行指令
//         parseCmd();
//         delete dupl_tty_buffer;
//         fflush(stdin);
//     }
// }

// void Shell::parseCmd()
// {
//     switch (getInstType())
//     {
//     case MOUNT:
//         mount(); //OK
//         break;
//     case UNMOUNT:
//         unmount(); //OK
//         break;
//     case FORMAT:
//         format(); //OK
//         break;
//     case CD:
//         cd(); //OK
//         break;
//     case LS:
//         ls(); //OK
//         break;
//     case RM:
//         rm(); //OK
//         break;
//     case RMDIR:
//         rmdir(); //OK
//         break;
//     case MKDIR:
//         mkdir(); //OK
//         break;
//     case TOUCH:
//         touch(); //OK
//         break;
//     case CLEAR:
//         clear(); //OK
//         break;
//     case HELP:
//         help(); //OK
//         break;
//     case EXIT:
//         mexit(); //OK
//         break;
//     case VERSION:
//         version(); //OK
//         break;
//     case STORE:
//         store(); //OK
//         break;
//     case WITHDRAW:
//         withdraw(); //OKKK
//         break;
//     case VIM:
//         fileName = split_cmd[1];
//         vim(fileName);
//         break;
//     default:
//         Logcat::log("CMD NOT SUPPORTED!\n");
//         break;
//     }
// }

// /**
//  * @comment:实际上是做字符串到枚举类型的转化，为了switch case
//  */
// INSTRUCT Shell::getInstType()
// {
//     char *instStr = getInstStr();
// #ifdef IS_DEBUG
//     Logcat::log(TAG, "命令行命令字为:");
//     Logcat::log(TAG, instStr);

// #endif
//     //为什么从1开始
//     for (int i = 1; i < INST_NUM; i++)
//     {
//         //这里要加感叹号，注意strcmp在相等时返回的是0
//         if (!strcmp(instructStr[i], instStr))
//         {

// #ifdef IS_DEBUG
//             //std::cout<<INSTRUCT(i)<<std::endl;
// #endif
//             return INSTRUCT(i - 1);
//         }
//     }
//     return ERROR_INST;
// }

// /**
//  * @comment:命令缓冲区→命令参数字符数组→第一个参数得到命令字符串
//  * 此函数的功能就是读出第一个字符串，亦即InstStr
//  */
// char *Shell::getInstStr()
// {
//     return split_cmd[0];
// }

// /**
//  * @comment:这个是getInstStr更通用的情况
//  */
// char *Shell::getParam(int i)
// {
//     return split_cmd[i];
// }

// /**
//  * 获得参数的个数
//  */
// int Shell::getParamAmount()
// {
//     for (int i = 0; i < MAX_PARAM_NUM; i++)
//     {
//         if (!strcmp(split_cmd[i], ""))
//         {
//             return i;
//         }
//     }
//     return MAX_PARAM_NUM;
// }

// void Shell::mount()
// {
//     Logcat::devlog(TAG, "MOUNT EXEC");
//     /**
//      * 装载磁盘的最上层命令调用函数：
//      * 硬盘装载的步骤：
//      * ①内存inodeCache初始化
//      * ②DiskDriver打开虚拟磁盘img，mmap，进入就绪状态
//      * ③装载SuperBlock到VFS的SuperBlock缓存
//      * 
//      *  */
//     bounded_VFS->mount();
// }

// void Shell::unmount()
// {
//     bounded_VFS->unmount();
//     Logcat::devlog(TAG, "unmount EXEC");
// }

// /**
//  * 对装载的磁盘镜像做格式化
//  */
// void Shell::format()
// {

//     if (bounded_VFS->isMounted())
//     {
//         bounded_VFS->format();
//         Logcat::devlog(TAG, "format EXEC");
//     }
//     else
//     {
//         Logcat::log(TAG, "ERROR,DISK NOT MOUNTED!");
//     }
// }
// void Shell::mkdir()
// {
//     if (getParamAmount() == 2)
//     {
//         if (bounded_VFS->mkDir(getParam(1)) < 0)
//         {
//             Logcat::log("ERROR!存在同名目录，创建失败！");
//         }
//     }
//     else
//     {
//         Logcat::log("ERROR！MKDIR参数个数错误！");
//     }
//     Logcat::devlog(TAG, "mkdir EXEC");
// }
// void Shell::cat()
// {
//     Logcat::devlog(TAG, "cat EXEC");
//     Logcat::log("cat 暂不支持");
// }
// void Shell::touch()
// {
//     if (getParamAmount() != 2)
//     {
//         Logcat::log("ERROR!参数个数错误！");
//         return;
//     }
//     else
//     {
//         if (0 > bounded_VFS->createFile(getParam(1)))
//         {
//             Logcat::log("ERROR!存在同名文件，创建失败！");
//         }
//     }

//     Logcat::devlog(TAG, "touch EXEC");
// }

// /**
//  * 删除文件
//  */
// void Shell::rm()
// {
//     if (getParamAmount() != 2)
//     {
//         Logcat::log("ERROR!参数个数错误！");
//         return;
//     }
//     else
//     {
//         if (0 > bounded_VFS->deleteFile(getParam(1)))
//         {
//             Logcat::log("删除文件失败！");
//         }
//     }

//     Logcat::devlog(TAG, "rm EXEC");
// }

// /**
//  * 删除目录以及其下的所有文件
//  */
// void Shell::rmdir()
// {
//     if (getParamAmount() != 2)
//     {
//         Logcat::log("ERROR!参数个数错误！");
//         return;
//     }
//     else
//     {
//         if (0 > bounded_VFS->deleteDir(getParam(1)))
//         {
//             Logcat::log("删除，目录失败！");
//         }
//     }

//     Logcat::devlog(TAG, "rmdir EXEC");
// }

// void Shell::version()
// {
//     system("cat version");
//     Logcat::devlog(TAG, "version EXEC");
// }
// void Shell::man()
// {
//     Logcat::log(TAG, "欢迎求助那个男人");

//     Logcat::devlog(TAG, "man EXEC");
// }
// void Shell::mexit()
// {
//     if (bounded_VFS->isMounted())
//     {
//         bounded_VFS->unmount();
//     }
//     Logcat::devlog(TAG, "exit EXEC");
//     Logcat::log("程序结束！");
//     exit(OK);
// }

// /**
//  * 用户指令：更改当前目录
//  */
// void Shell::cd()
// {

//     //cd必须带参数
//     if (getParamAmount() != 2)
//     {
//         Logcat::log("Error!cd命令参数个数错误！");
//     }
//     else
//     {
//         bounded_VFS->cd(getParam(1));
//     }
// }

// /**
//  * ls函数可以带参数，也可以不带（curDir）
//  */
// void Shell::ls()
// {
//     if (!strcmp(getParam(1), ""))
//     {
//         //不带参数的ls，以curDir为默认参数
//         bounded_VFS->ls(VirtualProcess::Instance()->getUser().curDirInodeId);
//     }
//     else
//     {
//         bounded_VFS->ls(getParam(1)); //getParam(1)获得的是ls后面跟的目录名（可能是相对的也可能是绝对的）
//     }
// }

// /**
//  * 将外部文件考入虚拟磁盘.带两个命令参数
//  * Usage: store [src path] [des filename]
//  */
// void Shell::store()
// {
//     if (getParamAmount() == 3)
//     {
//         InodeId desInodeId;
//         //STORE的步骤
//         //Step1：创建文件（如果有同名的返回失败）
//         desInodeId = bounded_VFS->createFile(getParam(2));
//         if (desInodeId < 0)
//         {
//             Logcat::log("ERROR!目标文件名已存在！");
//             return;
//         }
//         //Step2：打开文件
//         Path desPath(getParam(2));
//         FileFd fd_des = bounded_VFS->open(desPath, File::FWRITE);
//         //Step3：写入文件
//         FILE *fd_src = fopen(getParam(1), "rb");
//         if (fd_src == NULL)
//         {
//             Logcat::log("源文件打开失败！");
//             return;
//         }
//         DiskBlock tempBuf;
//         int file_size = 0;
//         while (!feof(fd_src))
//         {
//             //int blkCount = 0;
//             int readsize = fread(&tempBuf, 1, DISK_BLOCK_SIZE, fd_src);
//             file_size += readsize;
//             bounded_VFS->write(fd_des, (u_int8_t *)&tempBuf, readsize);
//         }
//         Inode *p_desInode = Kernel::instance()->getInodeCache().getInodeByID(desInodeId);
//         p_desInode->i_size = file_size; //TODO这一块不太好，封装性差了点

//         //Step4：关闭文件
//         fclose(fd_src);
//         bounded_VFS->close(fd_des);
//     }
//     else
//     {
//         Logcat::log("ERROR!store命令参数个数错误");
//     }
// }

// /**
//  * 将文件从虚拟磁盘中拷出
//  * Usage: withdraw [src filename] [des outer_path]
//  */
// void Shell::withdraw()
// {
//     if (getParamAmount() == 3)
//     {
//         InodeId desInodeId;
//         //WITHDRAW的步骤
//         //Step1：创建文件（如果有同名的返回失败）
//         FILE *fd_des = fopen(getParam(2), "wb");
//         if (fd_des == NULL)
//         {
//             Logcat::log("目的文件创建失败！");
//             return;
//         }

//         //Step2：打开文件
//         Path srcPath(getParam(1));
//         FileFd fd_src = bounded_VFS->open(srcPath, File::FREAD);
//         if (fd_src < 0)
//         {
//             Logcat::log("源文件打开失败！");
//             return;
//         }
//         //Step3：写入文件
//         DiskBlock tempBuf;
//         while (!bounded_VFS->eof(fd_src))
//         {
//             //int blkCount = 0;
//             int writesize = bounded_VFS->read(fd_src, (u_int8_t *)&tempBuf, DISK_BLOCK_SIZE);
//             fwrite(&tempBuf, 1, writesize, fd_des);
//         }
//         //Step4：关闭文件
//         fclose(fd_des);
//         bounded_VFS->close(fd_src);
//     }
//     else
//     {
//         Logcat::log("ERROR!store命令参数个数错误");
//     }
// }

// void Shell::clear()
// {
//     system("clear");
// }

// void Shell::vim(FileName file_name)
// {
//     std::string command = std::string("vim ") + file_name;
//     system(command.c_str());
// }

// Shell::Shell()
// {
//     TAG = strdup("Shell");
// }
// Shell::~Shell()
// {
//     delete TAG;
// }

// void Shell::setVFS(VFS *vfs)
// {
//     bounded_VFS = vfs;
// }

#include "../include/Shell.h"
#include "../include/VirtualProcess.h"
#include "../include/Kernel.h"
#include <limits>

//上下键浏览历史、行编辑、撤销、退格头文件
#include <readline/readline.h>
#include <readline/history.h>


FileName fileName;

void Shell::help()
{
    system("cat help");
};

// 初始化 readline
void Shell::initReadline() {
    // 启用历史记录
    using_history();
    
    // 设置历史记录文件（可选）
    read_history(".shell_history");
    
    // 设置最大历史记录数量
    stifle_history(100);
    
    // 启用自动补全（可选）
    rl_bind_key('\t', rl_complete);
}

// 清理 readline
void Shell::cleanupReadline() {
    // 保存历史记录到文件
    write_history(".shell_history");
    
    // 清理历史记录
    clear_history();
}

int Shell::readUserInput() {
    // 初始化 readline
    initReadline();

    system("cat help");
    
    while (true) {


        std::string username = VirtualProcess::Instance()->IsLoggedIn() ? VirtualProcess::Instance()->getUserManager().getUsername() : "guest";

        std::string hostname = "ext2"; // 可替换为实际模拟器名或机器名
        std::string currentPath = bounded_VFS->getCurrentPath(); // 假设你已实现获取当前路径的函数

        std::string prompt = "[" + username + "@" + hostname + " " + currentPath + "]";
        prompt += (username == "root" ? "# " : "$ ");




        char* input = readline(prompt.c_str());
        
        // 处理 Ctrl+D (EOF)
        if (!input) {
            std::cout << std::endl;
            break;
        }

        // 跳过空行
        if (strlen(input) == 0) {
            free(input);
            continue;
        }

        // 添加到历史记录（只有非空且不重复的命令才添加）
        if (strlen(input) > 0) {
            // 检查是否与上一条命令重复
            HIST_ENTRY *last = history_get(history_length);
            if (!last || strcmp(last->line, input) != 0) {
                add_history(input);
            }
        }

        // 复制输入到缓冲区
        strncpy(tty_buffer, input, MAX_CMD_LEN - 1);
        tty_buffer[MAX_CMD_LEN - 1] = '\0';
        free(input);

        // 替换制表符为空格
        for (char *checker = strrchr(tty_buffer, '\t'); checker != NULL; checker = strrchr(checker, '\t')) {
            *checker = ' ';
        }

        char *dupl_tty_buffer = strdup(tty_buffer);
        memset(split_cmd, 0x0, sizeof(split_cmd));
        int cmd_param_seq = 0;
        for (char *p = strtok(dupl_tty_buffer, " "); p != nullptr; p = strtok(NULL, " "), cmd_param_seq++) {
            strcpy(split_cmd[cmd_param_seq], p);
        }
        param_num = cmd_param_seq;

        parseCmd();
        free(dupl_tty_buffer);  // 使用 free 而不是 delete，因为 strdup 使用 malloc
    }
    
    // 清理 readline
    cleanupReadline();
    return 0;
}

void Shell::parseCmd()
{
    switch (getInstType())
    {
    case MOUNT:
        mount();
        break;
    case UNMOUNT:
        unmount();
        break;
    case FORMAT:
        format();
        break;
    case CD:
        cd();
        break;
    case LS:
        ls(); //OK
        break;
    case CLOSE:
        close(); //OK
        break;
    case READ:
        read(); //OK
        break;
    case WRITE:
        write(); //OK
        break;
    case OPEN:
        open();
        break;
    case RM:
        rm();
        break;
    case RMDIR:
        rmdir();
        break;
    case MKDIR:
        mkdir();
        break;
    case TOUCH:
        touch();
        break;
    case CLEAR:
        clear();
        break;
    case HELP:
        help();
        break;
    case EXIT:
        mexit();
        break;
    case VERSION:
        version();
        break;
    case STORE:
        store();
        break;
    case WITHDRAW:
        withdraw();
        break;
    case VIM:
        fileName = split_cmd[1];
        vim(fileName);
        break;
    case LOGIN:
        login();
        break;
    case LOGOUT:
        logout();
        break;
    default:
        Logcat::log("CMD NOT SUPPORTED!\n");
        break;
    }
}

INSTRUCT Shell::getInstType()
{
    char *instStr = getInstStr();
#ifdef IS_DEBUG
    Logcat::log(TAG, "命令行命令字为:");
    Logcat::log(TAG, instStr);
#endif
    for (int i = 1; i < INST_NUM; i++)
    {
        if (!strcmp(instructStr[i], instStr))
        {
            return INSTRUCT(i - 1);
        }
    }
    return ERROR_INST;
}

char *Shell::getInstStr()
{
    return split_cmd[0];
}

char *Shell::getParam(int i)
{
    return split_cmd[i];
}

int Shell::getParamAmount()
{
    for (int i = 0; i < MAX_PARAM_NUM; i++)
    {
        if (!strcmp(split_cmd[i], ""))
        {
            return i;
        }
    }
    return MAX_PARAM_NUM;
}

void Shell::mount()
{
    Logcat::devlog(TAG, "MOUNT EXEC");
    bounded_VFS->mount();
}

void Shell::unmount()
{
    bounded_VFS->unmount();
    Logcat::devlog(TAG, "unmount EXEC");
}

void Shell::format()
{
    if (bounded_VFS->isMounted())
    {
        bounded_VFS->format();
        Logcat::devlog(TAG, "format EXEC");
    }
    else
    {
        Logcat::log(TAG, "ERROR,DISK NOT MOUNTED!");
    }
}

void Shell::mkdir()
{
    if (!VirtualProcess::Instance()->IsLoggedIn())
    {
        Logcat::log("请先登录再执行 mkdir 命令！");
        return;
    }

    if (getParamAmount() == 2)
    {
        if (bounded_VFS->mkDir(getParam(1)) < 0)
        {
            Logcat::log("ERROR!存在同名目录，创建失败！");
        }
    }
    else
    {
        Logcat::log("ERROR！MKDIR参数个数错误！");
    }
    Logcat::devlog(TAG, "mkdir EXEC");
}

void Shell::cat()
{
    Logcat::devlog(TAG, "cat EXEC");
    Logcat::log("cat 暂不支持");
}

void Shell::touch()
{
    if (!VirtualProcess::Instance()->IsLoggedIn())
    {
        Logcat::log("请先登录再执行 touch 命令！");
        return;
    }

    if (getParamAmount() != 2)
    {
        Logcat::log("ERROR!参数个数错误！");
        return;
    }
    else
    {
        if (0 > bounded_VFS->createFile(getParam(1)))
        {
            Logcat::log("ERROR!存在同名文件，创建失败！");
        }
    }

    Logcat::devlog(TAG, "touch EXEC");
}

void Shell::rm()
{
    if (getParamAmount() != 2)
    {
        Logcat::log("ERROR!参数个数错误！");
        return;
    }
    else
    {
        if (0 > bounded_VFS->deleteFile(getParam(1)))
        {
            Logcat::log("删除文件失败！");
        }
    }

    Logcat::devlog(TAG, "rm EXEC");
}

void Shell::rmdir()
{
    if (getParamAmount() != 2)
    {
        Logcat::log("ERROR!参数个数错误！");
        return;
    }
    else
    {
        if (0 > bounded_VFS->deleteDir(getParam(1)))
        {
            Logcat::log("删除目录失败！");
        }
    }

    Logcat::devlog(TAG, "rmdir EXEC");
}

void Shell::version()
{
    system("cat version");
    Logcat::devlog(TAG, "version EXEC");
}

void Shell::man()
{
    Logcat::log(TAG, "欢迎求助那个男人");
    Logcat::devlog(TAG, "man EXEC");
}

void Shell::mexit()
{
    if (bounded_VFS->isMounted())
    {
        bounded_VFS->unmount();
    }
    Logcat::devlog(TAG, "exit EXEC");
    Logcat::log("程序结束！");
    exit(OK);
}

void Shell::cd()
{
    if (getParamAmount() != 2)
    {
        Logcat::log("Error!cd命令参数个数错误！");
    }
    else
    {
        bounded_VFS->cd(getParam(1));
    }
}

void Shell::ls()
{
    if (!strcmp(getParam(1), ""))
    {
        bounded_VFS->ls(VirtualProcess::Instance()->getUser().curDirInodeId);
    }
    else
    {
        bounded_VFS->ls(getParam(1));
    }
}

/**
 * Shell中的open命令处理函数
 * 语法: open <文件名> [模式]
 * 模式: r(只读), w(只写), rw(读写), 默认为r
 */
FileFd Shell::open() {
    // 检查参数
    char* filename = getParam(1);
    if (!strcmp(filename, "")) {
        Logcat::log("Usage: open <filename> [mode]");
        return -1;
    }

    // 解析打开模式
    int mode = File::FREAD; // 默认只读
    char* modeStr = getParam(2);
    if (strcmp(modeStr, "") != 0) {
        if (!strcmp(modeStr, "r")) {
            mode = File::FREAD;
        } else if (!strcmp(modeStr, "w")) {
            mode = File::FWRITE;
        } else if (!strcmp(modeStr, "rw")) {
            mode = File::FREAD | File::FWRITE;
        } else {
            Logcat::log("Invalid mode. Use 'r', 'w' or 'rw'");
            return -1;
        }
    }

    // 调用VFS的open函数
    FileFd fd = bounded_VFS->open(Path(filename), mode);
    
    // 处理结果
    if (fd < 0) {
        switch (fd) {
            case ERROR_OPEN_ILLEGAL: {
                const char* msg = "Error: Can only open regular files";
                Logcat::log(msg);
                break;
            }
            case ERROR_OUTOF_OPENFILE: {
                const char* msg = "Error: Open file table full";
                Logcat::log(msg);
                break;
            }
            case ERROR_OUTOF_FILEFD: {
                const char* msg = "Error: Process file descriptor table full";
                Logcat::log(msg);
                break;
            }
            default: {
                const char* msg = "Error: Failed to open file";
                Logcat::log(msg);
            }
        }
        return -1;
    }

    // 返回文件描述符
    char msg[64];
    snprintf(msg, sizeof(msg), "File opened with fd: %d", fd);
    Logcat::log(msg);
    return fd;
}


/**
 * Shell中的write命令
 * 语法: write <fd> "<content>"
 * 示例: write 1 "hello world"
 */
int Shell::write() {
    char* fdStr = getParam(1);
    char* content = getParam(2);
    
    if (fdStr == nullptr || content == nullptr) {
        Logcat::log("Usage: write <fd> \"<content>\"");
        return -1;
    }

    int fd = atoi(fdStr);
    User& u = VirtualProcess::Instance()->getUser();
    
    // 仅检查fd非负和是否存在（OpenFiles内部会处理越界）
    if (fd < 0 || u.u_ofiles.GetF(fd) == nullptr) {
        Logcat::log("Error: Invalid file descriptor");
        return -1;
    }

    // 处理内容
    size_t len = strlen(content);
    if (len < 2 || content[0] != '"' || content[len-1] != '"') {
        Logcat::log("Error: Content must be enclosed in double quotes");
        return -1;
    }

    char* actualContent = new char[len - 1];
    strncpy(actualContent, content + 1, len - 2);
    actualContent[len - 2] = '\0';

    int bytesWritten = bounded_VFS->write(fd, (u_int8_t*)actualContent, len - 2);
    delete[] actualContent;

    if (bytesWritten < 0) {
        Logcat::log("Error: Write failed");
        return -1;
    }

    char msg[128];
    snprintf(msg, sizeof(msg), "Wrote %d bytes to fd %d", bytesWritten, fd);
    Logcat::log(msg);
    
    return bytesWritten;
}
/**
 * 将外部文件考入虚拟磁盘.带两个命令参数
 * Usage: store [src path] [des filename]
 */

 /**
 * Shell中的read命令
 * 语法: read <fd> <length>
 * 示例: read 0 100  (从fd=0读取100字节)
 */
int Shell::read() {
    // 检查参数
    char* fdStr = getParam(1);
    char* lengthStr = getParam(2);
    
    if (!fdStr[0] || !lengthStr[0]) {
        Logcat::log("Usage", "read <fd> <length>");
        return -1;
    }

    // 转换参数
    int fd = atoi(fdStr);
    int length = atoi(lengthStr);
    
    if (length <= 0) {
        Logcat::log("Error", "Length must be positive");
        return -1;
    }

    // 验证文件描述符
    User& u = VirtualProcess::Instance()->getUser();
    if (fd < 0 || u.u_ofiles.GetF(fd) == nullptr) {
        Logcat::log("Error", "Invalid file descriptor");
        return -1;
    }

    // 分配读取缓冲区
    u_int8_t* buffer = new u_int8_t[length + 1]; // +1 for null terminator
    memset(buffer, 0, length + 1);

    // 调用VFS读取
    int bytesRead = bounded_VFS->read(fd, buffer, length);
    
    // 处理结果
    if (bytesRead < 0) {
        Logcat::log("Error", "Read failed");
        delete[] buffer;
        return -1;
    }

    // 将结果转换为字符串格式输出
    char msg[256];
    snprintf(msg, sizeof(msg), "Read %d bytes", bytesRead);
    Logcat::log("READ", msg);
    
    // 确保缓冲区以null结尾
    buffer[bytesRead] = '\0';
    Logcat::log("CONTENT", reinterpret_cast<const char*>(buffer));

    delete[] buffer;
    return bytesRead;
}

/**
 * Shell中的close命令
 * 语法: close <fd>
 * 示例: close 3  (关闭文件描述符3)
 */
int Shell::close() {
    // 检查参数
    char* fdStr = getParam(1);
    if (fdStr == nullptr || !fdStr[0]) {
        Logcat::log("Usage", "close <fd>");
        return -1;
    }

    // 转换文件描述符
    int fd = atoi(fdStr);
    if (fd < 0) {
        Logcat::log("Error", "Invalid file descriptor");
        return -1;
    }

    // 调用VFS关闭
    int result = bounded_VFS->close(fd);
    
    // 处理结果
    if (result == OK) {
        char msg[64];
        snprintf(msg, sizeof(msg), "Closed fd %d", fd);
        Logcat::log("CLOSE", msg);
        return 0;
    } else {
        Logcat::log("Error", "Close failed");
        return -1;
    }
}
void Shell::store()
{
    if (getParamAmount() == 3)
    {
        InodeId desInodeId;
        desInodeId = bounded_VFS->createFile(getParam(2));
        if (desInodeId < 0)
        {
            Logcat::log("ERROR!目标文件名已存在！");
            return;
        }
        Path desPath(getParam(2));
        FileFd fd_des = bounded_VFS->open(desPath, File::FWRITE);
        FILE *fd_src = fopen(getParam(1), "rb");
        if (fd_src == NULL)
        {
            Logcat::log("源文件打开失败！");
            return;
        }
        DiskBlock tempBuf;
        int file_size = 0;
        while (!feof(fd_src))
        {
            int readsize = fread(&tempBuf, 1, DISK_BLOCK_SIZE, fd_src);
            file_size += readsize;
            bounded_VFS->write(fd_des, (u_int8_t *)&tempBuf, readsize);
        }
        Inode *p_desInode = Kernel::instance()->getInodeCache().getInodeByID(desInodeId);
        p_desInode->i_size = file_size;
        fclose(fd_src);
        bounded_VFS->close(fd_des);
    }
    else
    {
        Logcat::log("ERROR!store命令参数个数错误");
    }
}

void Shell::withdraw()
{
    if (getParamAmount() == 3)
    {
        FILE *fd_des = fopen(getParam(2), "wb");
        if (fd_des == NULL)
        {
            Logcat::log("目的文件创建失败！");
            return;
        }

        Path srcPath(getParam(1));
        FileFd fd_src = bounded_VFS->open(srcPath, File::FREAD);
        if (fd_src < 0)
        {
            Logcat::log("源文件打开失败！");
            return;
        }
        DiskBlock tempBuf;
        while (!bounded_VFS->eof(fd_src))
        {
            int writesize = bounded_VFS->read(fd_src, (u_int8_t *)&tempBuf, DISK_BLOCK_SIZE);
            fwrite(&tempBuf, 1, writesize, fd_des);
        }
        fclose(fd_des);
        bounded_VFS->close(fd_src);
    }
    else
    {
        Logcat::log("ERROR!withdraw命令参数个数错误");
    }
}

void Shell::clear()
{
    system("clear");
}

void Shell::vim(FileName file_name)
{
    std::string command = std::string("vim ") + file_name;
    system(command.c_str());
}

// void Shell::login()
// {
//     std::string username, password;
//     std::cout << "Username: ";
//     std::cin >> username;
//     std::cout << "Password: ";
//     std::cin >> password;

//     if (VirtualProcess::Instance()->Login(username, password))
//     {
//         Logcat::log("登录成功，欢迎 " + username + "！");
//     }
//     else
//     {
//         Logcat::log("登录失败，请检查用户名或密码。");
//     }

//     std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
// }

void Shell::login()
{
    if (getParamAmount() < 3)
    {
        Logcat::log("ERROR! login 命令需要用户名和密码参数！");
        return;
    }
    std::string username = getParam(1);
    std::string password = getParam(2);

    bool success = VirtualProcess::Instance()->Login(username, password);
    if (success)
    {
        Logcat::log(("登录成功，欢迎 " + username + "！").c_str());
    }
    else
    {
        Logcat::log("登录失败！");
    }
}



void Shell::logout()
{
    VirtualProcess::Instance()->Logout();
    Logcat::log("已注销登录，当前为匿名用户。");
}

Shell::Shell()
{
    TAG = strdup("Shell");
}

Shell::~Shell()
{
    delete TAG;
}

void Shell::setVFS(VFS *vfs)
{
    bounded_VFS = vfs;
}
