#ifndef CAR_FLEET_CPP_COMMON_H
#define CAR_FLEET_CPP_COMMON_H

#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <windows.h>
#include <shellapi.h>

enum class ui_state : uint8_t
{
    MAIN_MENU,
    VIEW_MENU,
    ADD_MENU,
    REMOVE_MENU,
    SEARCH_MENU,
    DETAILED_MENU,
    EDIT_MENU,
    ABOUT_MENU
};

inline std::string itos(int conv)
{
    if(conv == 0)
        return "0";
    std::string ret;
    bool negative = false;
    if(conv < 0)
    {
        negative = true;
        conv = conv * -1;
    }
    while(conv != 0)
    {
        ret.insert(ret.begin(), 48 + conv % 10);
        conv /= 10;
    }
    if(negative)
        ret.insert(ret.begin(), '-');
    return ret;
}

#endif