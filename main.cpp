#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <array>
#include <cmath>
float mass =  100;
float gravity = -9.81;
float airDensity = 1.293;
float dragCoeff = 0.47;
float radius = 100;

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
    sf::RenderWindow window(sf::VideoMode(800, 600), "Falling Ball");
    sf::Clock clock;
    sf::CircleShape ball(25.f);
    float y = 0.f;
    float floor = 550.f;
    bool onGround = false;
    float time;

    std::array line =
    {
        sf::Vertex{sf::Vector2(0.f, floor)},
        sf::Vertex{sf::Vector2(800.f, floor)}
    };



    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        time = clock.getElapsedTime().asSeconds();

        //y += 0*clock.getElapsedTime().asSeconds() + (0.5f*gravity*pow(clock.getElapsedTime().asSeconds(),2));

        y -= yPosDrag(0, time);

        if(y+50.f >= floor){
            ball.setPosition(400.f-25.f,floor-50.f);
            //break;
        }
        else
        {
            ball.setPosition(400.f-25.f,0.f+y);
        }
        std::cout << y<< std::endl;
        window.clear();
        ball.setFillColor(sf::Color(255,255,255));

        window.draw(line.data(), line.size(), sf::PrimitiveType::Lines);
        window.draw(ball);
        window.display();

    }
    return 0;
}
