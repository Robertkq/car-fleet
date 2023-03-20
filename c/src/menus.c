#include "menus.h"

char main_menu_choices[2][13];
char view_menu_choices[5][20];

void edit_menu_init()
{
    reset_input();
    system("cls");
    static uint32_t initialized = 0;
    if(initialized)
        return;
    initialized = 1;
}

uint32_t edit_menu()
{
    static uint32_t selection_index = 0;
    static uint32_t keys[3]      = { 0, 0, 0 },
            old_keys[3]     = { 0, 0, 0 };

    edit_menu_init();

    for(uint32_t i = 0; i < num_cars; ++i)
    {
        if(selection_index == i)
            color(2);
        printf("%d: %s, %s, %s, %s\n",
            i, buffer_cars[i].brand, buffer_cars[i].type, buffer_cars[i].license_plate, buffer_cars[i].color);
        color(7);
    }
    if(selection_index == num_cars)
        color(2);
    printf("%d: Back\n", num_cars);
    color(7);

    while(1)
    {
        for(uint32_t i = 0; i < 3; ++i)
            old_keys[i] = keys[i];
        keys[0] = GetAsyncKeyState(VK_DOWN);
        keys[1] = GetAsyncKeyState(VK_UP);
        keys[2] = GetAsyncKeyState(VK_CONTROL);
        if(keys[0] && !old_keys[0])
        {
            if(selection_index == num_cars)
                selection_index = 0;
            else
                ++selection_index;
            return 1;
        }
        if(keys[1] && !old_keys[1])
        {
            if(selection_index == 0)
                selection_index = num_cars;
            else
                --selection_index;
            return 1;
        }
        if(keys[2] && !old_keys[2])
        {
            if(selection_index == num_cars)
                return 0;
            else
            {
                system("cls");
                printf("Information about the car you wish to edit:\n"
                "Brand: %s\nType: %s\nLicense Plate: %s\nColor: %s\n\n",
                buffer_cars[selection_index].brand, buffer_cars[selection_index].type,
                buffer_cars[selection_index].license_plate, buffer_cars[selection_index].color);
                add_car(buffer_cars, selection_index);
                return 1;
            }
        }
        Sleep(10);
    }
}

void search_menu_init()
{
    reset_input();
    system("cls");
    static uint32_t initialized = 0;
    if(initialized)
        return;
    initialized = 1;
}

uint32_t search_menu()
{
    static uint32_t selection_index = 0;
    static uint32_t keys[3]      = { 0, 0, 0 },
            old_keys[3]     = { 0, 0, 0 };
    search_menu_init();
    car_t match_me;
    printf("Provide information about the car(s) you want to search for.\nEntry \"*\" to match any.\n");
    printf("Brand: ");
    scanf("%s", match_me.brand);
    printf("Type: ");
    scanf("%s", match_me.type);
    printf("License Plate: ");
    scanf("%s", match_me.license_plate);
    printf("Color: ");
    scanf("%s", match_me.color);
    
    printf("Results:\n");
    for(uint32_t i = 0; i < num_cars; ++i)
    {
        if(!strcmp(match_me.brand, "*") || !strcmp(match_me.brand, buffer_cars[i].brand))
            if(!strcmp(match_me.type, "*") || !strcmp(match_me.type, buffer_cars[i].type))
                if(!strcmp(match_me.license_plate, "*") || !strcmp(match_me.license_plate, buffer_cars[i].license_plate))
                    if(!strcmp(match_me.color, "*") || !strcmp(match_me.color, buffer_cars[i].color))
                        printf("%d: %s, %s, %s, %s\n", 
                            i, buffer_cars[i].brand, buffer_cars[i].type, buffer_cars[i].license_plate, buffer_cars[i].color);
    }
    color(2);
    printf("Back\n");
    color(7);
    while(1)
    {
        for(uint32_t i = 0; i < 3; ++i)
            old_keys[i] = keys[i];
        keys[0] = GetAsyncKeyState(VK_DOWN);
        keys[1] = GetAsyncKeyState(VK_UP);
        keys[2] = GetAsyncKeyState(VK_CONTROL);
        if(keys[2] && !old_keys[2])
        {
            return 0;
        }
        Sleep(10);
    }
}

void remove_menu_init()
{

}

