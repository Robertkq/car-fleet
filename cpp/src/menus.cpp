#include "menus.h"

#include "application.h"

base_menu::base_menu(Application* _parent)
    : parent(_parent) {}

base_menu::~base_menu() {}

main_menu::main_menu(Application* _parent)
    : base_menu(_parent) {}

void main_menu::show() const 
{
    ImGui::SetNextWindowSize({800, 600});
    ImGui::SetNextWindowPos({0, 0});
    ImGui::Begin("Main Menu");
    ImGui::SetCursorPosX(300);
    if(ImGui::Button("View all cars", ImVec2{200, 30}))
    {
        parent->m_state = ui_state::VIEW_MENU;
    }
    ImGui::SetCursorPosX(300);
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 100);
    if(ImGui::Button("Add a car", ImVec2{200, 30}))
    {
        parent->m_state = ui_state::ADD_MENU;
    }
    ImGui::SetCursorPosX(300);
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 100);
    if(ImGui::Button("Search for cars", ImVec2{200, 30}))
    {
        parent->m_state = ui_state::SEARCH_MENU;
    }
    ImGui::SetCursorPosX(300);
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 100);
    if(ImGui::Button("About", ImVec2{200, 30}))
    {
        parent->m_state = ui_state::ABOUT_MENU;
    }
    ImGui::SetCursorPosX(300);
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 100);
    if(ImGui::Button("Exit", ImVec2{200, 30}))
    {
        parent->m_filemanager.SaveToFile(parent->m_cars);
        exit(0);
    }

    ImGui::End();
}

view_menu::view_menu(Application* _parent)
    : base_menu(_parent) {}

void view_menu::show() const 
{
    ImGui::SetNextWindowSize({800, 600});
    ImGui::SetNextWindowPos({0, 0});
    ImGui::Begin("View Menu");
    parent->list_cars([this](uint32_t i){
        if(ImGui::Button((std::string("View More " + itos(i))).data()))
         {
            parent->m_selected_car = i;
            parent->m_state = ui_state::DETAILED_MENU;
         }
    });
    if(ImGui::Button("Go Back"))
    {
        parent->m_state = ui_state::MAIN_MENU;
    }
    ImGui::End();
}

add_menu::add_menu(Application* _parent)
    : base_menu(_parent) {}

void add_menu::show() const 
{
    static bool all_fields_needed;
    ImGui::SetNextWindowSize({800, 600});
    ImGui::SetNextWindowPos({0, 0});
    ImGui::Begin("Add menu");
    ImGuiInputTextFlags text_flags = ImGuiInputTextFlags_CharsNoBlank;
    ImGuiInputTextFlags number_flags = ImGuiInputTextFlags_CharsDecimal | ImGuiInputTextFlags_CharsNoBlank;
    static char add_brand_buff[100];
    ImGui::Text("Add Brand: "); ImGui::SameLine(); ImGui::InputText("##Add Brand", add_brand_buff, 100, text_flags);
    static char  add_type_buff[100];
    ImGui::Text("Add Type: "); ImGui::SameLine(); ImGui::InputText("##Add Type", add_type_buff, 100, text_flags);
    static char  add_license_plate_buff[100];
    ImGui::Text("Add License Plate: "); ImGui::SameLine(); ImGui::InputText("##Add License Plate", add_license_plate_buff, 100, text_flags);
    static char  add_color_buff[100];
    ImGui::Text("Add Color: "); ImGui::SameLine(); ImGui::InputText("##Add Color", add_color_buff, 100, text_flags);
    static int add_doors = 0;
    ImGui::Text("Add Doors: "); ImGui::SameLine(); ImGui::InputInt("##Add Doors", &add_doors, 1, 1, number_flags);
    static int add_year = 0;
    ImGui::Text("Add Year: "); ImGui::SameLine(); ImGui::InputInt("##Add Year", &add_year, 1, 1, number_flags);
    static int add_price = 0;
    ImGui::Text("Add Price: "); ImGui::SameLine(); ImGui::InputInt("##Add Price", &add_price, 50, 200, number_flags);
    static int add_km = -1;
    ImGui::Text("Add Kilometers: "); ImGui::SameLine(); ImGui::InputInt("##Add Kilometers", &add_km, 10, 100, number_flags);
    if(ImGui::Button("Go Back"))
    {
        parent->m_state = ui_state::MAIN_MENU;
    }
    if(ImGui::Button("Add"))
    {
        if(!std::string(add_brand_buff).empty() && !std::string(add_type_buff).empty() && !std::string(add_license_plate_buff).empty() && !std::string(add_color_buff).empty()
         && add_doors != 0 && add_year != 0 && add_price != 0 && add_km != -1)
         {
                parent->m_cars.push_back({add_brand_buff, add_type_buff, add_license_plate_buff, add_color_buff,
                 static_cast<uint32_t>(add_doors), static_cast<uint32_t>(add_year),
                  static_cast<uint32_t>(add_price), static_cast<uint32_t>(add_km)});
                parent->m_state = ui_state::MAIN_MENU;
                add_brand_buff[0] = '\0';
                add_type_buff[0] = '\0';
                add_license_plate_buff[0] = '\0';
                add_color_buff[0] = '\0';
                add_doors = 0;
                add_year = 0;
                add_price = 0;
                add_km = -1;
                all_fields_needed = false;
         }
         else
         {
            all_fields_needed = true;
         }
    }
    if(all_fields_needed)
    {
        ImGui::Text("All fields need to be completed!\n");
    }
    ImGui::End();
}

