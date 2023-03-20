#include "filemanager.h"

car_t* ReadFromFile()
{
    FILE* file = fopen("cars.txt", "r");
    if(file == NULL)
    {
        printf("Error: Couldn't open cars.txt\n");
        return NULL;
    }
    fscanf(file, "%u", &num_cars);
    car_t* buffer = (car_t*)malloc(sizeof(car_t)*(num_cars));
    for(uint32_t i = 0; i < num_cars; ++i)
    {
        fscanf(file, "%s", buffer[i].brand);
        fscanf(file, "%s", buffer[i].type);
        fscanf(file, "%s", buffer[i].license_plate);
        fscanf(file, "%s", buffer[i].color);
    }
    return buffer;
}

void WriteToFile()
{
    FILE* file = fopen("cars.txt", "w");
    if(file == NULL)
    {
        printf("Error: Couldn't open cars.txt\n");
        return;
    }
    fprintf(file, "%u\n", num_cars);
    for(uint32_t i = 0; i < num_cars; ++i)
    {
        fprintf(file, "%s\n%s\n%s\n%s\n", buffer_cars[i].brand, buffer_cars[i].type, buffer_cars[i].license_plate, buffer_cars[i].color);
    }
}
