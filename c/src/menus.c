#include "menus.h"

char main_menu_choices[2][13];
char view_menu_choices[5][20];

void view_menu_init()
{
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

    for(uint32_t i = 0; i < num_cars; ++i)
    {
        printf("%d: %s, %s, %s, %s\n", 
            i+1, buffer_cars[i].brand, buffer_cars[i].type, buffer_cars[i].license_plate, buffer_cars[i].color);
    }
    printf("\n");
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
                printf("Add Car\n");
            }
            else if(selection_index == 1)
            {
                printf("Edit Car\n");
            }
            else if(selection_index == 2)
            {
                printf("Search Car\n");
            }
            else if(selection_index == 3)
            {
                printf("Remove Car\n");
            }
            else
            {
                return 0;
            }
        }
    }
}

void main_menu_init()
{
    system("cls");
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
    }
}