#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <array>
#include <cmath>
#include "imgui.h"
#include "imgui-SFML.h"
static_assert(SFML_VERSION_MAJOR == 3, "Requires SFML 3.0");
float mass =  1;
float gravity = -9.81;
float airDensity = 1.293;
float dragCoeff = 0.47;
float radius = 25.f;
static bool showDemoWindow = true;
float terminalV()
{
    float crossSection = M_PI * pow(radius, 2);
    float v = sqrt((2*mass*fabs(gravity)) / (airDensity*dragCoeff*crossSection));
    return v;
}

float yPosDrag(float startPos, float time)
{
    float y = startPos - ((pow(terminalV(),2)/fabs(gravity)) * log(cosh((gravity*time)/terminalV())));
    return y;
}

int main() {

    sf::RenderWindow window(sf::VideoMode({800, 600}), "Window Title");
    sf::Clock clock;
    sf::CircleShape ball(radius);
    ImGui::SFML::Init(window);
    float y = 0.f;
    float floor = 550.f;
    float time;

    std::array line =
    {
        sf::Vertex{sf::Vector2(0.f, floor)},
        sf::Vertex{sf::Vector2(800.f, floor)}
    };



    while (window.isOpen()) {
        //sf::Event event{};
        sf::Clock delta;
        while (const std::optional event = window.pollEvent())
        {
            ImGui::SFML::ProcessEvent(window, *event);
            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        ImGui::SFML::Update(window, delta.restart());

        ImGui::ShowDemoWindow(&showDemoWindow);

        ImGui::Begin("Hello, world!");
        ImGui::Button("I'm a button...");
        ImGui::End();

        time = clock.getElapsedTime().asSeconds();

        //y += 0*clock.getElapsedTime().asSeconds() + (0.5f*gravity*pow(clock.getElapsedTime().asSeconds(),2));

        y -= yPosDrag(0, time);

        if(y+2*radius >= floor){

            ball.setPosition(sf::Vector2f(400.f-radius, floor-2*radius));
            //break;
        }
        else
        {
            ball.setPosition(sf::Vector2f(400.f-radius,0.f+y));
        }
        std::cout << y<< std::endl;
        window.clear();
        ball.setFillColor(sf::Color(255,255,255));

        window.draw(line.data(), line.size(), sf::PrimitiveType::Lines);
        window.draw(ball);
        ImGui::SFML::Render(window);
        window.display();

    }
    ImGui::SFML::Shutdown();
    return 0;
}
