#ifndef CAR_H
#define CAR_H

#include "common.h"

typedef struct car
{
    char brand[15];
    char type[15];
    char license_plate[15];
    char color[15];
}car_t;

void add_car(car_t* buffer, uint32_t pos);
void remove_car(car_t* buffer, uint32_t num_cars, uint32_t pos);

car_t* realloc_car(car_t* buffer, uint32_t num_cars, uint32_t new_cars);

#endif