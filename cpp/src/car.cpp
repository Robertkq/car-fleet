#include "car.h"

car::car()
    : m_brand(), m_type(), m_license_plate(), m_color(), m_doors(), m_year(), m_price(), m_km()
{

}

std::string car::print_resume() const
{
    return "Brand: " + m_brand + ", Type: " + m_type 
    + ", Plate: " + m_license_plate + ", Color: " + m_color;
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