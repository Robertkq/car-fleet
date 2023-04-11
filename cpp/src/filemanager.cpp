#include "filemanager.h"
#include "car.h"

FileManager::FileManager(const std::string& filename)
    : m_filename(filename), m_file()
{}

void FileManager::LoadFromFile(std::vector<car>& buffer)
{
    m_file.open(m_filename.data());
    if(m_file.is_open())
    {
        if(m_file.peek() == std::fstream::traits_type::eof())
            return;
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
    else
    {
        std::cout << "Couldn't open " << m_filename << '\n';
    }
    m_file.close();
}

void FileManager::SaveToFile(const std::vector<car>& buffer)
{
    m_file.close(); // This fixes the file output problem but why ? I close the file in the reading part as well...
    m_file.open(m_filename.data());
    if(m_file.is_open())
    {
        m_file << buffer.size() << '\n';
        for(uint32_t i = 0; i < buffer.size(); ++i)
        {
            m_file << buffer[i].m_brand << '\n' << buffer[i].m_type << '\n' << buffer[i].m_license_plate << '\n' <<
                buffer[i].m_color << '\n' << buffer[i].m_doors << '\n' << buffer[i].m_year << '\n' <<
                buffer[i].m_price << '\n' << buffer[i].m_km << '\n';
        }
        m_file.flush();
    }
    else
    {
        std::cout << "Couldn't open " << m_filename << '\n';
    }
    m_file.close();
}


