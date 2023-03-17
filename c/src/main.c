#include "menus.h"
#include "filemanager.h"

int num_cars;
car_t* buffer_cars;

int main()
{
    buffer_cars = ReadFromFile(&num_cars);
    while(main_menu());
    printf("\nProcess ended...");
    return 0;
}