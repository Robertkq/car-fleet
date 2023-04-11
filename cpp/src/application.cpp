#include "application.h"

Application::Application(const char* filename)
    : m_state(ui_state::MAIN_MENU), m_window(sf::VideoMode(800, 600), "Car Fleet (C++)"),
        m_cars(), m_filemanager(filename), m_selected_car(0), m_menus({
             {ui_state::MAIN_MENU, new main_menu(this)},
             {ui_state::VIEW_MENU, new view_menu(this)},
             {ui_state::ADD_MENU, new add_menu(this)},
             {ui_state::SEARCH_MENU, new search_menu(this)},
             {ui_state::DETAILED_MENU, new detailed_menu(this)},
             {ui_state::EDIT_MENU, new edit_menu(this)},
             {ui_state::ABOUT_MENU, new about_menu(this)}
             })
{
    m_filemanager.LoadFromFile(m_cars);
    bool result = ImGui::SFML::Init(m_window);
}

Application::~Application()
{
    for(auto it = m_menus.begin(); it != m_menus.end(); ++it)
    {
        delete it->second;
    }
    ImGui::SFML::Shutdown();
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

        m_menus[m_state]->show();
        
        // Clear the window
        m_window.clear(sf::Color::White);

        // Draw Imgui
        ImGui::SFML::Render(m_window);

        // Display the window
        m_window.display();
    }
    
}

void Application::list_cars(std::function<void(uint32_t)> buttonFunc)
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
