#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <string>

namespace FileUtils {
    bool fileExists(const std::string& filePath);
    std::string getFileName(const std::string& filePath);
    long getFileSize(const std::string& filePath);
}

#endif // FILE_UTILS_H