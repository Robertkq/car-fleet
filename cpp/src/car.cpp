#include "car.h"

car::car()
    : m_brand(), m_type(), m_license_plate(), m_color(), m_doors(), m_year(), m_price(), m_km()
{

}

car::car(const car& other)
    : m_brand(other.m_brand), m_type(other.m_type), m_license_plate(other.m_license_plate), m_color(other.m_color),
    m_doors(other.m_doors), m_year(other.m_year), m_price(other.m_price), m_km(other.m_km)
{
    
}

car::car(car&& other) noexcept
    : m_brand(std::move(other.m_brand)), m_type(std::move(other.m_type)), m_license_plate(std::move(other.m_license_plate)), m_color(std::move(other.m_color)),
    m_doors(other.m_doors), m_year(other.m_year), m_price(other.m_price), m_km(other.m_km)
{

}

car::car(const std::string& brand, const std::string& type, const std::string& license_plate, const std::string& color,
            uint32_t doors, uint32_t year, uint32_t price, uint32_t km)
    : m_brand(brand), m_type(type), m_license_plate(license_plate), m_color(color),
    m_doors(doors), m_year(year), m_price(price), m_km(km)
{
    
}

car& car::operator=(const car& other)
{
    if(this != &other)
    {
        m_brand = other.m_brand;
        m_type = other.m_type;
        m_license_plate = other.m_license_plate;
        m_color = other.m_color;
        m_doors = other.m_doors;
        m_year = other.m_year;
        m_price = other.m_price;
        m_km = other.m_km;
    }
    return *this;
}

car& car::operator=(car&& other) noexcept
{
    if(this != &other)
    {
        m_brand = std::move(other.m_brand);
        m_type = std::move(other.m_type);
        m_license_plate = std::move(other.m_license_plate);
        m_color = std::move(other.m_color);
        m_doors = other.m_doors;
        m_year = other.m_year;
        m_price = other.m_price;
        m_km = other.m_km;
    }
    return *this;
}

void car::print_detailed() const
{
    ImGui::Text((std::string("Brand: ") + m_brand).data());
    ImGui::Text((std::string("Type: ") + m_type).data());
    ImGui::Text((std::string("License Plate: ") + m_license_plate).data());
    ImGui::Text((std::string("Color: ") + m_color).data());
    ImGui::Text((std::string("Doors: ") + itos(m_doors)).data());
    ImGui::Text((std::string("Year: ") + itos(m_year)).data());
    ImGui::Text((std::string("Price: ") + itos(m_price)).data());
    ImGui::Text((std::string("Kilometers: ") + itos(m_km)).data());
}