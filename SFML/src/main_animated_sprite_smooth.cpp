#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include <vector>
#include <string>
#include <math.h>
#include <iostream>

int main()
{
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;
    auto window = sf::RenderWindow(sf::VideoMode({800u, 600u}), "CMake SFML Project", sf::Style::Default, sf::State::Windowed, settings);
    window.setFramerateLimit(50);
    sf::Texture texture("../resources/SpaceInvaders.png");
    sf::Vector2f pos({0.f, 0.f});
    int sign = 1;
    float move_speed = 100.0;  // pixels/sec
    float swap_interval = 0.4; // sec
    bool alternate_step = true;

    sf::Sprite sprite(texture);
    sprite.setTextureRect(sf::IntRect({5, 1}, {8, 8}));
    sprite.scale({10.f, 10.f});
    sprite.setColor(sf::Color::Red);
    sprite.setPosition(pos);

    bool first_frame;
    sf::Clock move_clock;
    sf::Clock swap_clock;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            // event loop + event handler
            if (event->is<sf::Event::Closed>())
            {
                window.close();
                break;
            }
        }

        // Do graphics
        window.clear();

        if (!first_frame)
        {
            if (swap_clock.getElapsedTime().asSeconds() > swap_interval)
            {
                swap_clock.restart();
                alternate_step = !alternate_step;
                if (alternate_step)
                    sprite.setTextureRect(sf::IntRect({5, 1}, {8, 8}));
                else
                    sprite.setTextureRect(sf::IntRect({5, 11}, {8, 8}));
            }

            if ((pos.x >= window.getSize().x - 80 && sign == 1) || (pos.x <= 0 && sign == -1))
            {
                pos += {0.f, 30.f};
                sign = -sign;
            }
            else
            {
                double step = move_speed * move_clock.restart().asSeconds();
                pos.x += step * sign;
            }
        }

        sprite.setPosition(pos);
        window.draw(sprite);
        window.display();

        first_frame = false;
    }
}
