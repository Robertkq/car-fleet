#ifndef CAR_FLEET_CPP_CAR_H
#define CAR_FLEET_CPP_CAR_H

#include "common.h"

struct car
{
    public:
        car();
        car(const car& other);
        car(car&& other) noexcept;
        car(const std::string& brand, const std::string& type, const std::string& license_plate, const std::string& color,
            uint32_t doors, uint32_t year, uint32_t price, uint32_t km);
            
        car& operator=(const car& other);
        car& operator=(car&& other) noexcept;

        void print_detailed() const;

    public:
        std::string m_brand;
        std::string m_type;
        std::string m_license_plate;
        std::string m_color;
        uint32_t m_doors;
        uint32_t m_year;
        uint32_t m_price;
        uint32_t m_km;
};

#endif