/*
 *    Author:       Can Cui(cuican01@baidu.com)
 *    Copyright:    Copyright 2013, Baidu Inc.
 *    Description:  封装的一些和文件目录相关的操作
 */

#ifndef INF_DS_BOSS_SDK_C_TEST_FILE_URIL_H_
#define INF_DS_BOSS_SDK_C_TEST_FILE_URIL_H_
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <string>
#include <vector>

class FileUtil {
public:
    static bool Exist(const std::string &filename) {
        return ::access(filename.c_str(), F_OK) == 0;
    }

    static bool Rename(const std::string &src, const std::string &dest) {
        return ::rename(src.c_str(), dest.c_str()) == 0;
    }

    static int64_t Size(const std::string &filename) {
        struct stat st;
        int ret = stat(filename.c_str(), &st);
        if (ret != 0) {
            return ret;
        }

        return st.st_size;
    }

    static int Mkdir(const std::string &dir_name) {
        return mkdir(dir_name.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    }

    // 递归的删除一个目录或者文件
    static int Remove(const std::string &dir) {
        if (IsFile(dir)) {
            return ::remove(dir.c_str());
        }

        std::vector<std::string> children;
        if (FileUtil::ListDir(dir, &children)) {
            return -1;
        }

        for (size_t i = 0; i < children.size(); i++) {
            if (children[i] == "." || children[i] == "..") {
                continue;
            }
            if (Remove(dir + "/" + children[i])) {
                return -1;
            }
        }

        return ::remove(dir.c_str());
    }

    static int ListDir(const std::string &dir_name, std::vector<std::string> *children) {
        if (children == NULL) {
            return -1;
        }

        DIR *dir = opendir(dir_name.c_str());
        if (dir == NULL) {
            return -2;
        }

        struct dirent *dirent = NULL;
        while ((dirent = readdir(dir)) != NULL) { // NOLINT
            children->push_back(std::string(dirent->d_name));
        }

        closedir(dir);

        return 0;
    }

    static bool IsFile(const std::string &filename) {
        struct stat stat_info;
        if (!stat(filename.c_str(), &stat_info)) {
            return S_ISREG(stat_info.st_mode);
        }

        return false;
    }

    static int WriteAll(int fd, const void *data, int len) {
        int data_write = 0;
        while (data_write < len) {
            int current_write = write(fd, reinterpret_cast<const char *>(data) + data_write,
                    len - data_write);

            if (current_write <= 0) {
                return current_write;
            }

            data_write += current_write;
        }
        return data_write;
    }

    static int ReadAll(int fd, void *buffer, int len) {
        int data_read = 0;
        while (data_read < len) {
            int current_read = read(fd, reinterpret_cast<char *>(buffer) + data_read,
                    len - data_read);

            if (current_read < 0) {
                return current_read;
            }

            if (current_read  == 0) {
                break;
            }

            data_read += current_read;
        }
        return data_read;
    }

    static int ReadFile(const std::string &filename, void *buffer, int len) {
        int fd = open(filename.c_str(), O_RDONLY);
        if (fd < 0) {
            return fd;
        }

        int byte_read = ReadAll(fd, buffer, len);
        close(fd);
        return byte_read;
    }

    static int ReadAllFile(const std::string &filename, std::string *buffer) {
        int64_t size = Size(filename);
        if (size < 0) {
            return static_cast<int32_t>(size);
        }

        char *c_buffer = new char[size];
        int ret = ReadFile(filename, c_buffer, size);

        if (ret < 0) {
            delete []c_buffer;
        }

        buffer->assign(c_buffer, ret);
        delete []c_buffer;
        return ret;
    }

    static int WriteFile(const std::string &filename, const void *buffer, int len) {
        int fd = open(filename.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0) {
            return fd;
        }

        int byte_write = WriteAll(fd, buffer, len);
        close(fd);
        return byte_write;
    }

    static int WriteFile(const std::string &filename, const std::string &data) {
        return WriteFile(filename, data.data(), data.size());
    }

    static int LastModifyTime(const std::string &filename) {
        struct stat st;
        int ret = stat(filename.c_str(), &st);
        if (ret != 0) {
            return ret;
        }

        return st.st_mtime;
    }

    static int LastChangeTime(const std::string &filename) {
        struct stat st;
        int ret = stat(filename.c_str(), &st);
        if (ret != 0) {
            return ret;
        }

        return st.st_ctime;
    }

    static int LastAccessTime(const std::string &filename) {
        struct stat st;
        int ret = stat(filename.c_str(), &st);
        if (ret != 0) {
            return ret;
        }

        return st.st_atime;
    }

    static int WriteCrcFile(const std::string &filename, const std::string &data) {
        return WriteFile(filename, data);
    }

    static int ReadCrcFile(const std::string &filename, std::string *data) {
        return ReadAllFile(filename, data);
    }

    static int WriteAtomicFile(const std::string &filename, const std::string &data) {
        if (CheckAndRepairAtomicFile(filename)) {
            return -1;
        }

        std::vector<std::string> sub_names;
        GenerateAtomicFileNames(filename, &sub_names);
        if (WriteCrcFile(sub_names[0], data)) {
            return -1;
        }

        if (WriteCrcFile(sub_names[1], data)) {
            return -1;
        }

        if (WriteCrcFile(sub_names[2], data)) {
            return -1;
        }

        return 0;
    }

    static int ReadAtomicFile(const std::string &filename, std::string *data) {
        std::vector<std::string> sub_names;
        GenerateAtomicFileNames(filename, &sub_names);

        return 0;
    }

private:
    static int CheckAndRepairAtomicFile(const std::string &filename) {
        std::vector<std::string> sub_names;
        GenerateAtomicFileNames(filename, &sub_names);

        // create file if not exist
        for (uint32_t i = 0; i < sub_names.size(); i++) {
            if (!Exist(sub_names[i])) {
                if (WriteCrcFile(sub_names[i], "")) {
                    return -1;
                }
            }
        }

        std::string data1;
        std::string data2;
        std::string data3;

        int read_file1_ret = ReadCrcFile(sub_names[0], &data1);
        int read_file2_ret = ReadCrcFile(sub_names[0], &data2);
        int read_file3_ret = ReadCrcFile(sub_names[0], &data3);

        if (read_file1_ret || read_file2_ret || read_file3_ret) {
            return -1;
        }
        return 0;
    }

    static int GenerateAtomicFileNames(const std::string &filename, std::vector<std::string> *sub_names) {
        sub_names->push_back(filename + std::string(".1"));
        sub_names->push_back(filename + std::string(".2"));
        sub_names->push_back(filename + std::string(".3"));

        return 0;
    }
}; // end class FileUtil
#endif //INF_DS_BOSS_SDK_C_TEST_FILE_URIL_H_
