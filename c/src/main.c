#include "menus.hpp"
#include "filemanager.hpp"
#include "car.hpp"

uint32_t num_cars;
car_t* buffer_cars;

int main()
{
    buffer_cars = ReadFromFile();
    while(main_menu());
    printf("\nProcess ended...");
    WriteToFile();
    return 0;
}