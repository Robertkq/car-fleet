#include "application.h"

Application::Application()
    : m_state(ui_state::MAIN_MENU), m_window(sf::VideoMode(800, 600), "SFML Imgui Menu Example")
{
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

        if(m_state == ui_state::MAIN_MENU)
        {
            show_main_menu();
        }

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
}

void Application::show_main_menu()
{
    ImGui::SetNextWindowSize({800, 600});
    ImGui::SetNextWindowPos({0, 0});
    ImGui::Begin("Main Menu");
    if(ImGui::Button("Press me!"))
    {
        std::cout << "I got pressed!\n";
    }
    ImGui::End();
}