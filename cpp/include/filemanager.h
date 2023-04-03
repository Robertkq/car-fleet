#ifndef CAR_CLEET_CPP_FILEMANAGER_H
#define CAR_FLEET_CPP_FILEMANAGER_H

#include "common.h"
#include "car.h"

struct FileManager
{
    public:
        FileManager(const std::string& filename);
        void LoadFromFile(std::vector<car>& buffer);
        void SaveToFile(const std::vector<car>& buffer);
    private:
        std::string m_filename;
        std::fstream m_file;
};

#endif