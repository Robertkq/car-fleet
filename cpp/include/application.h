#ifndef CAR_FLEET_CPP_APPLICATION_H
#define CAR_FLEET_CPP_APPLICATION_H

#include "common.h"
#include "car.h"
#include "filemanager.h"

struct Application
{
    public:
        Application();
        ~Application();
        void run();
        
    private:
        void show_current_menu();
        void show_main_menu();
        void show_view_menu();
        void show_detailed_menu();
        void show_edit_menu();
        void show_search_menu();
        void show_about_menu();
        void show_add_menu();

        template<typename ButtonFuncType>
        void list_cars(ButtonFuncType buttonFunc);
    
    private:
        ui_state m_state;
        sf::RenderWindow m_window;
        std::vector<car> m_cars;
        FileManager m_filemanager;
        uint32_t m_selected_car;
};

#endif