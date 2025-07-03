# user_fs : user_fs.o  main.o  Shell.o DirectoryEntry.o File.o VFS.o User.o VirtualProcess.o Logcat.o DiskBlock.o Ext2.o SuperBlock.o InodePool.o Bitmap.o Path.o BufferCache.o InodeCache.o DirectoryCache.o BufferLruList.o Kernel.o DiskInode.o DiskDriver.o Inode.o SuperBlockCache.o TimeHelper.o OpenFileTable.o
# 	g++ -g -o user_fs main.o  Shell.o DirectoryEntry.o File.o VFS.o User.o VirtualProcess.o Logcat.o DiskBlock.o Ext2.o SuperBlock.o InodePool.o Bitmap.o Path.o BufferCache.o InodeCache.o DirectoryCache.o BufferLruList.o Kernel.o DiskInode.o DiskDriver.o Inode.o SuperBlockCache.o TimeHelper.o Buf.o OpenFileTable.o
	
# user_fs.o : main.cpp include/define.h include/DirectoryEntry.h include/DiskDriver.h include/DiskInode.h include/File.h include/Inode.h include/Shell.h  include/User.h include/VFS.h include/VirtualProcess.h Shell/Shell.cpp VFS/DirectoryEntry.cpp VFS/File.cpp VFS/VFS.cpp VirtualProcess/User.cpp VirtualProcess/VirtualProcess.cpp include/Logcat.h Utils/Logcat.cpp include/DiskBlock.h DiskDriver/DiskBlock.cpp include/Ext2.h Ext2/Ext2.cpp Ext2/SuperBlock.cpp include/SuperBlock.h include/InodePool.h Ext2/InodePool.cpp include/Bitmap.h Utils/Bitmap.cpp include/Path.h Ext2/Path.cpp include/BufferCache.h BufferCache/BufferCache.cpp include/InodeCache.h VFS/InodeCache.cpp include/DirectoryCache.h VFS/DirectoryCache.cpp include/BufferLruList.h BufferCache/BufferLruList.cpp include/Kernel.h VirtualProcess/Kernel.cpp DiskDriver/DiskDriver.cpp Ext2/DiskInode.cpp VFS/Inode.cpp VFS/SuperBlockCache.cpp include/SuperBlockCache.h include/TimeHelper.h Utils/TimeHelper.cpp BufferCache/Buf.cpp include/Buf.h include/OpenFileTable.h VFS/OpenFileTable.cpp
# 	g++ -g -c main.cpp include/define.h include/DirectoryEntry.h include/DiskDriver.h include/DiskInode.h include/File.h include/Inode.h include/Shell.h  include/User.h include/VFS.h include/VirtualProcess.h Shell/Shell.cpp VFS/DirectoryEntry.cpp VFS/File.cpp VFS/VFS.cpp VirtualProcess/User.cpp VirtualProcess/VirtualProcess.cpp include/Logcat.h Utils/Logcat.cpp include/DiskBlock.h DiskDriver/DiskBlock.cpp include/Ext2.h Ext2/Ext2.cpp Ext2/SuperBlock.cpp include/SuperBlock.h include/InodePool.h Ext2/InodePool.cpp include/Bitmap.h Utils/Bitmap.cpp include/Path.h Ext2/Path.cpp include/BufferCache.h BufferCache/BufferCache.cpp include/InodeCache.h VFS/InodeCache.cpp include/DirectoryCache.h VFS/DirectoryCache.cpp include/BufferLruList.h BufferCache/BufferLruList.cpp include/Kernel.h VirtualProcess/Kernel.cpp DiskDriver/DiskDriver.cpp Ext2/DiskInode.cpp VFS/Inode.cpp VFS/SuperBlockCache.cpp include/SuperBlockCache.h include/TimeHelper.h Utils/TimeHelper.cpp BufferCache/Buf.cpp include/Buf.h include/OpenFileTable.h VFS/OpenFileTable.cpp -std=c++11 -lpthread

# all: user_fs
# # 	g++ -g main.cpp include/define.h include/DirectoryEntry.h include/DiskDriver.h include/DiskInode.h include/File.h include/Inode.h include/Shell.h  include/User.h include/VFS.h include/VirtualProcess.h Shell/Shell.cpp VFS/DirectoryEntry.cpp VFS/File.cpp VFS/VFS.cpp VirtualProcess/User.cpp VirtualProcess/VirtualProcess.cpp  -o  ext2_fs -std=c++11 -lpthread
# clean:
# 	rm -rf include/*.gch *.o


# ######################################################################################
# CXX = g++
# CXXFLAGS = -g -std=c++11 -lpthread -lreadline -lncurses

# SRC_DIRS = Shell VFS VirtualProcess DiskDriver Ext2 BufferCache Utils
# INCLUDE_DIR = include

# SRCS = main.cpp \
#     $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.cpp))

# OBJS = $(SRCS:.cpp=.o)

# TARGET = fs

# $(TARGET): $(OBJS)
# 	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# %.o: %.cpp
# 	$(CXX) -g -c $< -o $@

# clean:
# 	rm -f $(OBJS) $(TARGET)
# 	find . -name '*.gch' -delete
#########################################################################################

CXX = g++
CXXFLAGS = -g -std=c++11 -I$(INCLUDE_DIR)
LDFLAGS = -lpthread -lreadline -lncurses
SRC_DIRS = Shell VFS VirtualProcess DiskDriver Ext2 BufferCache Utils
INCLUDE_DIR = include

# 修正通配符路径 - 从 $(dir)/.cpp 改为 $(dir)/*.cpp
SRCS = main.cpp \
    $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.cpp))

OBJS = $(SRCS:.cpp=.o)
TARGET = fs

# 主目标 - 在链接阶段添加库
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)

# 编译规则 - 只包含编译标志，不包含链接库
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
	find . -name '*.gch' -delete

.PHONY: clean

# 调试信息 - 可以用 make debug 查看变量值
debug:
	@echo "SRCS: $(SRCS)"
	@echo "OBJS: $(OBJS)"
	@echo "SRC_DIRS: $(SRC_DIRS)"