/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#ifndef TRANSFERFILES_H
#define TRANSFERFILES_H

#include <string>
#include <map>

class TransferFilesManager {
public:
    static TransferFilesManager& getInstance() {
        static TransferFilesManager instance;
        return instance;
    }

    struct FileItemInfo{
        size_t id;
        std::string path;
    };
    TransferFilesManager(const TransferFilesManager&) = delete;
    void operator=(const TransferFilesManager&) = delete;

    std::string getPath(const unsigned int& id) { return id_path[id]; }
    void addFileInfo(const unsigned int& id, std::string path) { id_path.insert({id, path}); }

private:
    TransferFilesManager(){};
    std::map<unsigned int, std::string> id_path;
};

#endif  //TRANSFERFILES_H