int remove_menu()
{
    static uint32_t selection_index = 0;
    static uint32_t keys[3]      = { 0, 0, 0 },
            old_keys[3]     = { 0, 0, 0 };

    view_menu_init();
    printf("Select a car to remove:\n");
    for(uint32_t i = 0; i < num_cars; ++i)
    {
        if(selection_index == i)
            color(2);
        printf("%d: %s, %s, %s, %s\n", 
            i, buffer_cars[i].brand, buffer_cars[i].type, buffer_cars[i].license_plate, buffer_cars[i].color);
        color(7);
    }
    if(selection_index == num_cars)
        color(2);
    printf("%d: Back\n", num_cars);
    color(7);
    while(1)
    {
        for(uint32_t i = 0; i < 3; ++i)
            old_keys[i] = keys[i];
        keys[0] = GetAsyncKeyState(VK_DOWN);
        keys[1] = GetAsyncKeyState(VK_UP);
        keys[2] = GetAsyncKeyState(VK_CONTROL);
        if(keys[0] && !old_keys[0])
        {
            if(selection_index == num_cars)
                selection_index = 0;
            else
                ++selection_index;
            return 1;
        }
        if(keys[1] && !old_keys[1])
        {
            if(selection_index == 0)
                selection_index = num_cars;
            else
                --selection_index;
            return 1;
        }
        if(keys[2] && !old_keys[2])
        {
            if(selection_index == num_cars)
            {
                return 0;
            }
            else
            {
                printf("Remove %d\n", selection_index);
                remove_car(buffer_cars, num_cars, selection_index);
                --num_cars;
                return 1;
            }
        }
        Sleep(10);
    }
}

void view_menu_init()
{
    reset_input();
    system("cls");
    static uint32_t initialized = 0;
    if(initialized)
        return;
    initialized = 1;
    my_strcpy(view_menu_choices[0], "Add Vehicle");
    my_strcpy(view_menu_choices[1], "Edit Vehicle");
    my_strcpy(view_menu_choices[2], "Search Vehicle");
    my_strcpy(view_menu_choices[3], "Remove Vehicle");
    my_strcpy(view_menu_choices[4], "Back");
}

uint32_t view_menu()
{
    static uint32_t selection_index = 0;
    static uint32_t keys[3]      = { 0, 0, 0 },
            old_keys[3]     = { 0, 0, 0 };

    view_menu_init();
    printf("Available Cars:\n");
    for(uint32_t i = 0; i < num_cars; ++i)
    {
        printf("%d: %s, %s, %s, %s\n", 
            i, buffer_cars[i].brand, buffer_cars[i].type, buffer_cars[i].license_plate, buffer_cars[i].color);
    }
    printf("\nOptions:\n");
    for(uint32_t i = 0; i < 5; ++i)
    {
        if(selection_index == i)
            color(2);
        printf("%d: %s\n", i+1, view_menu_choices[i]);
        color(7);
    }

    while(1)
    {
        for(uint32_t i = 0; i < 3; ++i)
            old_keys[i] = keys[i];
        keys[0] = GetAsyncKeyState(VK_DOWN);
        keys[1] = GetAsyncKeyState(VK_UP);
        keys[2] = GetAsyncKeyState(VK_CONTROL);
        if(keys[0] && !old_keys[0])
        {
            if(selection_index == 4)
                selection_index = 0;
            else
                ++selection_index;
            return 1;
        }
        if(keys[1] && !old_keys[1])
        {
            if(selection_index == 0)
                selection_index = 4;
            else
                --selection_index;
            return 1;
        }
        if(keys[2] && !old_keys[2])
        {
            if(selection_index == 0)
            {
                buffer_cars = realloc_car(buffer_cars, num_cars, num_cars + 1);
                add_car(buffer_cars, num_cars);
                ++num_cars;
                return 1;
            }
            else if(selection_index == 1)
            {
                while(edit_menu());
                return 1;
            }
            else if(selection_index == 2)
            {
                while(search_menu());
                return 1;
            }
            else if(selection_index == 3)
            {
                while(remove_menu());
                return 1;
            }
            else
            {
                return 0;
            }
        }
        Sleep(10);
    }
}

void main_menu_init()
{
    system("cls");
    reset_input();
    static uint32_t initialized = 0;
    if(initialized)
        return;
    initialized = 1;
    my_strcpy(main_menu_choices[0], "View Vehicle");
    my_strcpy(main_menu_choices[1], "Exit");
}

uint32_t main_menu()
{
    static uint32_t selection_index = 0;
    static uint32_t keys[3]      = { 0, 0, 0 },
            old_keys[3]     = { 0, 0, 0 };

    main_menu_init();

    for(uint32_t i = 0; i < 2; ++i)
    {
        if(selection_index == i)
            color(2);
        printf("%d: %s\n", i+1, main_menu_choices[i]);
        color(7);
    }

    while(1)
    {
        for(uint32_t i = 0; i < 3; ++i)
            old_keys[i] = keys[i];
        keys[0] = GetAsyncKeyState(VK_DOWN);
        keys[1] = GetAsyncKeyState(VK_UP);
        keys[2] = GetAsyncKeyState(VK_CONTROL);
        if(keys[0] && !old_keys[0])
        {
            if(selection_index == 1)
                selection_index = 0;
            else
                ++selection_index;
            return 1;
        }
        if(keys[1] && !old_keys[1])
        {
            if(selection_index == 0)
                selection_index = 1;
            else
                --selection_index;
            return 1;
        }
        if(keys[2] && !old_keys[2])
        {
            if(selection_index == 0)
            {
                while(view_menu());
                return 1;
            }
            else if(selection_index == 1)
            {
                return 0;
            }
        }
        Sleep(10);
    }
}