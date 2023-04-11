#ifndef CAR_FLEET_CPP_APPLICATION_H
#define CAR_FLEET_CPP_APPLICATION_H

#include "common.h"
#include "car.h"
#include "filemanager.h"
#include "menus.h"
struct Application
{
    public:
        Application(const char* filename);
        ~Application();

        void run();
        void list_cars(std::function<void(uint32_t)> buttonFunc);

    public:
        ui_state m_state;
        sf::RenderWindow m_window;
        std::vector<car> m_cars;
        FileManager m_filemanager;
        uint32_t m_selected_car;
        std::unordered_map<ui_state, base_menu*> m_menus;

        friend struct base_menu;
};

#endif