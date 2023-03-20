#ifndef COMMON_H
#define COMMON_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <stdint.h>
#include "car.h"

extern uint32_t num_cars;
extern car_t* buffer_cars;

inline void color(int k)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), k);
}

inline void my_strcpy(char* dest, const char* src)
{
    while(*src != '\0')
    {
        *(dest++) = *(src++);
    }
    *dest = *src;
}

inline void reset_input()
{
    while(GetAsyncKeyState(VK_DOWN) ||
    GetAsyncKeyState(VK_UP) ||
    GetAsyncKeyState(VK_CONTROL) )
    {
        Sleep(10);
    }
}

#endif