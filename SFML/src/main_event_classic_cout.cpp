////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Window.hpp>

#include <vector>
#include <string>
#include <iostream>

std::string vec2ToString(const sf::Vector2i vec2)
{
    return '(' + std::to_string(vec2.x) + ", " + std::to_string(vec2.y) + ')';
}

int main()
{
    auto window = sf::Window(sf::VideoMode({800u, 600u}), "CMake SFML Project");

    while (window.isOpen())
    { // main loop
        while (const std::optional event = window.pollEvent())
        { // event loop + hevent handler
            if (event->is<sf::Event::Closed>())
            {
                window.close();
                break;
            }

            if (const auto *keyPress = event->getIf<sf::Event::KeyPressed>())
            {
                std::string s = sf::Keyboard::getDescription(keyPress->scancode);
                std::cout << "Key Pressed: " << s << std::endl;
            }
            else if (const auto *mouseMoved = event->getIf<sf::Event::MouseMoved>())
            {
                std::cout << "Mouse Moved: " << vec2ToString(mouseMoved->position) << std::endl;
            }
            else if (const auto *mouseButton = event->getIf<sf::Event::MouseButtonPressed>())
            {
                sf::Mouse::Button but = mouseButton->button;
                std::string sb;
                switch (but)
                {
                case sf::Mouse::Button::Left:
                    sb = "Left";
                    break;
                case sf::Mouse::Button::Right:
                    sb = "Right";
                    break;
                case sf::Mouse::Button::Middle:
                    sb = "Middle";
                    break;
                default:
                    sb = "Unknown";
                }
                std::cout << "Mouse Pressed - " << sb << std::endl;
            }
            else if (event->is<sf::Event::FocusGained>())
            {
                std::cout << "Focus gained" << std::endl;
            }
            else if (event->is<sf::Event::FocusLost>())
            {
                std::cout << "Focus lost" << std::endl;
            }
            else if (event->is<sf::Event::KeyReleased>())
            {
                std::cout << "Key released" << std::endl;
            }
            else if (event->is<sf::Event::MouseButtonReleased>())
            {
                std::cout << "Mouse button released" << std::endl;
            }
            else if (event->is<sf::Event::MouseEntered>())
            {
                std::cout << "Mouse entered" << std::endl;
            }
            else if (event->is<sf::Event::MouseLeft>())
            {
                std::cout << "Mouse left" << std::endl;
            }
            else if (event->is<sf::Event::MouseWheelScrolled>())
            {
                std::cout << "Mouse wheel scrolled" << std::endl;
            }
            else if (const auto *resized = event->getIf<sf::Event::Resized>())
            {
                sf::Vector2u s = resized->size;
                std::cout << "Window resized to: (" << s.x << ", " << s.y << ")" << std::endl;
            }
            else if (const auto *keypress = event->getIf<sf::Event::TextEntered>())
            {
                std::cout << "Text entered: " << keypress->unicode << std::endl;
            }
            else
            {
                // All unhandled events will end up here
                std::cout << "Other Event" << std::endl;
            }
        }
    }
}
