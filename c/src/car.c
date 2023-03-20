#include "car.h"

void add_car(car_t* buffer, uint32_t pos)
{
    printf("Brand of the new car: ");
    scanf("%s", buffer[pos].brand);
    printf("Type of the new car: ");
    scanf("%s", buffer[pos].type);
    printf("License Plate of the new car: ");
    scanf("%s", buffer[pos].license_plate);
    printf("Color of the new car: ");
    scanf("%s", buffer[pos].color);
}

void remove_car(car_t* buffer, uint32_t num_cars, uint32_t pos)
{
    for(uint32_t i = pos; i < num_cars - 1; ++i)
    {
        my_strcpy(buffer[i].brand, buffer[i+1].brand);
        my_strcpy(buffer[i].type, buffer[i+1].type);
        my_strcpy(buffer[i].license_plate, buffer[i+1].license_plate);
        my_strcpy(buffer[i].color, buffer[i+1].color);
    }
}

car_t* realloc_car(car_t* buffer, uint32_t num_cars, uint32_t new_cars)
{
    car_t* new_buffer = (car_t*)malloc(sizeof(car_t)*new_cars);
    if(new_buffer == NULL)
    {
        printf("Error: couldn't allocate for %d cars\n", new_cars);
        return NULL;
    }
    for(uint32_t i = 0; i < num_cars; ++i)
    {
        my_strcpy(new_buffer[i].brand, buffer[i].brand);
        my_strcpy(new_buffer[i].type, buffer[i].type);
        my_strcpy(new_buffer[i].license_plate, buffer[i].license_plate);
        my_strcpy(new_buffer[i].color, buffer[i].color);
    }
    free(buffer);
    return new_buffer;
}