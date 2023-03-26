#ifndef CAR_FLEET_CPP_APPLICATION_H
#define CAR_FLEET_CPP_APPLICATION_H

#include "common.h"

struct Application
{
    public:
        Application();
        ~Application();
        void run();
        void show_main_menu();
    private:
        ui_state m_state;
        sf::RenderWindow m_window;
};

#endif