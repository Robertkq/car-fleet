#include "application.h"



Application::Application()
    : m_state(ui_state::MAIN_MENU), m_window(sf::VideoMode(800, 600), "Car Fleet (C++)"),
        m_cars(), m_filemanager("cars.txt")
{
    m_filemanager.LoadFromFile(m_cars);
    bool result = ImGui::SFML::Init(m_window);
}

void Application::run()
{
    // Run the main loop
    while(m_window.isOpen())
    {
        // Handle SFML events
        sf::Event event;
        while(m_window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            if(event.type == sf::Event::Closed)
                m_window.close();
        }

        // Start Imgui frame
        ImGui::SFML::Update(m_window, sf::seconds(1.0f / 60.0f));

        show_current_menu();

        ImGui::ShowDemoWindow();
        
        // Clear the window
        m_window.clear(sf::Color::White);

        // Draw Imgui
        ImGui::SFML::Render(m_window);

        // Display the window
        m_window.display();
    }
    
}

Application::~Application()
{
    ImGui::SFML::Shutdown();
    m_filemanager.SaveToFile(m_cars);
}

void Application::show_current_menu()
{
    if(m_state == ui_state::MAIN_MENU)
    {
        show_main_menu();
    }
    else if(m_state == ui_state::VIEW_MENU)
    {
        show_view_menu();
    }
    else if(m_state == ui_state::DETAILED_MENU)
    {
        show_detailed_menu();
    }
    else if(m_state == ui_state::EDIT_MENU)
    {
        show_edit_menu();
    }
    else if(m_state == ui_state::SERACH_MENU)
    {
        show_search_menu();
    }
}

void  Application::show_edit_menu()
{
    ImGui::SetNextWindowSize({800, 600});
    ImGui::SetNextWindowPos({0, 0});
    ImGui::Begin("Edit menu");
    m_cars[m_selected_car].print_detailed();
    ImGuiInputTextFlags text_flags = ImGuiInputTextFlags_CharsNoBlank;
    ImGuiInputTextFlags number_flags = ImGuiInputTextFlags_CharsDecimal | ImGuiInputTextFlags_CharsNoBlank;
    static char new_brand_buff[100] = {};
    ImGui::Text("New Brand: "); ImGui::SameLine(); ImGui::InputText("##New Brand", new_brand_buff, 100, text_flags);
    static char new_type_buff[100] = {};
    ImGui::Text("New Type: "); ImGui::SameLine(); ImGui::InputText("##New Type", new_type_buff, 100, text_flags);
    static char new_license_plate_buff[100] = {};
    ImGui::Text("New License Plate: "); ImGui::SameLine(); ImGui::InputText("##New License Plate", new_license_plate_buff, 100, text_flags);
    static char new_color_buff[100] = {};
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
        m_state = ui_state::DETAILED_MENU;
    }
    if(ImGui::Button("Save"))
    {
        
        std::cout << new_brand_buff << '\n' << new_type_buff << '\n' << new_license_plate_buff << '\n' << new_color_buff << '\n'
            << new_doors << '\n';
        if(new_brand_buff[0] != '\0')
        {
            m_cars[m_selected_car].m_brand = new_brand_buff;
            new_brand_buff[0] = '\0';
        }
        if(new_type_buff[0] != '\0')
        {
            m_cars[m_selected_car].m_type = new_type_buff;
            new_type_buff[0] = '\0';
        }
        if(new_license_plate_buff[0] != '\0')
        {
            m_cars[m_selected_car].m_license_plate = new_license_plate_buff;
            new_license_plate_buff[0] = '\0';
        }
        if(new_color_buff[0] != '\0')
        {
            m_cars[m_selected_car].m_color = new_color_buff;
            new_color_buff[0] = '\0';
        }
        if(new_doors != 0)
        {
            m_cars[m_selected_car].m_doors = new_doors;
            new_doors = 0;
        }
        if(new_year != 0)
        {
            m_cars[m_selected_car].m_year = new_year;
            new_year = 0;
        }
        if(new_price != 0)
        {
            m_cars[m_selected_car].m_price = new_price;
            new_price = 0;
        }
        if(new_km != 0)
        {
            m_cars[m_selected_car].m_km = new_km;
            new_km = 0;
        }
    }
    ImGui::End();
}

