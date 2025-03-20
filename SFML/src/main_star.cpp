////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>

#include <vector>
#include <string>
#include <math.h>
#include <iostream>

sf::ConvexShape star(float R, float r)
{
    const float PI = 3.14159265359;
    sf::ConvexShape c(10);
    c.setPoint(0, {0, R});
    c.setPoint(1, {r * cos(7 * PI / 10), r * sin(7 * PI / 10)});
    c.setPoint(2, {R * cos(9 * PI / 10), R * sin(9 * PI / 10)});
    c.setPoint(3, {r * cos(11 * PI / 10), r * sin(11 * PI / 10)});
    c.setPoint(4, {R * cos(13 * PI / 10), R * sin(13 * PI / 10)});
    c.setPoint(5, {0, -r});
    c.setPoint(6, {R * cos(17 * PI / 10), R * sin(17 * PI / 10)});
    c.setPoint(7, {r * cos(19 * PI / 10), r * sin(19 * PI / 10)});
    c.setPoint(8, {R * cos(PI / 10), R * sin(PI / 10)});
    c.setPoint(9, {r * cos(3 * PI / 10), r * sin(3 * PI / 10)});
    return c;
}

sf::ConvexShape star(float R, float r, int p) {
    const float PI = 3.14159265359;
    const int points = p*2;
    
    sf::ConvexShape c(points);

    for(int i = 0; i < points; i++) {
        float pos_x, pos_y;
        int angle = i*2+5;

        if(i%2 == 0) {
            pos_x = R * cos(angle * PI / points);
            pos_y = R * sin(angle * PI / points);
        } else {
            pos_x = r * cos(angle * PI / points);
            pos_y = r * sin(angle * PI / points);
        }

        c.setPoint(i,{pos_x, pos_y});
    }
    return c;
}

int main()
{
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;
    auto window = sf::RenderWindow(sf::VideoMode({800u, 600u}), "CMake SFML Project", sf::Style::Default, sf::State::Windowed, settings);
    // window.setFramerateLimit(30);

    while (window.isOpen()) // main loop
    {
        while (const std::optional event = window.pollEvent())
        { // event loop + hevent handler
            if (event->is<sf::Event::Closed>())
            {
                window.close();
                break;
            }
        }
        // Do graphics
        window.clear();

        float sqrt32 = sqrt(3.f) / 2.f;
        sf::ConvexShape s = star(100.f, 40.f, 20);
        s.setFillColor(sf::Color::Green);
        s.rotate(sf::degrees(180));
        s.setScale({2.f, 2.f});
        s.setPosition({400.f, 300.f});
        // std::cout << "BBox: (" << s.getGlobalBounds().position.x << ", "
        //           << s.getGlobalBounds().position.y << ", "
        //           << s.getGlobalBounds().size.x << ", "
        //           << s.getGlobalBounds().size.y << ")\n";
        window.draw(s);
        window.display();
    }
}
