#ifndef OS_MAIN_DEFINE //确保不重复编译
#define OS_MAIN_DEFINE
//#define IS_DEBUG //调试状态

#include <iostream> //大家都懂
#include <stdio.h>
#include <cstring>    //用到str函数
#include <string>     //沈坚不让用的String类
#include <stdint.h>   //需要用到比特类型
#include <fcntl.h>    //open系统调用
#include <unistd.h>   //lseek函数
#include <sys/mman.h> //mmap函数
#include <sys/stat.h> //文件设置权限
#include <stdlib.h>   //随机数
#include <time.h>     //随机数种子要用

//const和define的区别》
#define DISK_BLOCK_SIZE 4096                         //每个磁盘块的大小（字节）
#define DISK_SIZE (64 * 1024 * 1024)                 //磁盘大小（字节）
#define DISK_BLOCK_NUM (DISK_SIZE / DISK_BLOCK_SIZE) //磁盘有多少个磁盘块
#define DISK_IMG_FILEPATH "./disk.img"
#define BITMAP_PERBLOCK_SIZE 8
#define BUFFER_CACHE_NUM 20
#define DISKINODE_SIZE 64
#define INODE_SIZE 64
#define MAX_BITMAP_ELEM_NUM DISK_BLOCK_NUM                   //这个Bitmap静态改造的一部分，原本的bitmap是动态申请的，但是放到磁盘很难办，于是去一个最大值
#define MAX_INODE_NUM (2 * DISK_BLOCK_SIZE / DISKINODE_SIZE) //用两块磁盘块存放inode，表示的是inode的最大数量，不是最大序号
#define MAX_PATH_LEVEL 10                                    //最大目录层次
#define MAX_FILENAME_LEN 28                                  //最长文件名
#define INODE_CACHE_SIZE 128                                 //系统可以缓存这么多inode
#define DIRECTORY_ENTRY_CACHE_SIZE 128                       //系统可以缓存这么多目录项
#define MIXED_ADDR_TABLE_SIZE (10 * sizeof(int))             //混合索引表数组所占空间的大小

// 成功码
#define OK 0

// 错误码 - 保持原有定义不变
#define ERROR_NOTSPEC -1                    // 并不想指明哪一种错误，但是是错误
#define ERROR_CANCEL -2                     // 操作取消
#define ERROR_PERMISSION_DENIED -3          // 权限不足
#define ERROR_OFR -4                        // 原有错误
#define ERROR_LBN_OVERFLOW -5               // 文件的逻辑块号大小溢出
#define ERROR_PATH_NFOUND -6                // 路径未找到
#define ERROR_OUTOF_INODE -7                // inode耗尽
#define ERROR_OPEN_ILLEGAL -8               // 非法打开操作
#define ERROR_OUTOF_OPENFILE -9             // 打开文件数超限
#define ERROR_OUTOF_FILEFD -10              // 文件描述符耗尽
#define ERROR_FILENAME_EXSIST -11           // 文件名已存在
#define ERROR_CLOSE_FAIL -12                // 关闭文件失败
#define ERROR_OUTOF_BLOCK -13               // 磁盘块耗尽
#define ERROR_DELETE_FAIL -14               // 删除失败
#define ERROR_NO_READ_PERMISSION -15        // 没有读权限
#define ERROR_NO_WRITE_PERMISSION -16       // 没有写权限

// 新增的文件系统相关错误码
#define ERROR_FILE_NOT_FOUND -17            // 文件不存在
#define ERROR_DIR_NOT_FOUND -18             // 目录不存在
#define ERROR_IS_A_DIRECTORY -19            // 目标是目录（当期望文件时）
#define ERROR_NOT_A_DIRECTORY -20           // 目标不是目录（当期望目录时）
#define ERROR_DIR_NOT_EMPTY -21             // 目录非空
#define ERROR_CANNOT_DELETE_CWD -22         // 不能删除当前工作目录

// 后面新增
#define ERROR_PATH_NOT_FOUND -23


typedef int FileFd;  //文件句柄，实际上就是一个int
typedef int InodeId; //inode号，实际上是一个int
typedef int BlkNum;  //扇区号

typedef const char *FileName; //文件名

enum INSTRUCT
{
    ERROR_INST = -1,
    MOUNT,
    UNMOUNT,
    FORMAT,
    CD,
    LS,
    CLOSE,
    READ,
    WRITE,
    OPEN,
    RM,
    MKDIR,
    TOUCH,
    CLEAR,
    HELP,
    EXIT,
    VERSION,
    STORE,
    WITHDRAW,
    RMDIR,
    VIM,
    LOGIN,
    LOGOUT
};
const int INST_NUM = 23;//17+2=19
//NOTE 注意，如果改了上面的枚举类型，那么下面的这个数字也需要相应修改

static const char *instructStr[]{
    "error", //实际上会从下表1开始查找，这个"error"是为了占位置
    "mount",
    "unmount",
    "format",
    "cd",
    "ls",
    "close",
    "read",
    "write",
    "open",
    "rm",
    "mkdir",
    "touch",
    "clear",
    "help",
    "exit",
    "version",
    "store",
    "withdraw",
    "rmdir",
    "vim",
    "login",
    "logout"
};
enum FileType
{
    NORMAL_FILE,
    DIRECTORY,
    DEVICE
};

#endif

/**
 * 类型定义的反思：
 * 写到一半，发现如果把inodeNum、DiskBlockNum这种用typedef类型定义会更好。
 * 因为可能会中途想改变他们的数据类型，再去挨个找的话太困难了：函数返回类型、形参类型等一堆
 * 
 */