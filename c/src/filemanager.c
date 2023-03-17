#include "filemanager.h"

car_t* ReadFromFile(int* num_of_cars)
{
    FILE* file = fopen("cars.txt", "r");
    if(file == NULL)
    {
        printf("Error: Couldn't open cars.txt\n");
        return NULL;
    }
    fscanf(file, "%d", num_of_cars);
    car_t* buffer = (car_t*)malloc(sizeof(car_t)*(*num_of_cars));
    for(int i = 0; i < *num_of_cars; ++i)
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

}
