#include "filemanager.h"
#include "car.h"

FileManager::FileManager(const std::string& filename)
    : m_file(filename)
{}

void FileManager::LoadFromFile(std::vector<car>& buffer)
{
    
    m_file.seekg(0);
    uint32_t number_cars;
    m_file >> number_cars;
    buffer.reserve(number_cars);
    for(uint32_t i = 0; i < number_cars; ++i)
    {
        car aux;
        m_file >> aux.m_brand >> aux.m_type >> aux.m_license_plate >>
            aux.m_color >> aux.m_doors >> aux.m_year >>
            aux.m_price >> aux.m_km;
        buffer.push_back(aux);
    }
}

void FileManager::SaveToFile(const std::vector<car>& buffer)
{
    m_file.seekp(0);
    m_file << buffer.size() << '\n';
    for(uint32_t i = 0; i < buffer.size(); ++i)
    {
        m_file << buffer[i].m_brand << '\n' << buffer[i].m_type << buffer[i].m_license_plate <<
            buffer[i].m_color << buffer[i].m_doors << buffer[i].m_year <<
            buffer[i].m_price << buffer[i].m_km;
    }
}


