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

////////////////////////////////////////////////////////////
/// Funzioni callback
void handle(const sf::Event::Closed &, sf::Window &window)
{
    window.close();
}

void handle(const sf::Event::KeyPressed &keyPress, sf::Window &window)
{
    std::string s = sf::Keyboard::getDescription(keyPress.scancode);
    std::cout << "Key Pressed: " + s << std::endl;
}

void handle(const sf::Event::MouseMoved &mouseMoved, sf::Window &window)
{
    std::cout << "Mouse Moved: " + vec2ToString(mouseMoved.position) << std::endl;
}

void handle(const sf::Event::MouseButtonPressed &but, sf::Window &window)
{
    std::string sb;
    switch (but.button)
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

void handle(const sf::Event::FocusGained &, sf::Window &window)
{
    std::cout << "Focus gained" << std::endl;
}

void handle(const sf::Event::FocusLost &, sf::Window &window)
{
    std::cout << "Focus lost" << std::endl;
}

void handle(const sf::Event::KeyReleased &, sf::Window &window)
{
    std::cout << "Key released" << std::endl;
}

void handle(const sf::Event::MouseButtonReleased &, sf::Window &window)
{
    std::cout << "Mouse button released" << std::endl;
}

void handle(const sf::Event::MouseEntered &, sf::Window &window)
{
    std::cout << "Mouse bentered" << std::endl;
}

void handle(const sf::Event::MouseLeft &, sf::Window &window)
{
    std::cout << "Mouse left" << std::endl;
}

void handle(const sf::Event::MouseWheelScrolled &, sf::Window &window)
{
    std::cout << "Mouse wheel scrolled" << std::endl;
}

void handle(const sf::Event::Resized &resized, sf::Window &window)
{
    sf::Vector2u s = resized.size;
    std::cout << "Window resized to: (" << s.x << ", " << s.y << ")" << std::endl;
}

template <typename T>
void handle(const T &, sf::Window &window)
{
    // All unhandled events will end up here
    std::cout << "Other Event" << std::endl;
}
///
////////////////////////////////////////////////////////////

int main()
{
    auto window = sf::Window(sf::VideoMode({800u, 600u}), "CMake SFML Project");
    while (window.isOpen()) // main loop
    {
        // event loop and handler through callbacks
        window.handleEvents([&](const auto &event)
                            { handle(event, window); });
    }
}