search_menu::search_menu(Application* _parent)
    : base_menu(_parent) {}

void search_menu::show() const 
{
    static bool show_results = false;
    ImGui::SetNextWindowSize({800, 600});
    ImGui::SetNextWindowPos({0, 0});
    ImGui::Begin("Search Menu");
    ImGuiInputTextFlags text_flags = ImGuiInputTextFlags_CharsNoBlank;
    ImGuiInputTextFlags number_flags = ImGuiInputTextFlags_CharsDecimal | ImGuiInputTextFlags_CharsNoBlank;
    static char search_brand_buff[100];
    static char search_type_buff[100];
    static char search_license_plate_buff[100];
    static char search_color_buff[100];
    static int search_doors = 0;
    static int search_year = 0;
    static int search_price = 0;
    static int search_km = -1;
    if(!show_results)
    {
        ImGui::Text("Search Brand: "); ImGui::SameLine(); ImGui::InputText("##Search Brand", search_brand_buff, 100, text_flags);
        ImGui::Text("Search Type: "); ImGui::SameLine(); ImGui::InputText("##Search Type", search_type_buff, 100, text_flags);
        ImGui::Text("Search License Plate: "); ImGui::SameLine(); ImGui::InputText("##Search License Plate", search_license_plate_buff, 100, text_flags);
        ImGui::Text("Search Color: "); ImGui::SameLine(); ImGui::InputText("##Search Color", search_color_buff, 100, text_flags);
        ImGui::Text("Search Doors: "); ImGui::SameLine(); ImGui::InputInt("##Search Doors", &search_doors, 1, 1, number_flags);
        ImGui::Text("Search Year: "); ImGui::SameLine(); ImGui::InputInt("##Search Year", &search_year, 1, 1, number_flags);
        ImGui::Text("Search Price: "); ImGui::SameLine(); ImGui::InputInt("##Search Price", &search_price, 50, 200, number_flags);
        ImGui::Text("Kilometers: "); ImGui::SameLine(); ImGui::InputInt("##Search Kilometers", &search_km, 10, 100, number_flags);
    }
    if(ImGui::Button("Go Back"))
    {
        parent->m_state = ui_state::MAIN_MENU;
    }
    if(ImGui::Button("Search"))
    {
        show_results = true;
    }
    if(show_results)
    {
        if(ImGui::Button("Reset"))
        {  
            search_brand_buff[0] = '\0';
            search_type_buff[0] = '\0';
            search_license_plate_buff[0] = '\0';
            search_color_buff[0] = '\0';
            search_doors = 0;
            search_year = 0;
            search_price = 0;
            search_km = -1;
            show_results = false;
        }
        static ImGuiTableFlags flags = ImGuiTableFlags_ScrollY | ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable;
        const float TEXT_BASE_HEIGHT = ImGui::GetTextLineHeightWithSpacing();
        ImVec2 outer_size = ImVec2(0.0f, TEXT_BASE_HEIGHT * 8);
        ImGui::BeginTable("list_cars", 6, flags, outer_size);
        ImGui::TableSetupScrollFreeze(0, 1); // Make top row always visible
        ImGui::TableSetupColumn("Index", ImGuiTableColumnFlags_None);
        ImGui::TableSetupColumn("Brand", ImGuiTableColumnFlags_None);
        ImGui::TableSetupColumn("Type", ImGuiTableColumnFlags_None);
        ImGui::TableSetupColumn("License Plate", ImGuiTableColumnFlags_None);
        ImGui::TableSetupColumn("Color", ImGuiTableColumnFlags_None);
        ImGui::TableSetupColumn("", ImGuiTableColumnFlags_None);
        ImGui::TableHeadersRow();
        
        for(uint32_t i = 0; i < parent->m_cars.size(); ++i)
        {
            if(std::string(search_brand_buff) == parent->m_cars[i].m_brand || search_brand_buff[0] == '\0')
            {
                if(std::string(search_type_buff) == parent->m_cars[i].m_type || search_type_buff[0] == '\0')
                {
                    if(std::string(search_license_plate_buff) == parent->m_cars[i].m_license_plate || search_license_plate_buff[0] == '\0')
                    {
                        if(std::string(search_color_buff) == parent->m_cars[i].m_color || search_color_buff[0] == '\0')
                        {
                            if(search_doors == parent->m_cars[i].m_doors || search_doors == 0)
                            {
                                if(search_year == parent->m_cars[i].m_year || search_year == 0)
                                {
                                    if(search_price == parent->m_cars[i].m_price || search_price == 0)
                                    {
                                        if(search_km == parent->m_cars[i].m_km || search_km == -1)
                                        {
                                            ImGui::TableNextRow();
                                            ImGui::TableSetColumnIndex(0);
                                            ImGui::Text(itos(i).data());
                                            ImGui::TableSetColumnIndex(1);
                                            ImGui::Text(parent->m_cars[i].m_brand.data());
                                            ImGui::TableSetColumnIndex(2);
                                            ImGui::Text(parent->m_cars[i].m_type.data());
                                            ImGui::TableSetColumnIndex(3);
                                            ImGui::Text(parent->m_cars[i].m_license_plate.data());
                                            ImGui::TableSetColumnIndex(4);
                                            ImGui::Text(parent->m_cars[i].m_color.data());
                                            ImGui::TableSetColumnIndex(5);
                                            if(ImGui::Button((std::string("View More ") + itos(i)).data()))
                                            {
                                                parent->m_selected_car = i;
                                                parent->m_state = ui_state::DETAILED_MENU;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        ImGui::EndTable();
    }
    ImGui::End();
}

detailed_menu::detailed_menu(Application* _parent)
    : base_menu(_parent) {}

void detailed_menu::show() const 
{
    static bool confirm = false;
    ImGui::SetNextWindowSize({800, 600});
    ImGui::SetNextWindowPos({0, 0});
    ImGui::Begin("Detailed menu");
    parent->m_cars[parent->m_selected_car].print_detailed();
    if(ImGui::Button("Go Back"))
    {
        parent->m_state = ui_state::VIEW_MENU;
        confirm = false;
    }
    ImGui::SameLine();
    if(ImGui::Button("Edit"))
    {
        parent->m_state = ui_state::EDIT_MENU;
    }
    ImGui::SameLine();
    if(ImGui::Button("Remove"))
    {
        confirm = true;
    }
    if(confirm)
    {
        ImGui::Text("Are you sure you want to remove this car?");
        ImGui::SameLine();
        if(ImGui::Button("Yes"))
        {
            parent->m_cars.erase(parent->m_cars.begin() + parent->m_selected_car);
            parent->m_state = ui_state::VIEW_MENU;
        }
        ImGui::SameLine();
        if(ImGui::Button("No"))
        {
            confirm = false;
        }
    }
    ImGui::End();
}

edit_menu::edit_menu(Application* _parent)
    : base_menu(_parent) {}

void edit_menu::show() const 
{
    ImGui::SetNextWindowSize({800, 600});
    ImGui::SetNextWindowPos({0, 0});
    ImGui::Begin("Edit menu");
    parent->m_cars[parent->m_selected_car].print_detailed();
    ImGuiInputTextFlags text_flags = ImGuiInputTextFlags_CharsNoBlank;
    ImGuiInputTextFlags number_flags = ImGuiInputTextFlags_CharsDecimal | ImGuiInputTextFlags_CharsNoBlank;
    static char new_brand_buff[100];
    ImGui::Text("New Brand: "); ImGui::SameLine(); ImGui::InputText("##New Brand", new_brand_buff, 100, text_flags);
    static char new_type_buff[100];
    ImGui::Text("New Type: "); ImGui::SameLine(); ImGui::InputText("##New Type", new_type_buff, 100, text_flags);
    static char new_license_plate_buff[100];
    ImGui::Text("New License Plate: "); ImGui::SameLine(); ImGui::InputText("##New License Plate", new_license_plate_buff, 100, text_flags);
    static char new_color_buff[100];
    ImGui::Text("New Color: "); ImGui::SameLine(); ImGui::InputText("##New Color", new_color_buff, 100, text_flags);
    static int new_doors = 0;
    ImGui::Text("New Doors: "); ImGui::SameLine(); ImGui::InputInt("##New Doors", &new_doors, 1, 1, number_flags);
    static int new_year = 0;
    ImGui::Text("New Year: "); ImGui::SameLine(); ImGui::InputInt("##New Year", &new_year, 1, 1, number_flags);
    static int new_price = 0;
    ImGui::Text("New Price: "); ImGui::SameLine(); ImGui::InputInt("##New Price", &new_price, 50, 200, number_flags);
    static int new_km = 0;
    ImGui::Text("New Kilometers: "); ImGui::SameLine(); ImGui::InputInt("##New Kilometers", &new_km, 10, 100, number_flags);
    if(ImGui::Button("Go Back"))
    {
        parent->m_state = ui_state::DETAILED_MENU;
    }
    if(ImGui::Button("Save"))
    {
        if(new_brand_buff[0] != '\0')
        {
            parent->m_cars[parent->m_selected_car].m_brand = new_brand_buff;
            new_brand_buff[0] = '\0';
        }
        if(new_type_buff[0] != '\0')
        {
            parent->m_cars[parent->m_selected_car].m_type = new_type_buff;
            new_type_buff[0] = '\0';
        }
        if(new_license_plate_buff[0] != '\0')
        {
            parent->m_cars[parent->m_selected_car].m_license_plate = new_license_plate_buff;
            new_license_plate_buff[0] = '\0';
        }
        if(new_color_buff[0] != '\0')
        {
            parent->m_cars[parent->m_selected_car].m_color = new_color_buff;
            new_color_buff[0] = '\0';
        }
        if(new_doors != 0)
        {
            parent->m_cars[parent->m_selected_car].m_doors = new_doors;
            new_doors = 0;
        }
        if(new_year != 0)
        {
            parent->m_cars[parent->m_selected_car].m_year = new_year;
            new_year = 0;
        }
        if(new_price != 0)
        {
            parent->m_cars[parent->m_selected_car].m_price = new_price;
            new_price = 0;
        }
        if(new_km != 0)
        {
            parent->m_cars[parent->m_selected_car].m_km = new_km;
            new_km = 0;
        }
    }
    ImGui::End();
}

about_menu::about_menu(Application* _parent)
    : base_menu(_parent) {}

void about_menu::show() const 
{
    static sf::Texture catto;
    static int initialized = 0;
    if(!initialized)
    {
        initialized = 1;
        catto.loadFromFile("catto.jpg");
    }
    

    ImGui::SetNextWindowSize({800, 600});
    ImGui::SetNextWindowPos({0, 0});
    ImGui::Begin("About Menu");
    ImGui::SetCursorPosX(400);
    ImGui::SetCursorPosY(150);
    if(ImGui::Button("GitHub"))
    {
        ShellExecute(0, 0, "https://github.com/Robertkq/car-fleet", 0, 0 , SW_SHOW );
    }
    ImGui::SetCursorPosX(200);
    ImGui::Image(catto, {400, 300});
    
    ImGui::SetCursorPosX(400);
    if(ImGui::Button("Go Back"))
    {
        parent->m_state = ui_state::MAIN_MENU;
    }
    ImGui::End();
}