template<typename ButtonFuncType>
void Application::list_cars(ButtonFuncType buttonFunc)
{
    static ImGuiTableFlags flags = ImGuiTableFlags_ScrollY | ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable;
    const float TEXT_BASE_HEIGHT = ImGui::GetTextLineHeightWithSpacing();
    ImVec2 outer_size = ImVec2(0.0f, TEXT_BASE_HEIGHT * 8);
    if (ImGui::BeginTable("list_cars", 6, flags, outer_size))
        {
            ImGui::TableSetupScrollFreeze(0, 1); // Make top row always visible
            ImGui::TableSetupColumn("Index", ImGuiTableColumnFlags_None);
            ImGui::TableSetupColumn("Brand", ImGuiTableColumnFlags_None);
            ImGui::TableSetupColumn("Type", ImGuiTableColumnFlags_None);
            ImGui::TableSetupColumn("License Plate", ImGuiTableColumnFlags_None);
            ImGui::TableSetupColumn("Color", ImGuiTableColumnFlags_None);
            ImGui::TableSetupColumn("", ImGuiTableColumnFlags_None);
            ImGui::TableHeadersRow();

            for (uint32_t i = 0; i < m_cars.size(); ++i)
            {
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::Text(itos(i).data());
                ImGui::TableSetColumnIndex(1);
                ImGui::Text(m_cars[i].m_brand.data());
                ImGui::TableSetColumnIndex(2);
                ImGui::Text(m_cars[i].m_type.data());
                ImGui::TableSetColumnIndex(3);
                ImGui::Text(m_cars[i].m_license_plate.data());
                ImGui::TableSetColumnIndex(4);
                ImGui::Text(m_cars[i].m_color.data());
                ImGui::TableSetColumnIndex(5);
                buttonFunc(i);
            }
            
            ImGui::EndTable();
        }
}

void Application::show_main_menu()
{
    ImGui::SetNextWindowSize({800, 600});
    ImGui::SetNextWindowPos({0, 0});
    ImGui::Begin("Main Menu");
    ImGui::SetCursorPosX(300);
    if(ImGui::Button("View all cars", ImVec2{200, 30}))
    {
        m_state = ui_state::VIEW_MENU;
    }
    ImGui::SetCursorPosX(300);
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 100);
    if(ImGui::Button("Add a car", ImVec2{200, 30}))
    {
        m_state = ui_state::ADD_MENU;
    }
    ImGui::SetCursorPosX(300);
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 100);
    if(ImGui::Button("Search for cars", ImVec2{200, 30}))
    {
        m_state = ui_state::SEARCH_MENU;
    }
    ImGui::SetCursorPosX(300);
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 100);
    if(ImGui::Button("Exit", ImVec2{200, 30}))
    {
        // save file info
        exit(0);
    }

    ImGui::End();
}

void Application::show_view_menu()
{
    ImGui::SetNextWindowSize({800, 600});
    ImGui::SetNextWindowPos({0, 0});
    ImGui::Begin("View Menu");
    list_cars([this](uint32_t i)
    {
        if(ImGui::Button((std::string("View More " + itos(i))).data()))
        {
            m_selected_car = i;
            m_state = ui_state::DETAILED_MENU;
        }
    });
    if(ImGui::Button("Go Back"))
    {
        m_state = ui_state::MAIN_MENU;
    }
    ImGui::End();
}

void Application::show_detailed_menu()
{
    ImGui::SetNextWindowSize({800, 600});
    ImGui::SetNextWindowPos({0, 0});
    ImGui::Begin("Detailed menu");
    m_cars[m_selected_car].print_detailed();
    if(ImGui::Button("Go Back"))
    {
        m_state = ui_state::VIEW_MENU;
    }
    ImGui::SameLine();
    if(ImGui::Button("Edit"))
    {
        m_state = ui_state::EDIT_MENU;
    }
    ImGui::SameLine();
    static bool confirm = false;
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
            std::cout << "Remove car " << m_selected_car << "\n";
        }
        ImGui::SameLine();
        if(ImGui::Button("No"))
        {
            confirm = false;
        }
    }
    ImGui::End();
}