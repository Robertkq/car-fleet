#ifndef CAR_FLEET_CPP_CAR_H
#define CAR_FLEET_CPP_CAR_H

#include "common.h"

struct car
{
    public:
        car();
        std::string print_resume() const;
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