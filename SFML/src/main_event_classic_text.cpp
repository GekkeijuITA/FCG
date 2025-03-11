////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>

#include <vector>
#include <string>

std::string vec2ToString(const sf::Vector2i vec2)
{
    return '(' + std::to_string(vec2.x) + ", " + std::to_string(vec2.y) + ')';
}

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({800u, 600u}), "CMake SFML Project");
    std::vector<std::string> log;
    const sf::Font font{"../resources/tuffy.ttf"};
    sf::Text logText{font, "", 20};

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
                log.emplace_back("Key Pressed: " + sf::Keyboard::getDescription(keyPress->scancode));
            }
            else if (const auto *mouseMoved = event->getIf<sf::Event::MouseMoved>())
            {
                log.emplace_back("Mouse Moved: " + vec2ToString(mouseMoved->position));
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
                log.emplace_back("Mouse Pressed - " + sb);
            }
            else if (event->is<sf::Event::FocusGained>())
            {
                log.emplace_back("Focus gained");
            }
            else if (event->is<sf::Event::FocusLost>())
            {
                log.emplace_back("Focus lost");
            }
            else if (event->is<sf::Event::KeyReleased>())
            {
                log.emplace_back("Key released");
            }
            else if (event->is<sf::Event::MouseButtonReleased>())
            {
                log.emplace_back("Mouse released");
            }
            else if (event->is<sf::Event::MouseEntered>())
            {
                log.emplace_back("Mouse entered");
            }
            else if (event->is<sf::Event::MouseLeft>())
            {
                log.emplace_back("Mouse left");
            }
            else if (event->is<sf::Event::MouseWheelScrolled>())
            {
                log.emplace_back("Mouse wheel scrolled");
            }
            else if (event->is<sf::Event::Resized>())
            {
                log.emplace_back("Window resized");
            }
            else if (event->is<sf::Event::TextEntered>())
            {
                log.emplace_back("Text entered");
            }
            else
            {
                // All unhandled events will end up here
                log.emplace_back("Other Event");
            }

            // Show log
            if (log.size() > 24u) // Limit the log to 24 entries
                log.erase(log.begin(), log.begin() + static_cast<int>(log.size() - 24u));
            window.clear();
            for (std::size_t i = 0; i < log.size(); ++i)
            {
                logText.setPosition({50.f, static_cast<float>(i * 20) + 50.f});
                logText.setString(log[i]);
                window.draw(logText);
            }
            window.display();
        }
    }
}
