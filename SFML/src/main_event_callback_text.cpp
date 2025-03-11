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

////////////////////////////////////////////////////////////
/// Stato della GUI
struct State
{
    sf::RenderWindow window;
    std::vector<std::string> log;
    const sf::Font font{"../resources/tuffy.ttf"};

    State(unsigned w, unsigned h, std::string title)
    {
        window = sf::RenderWindow(sf::VideoMode({w, h}), title);
    }
};

// State gs;

///
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
/// Funzioni callback
void handle(const sf::Event::Closed &, State &gs)
{
    gs.window.close();
}

void handle(const sf::Event::KeyPressed &keyPress, State &gs)
{
    gs.log.emplace_back("Key Pressed: " + sf::Keyboard::getDescription(keyPress.scancode));
}

void handle(const sf::Event::MouseMoved &mouseMoved, State &gs)
{
    gs.log.emplace_back("Mouse Moved: " + vec2ToString(mouseMoved.position));
}

void handle(const sf::Event::MouseButtonPressed &, State &gs)
{
    gs.log.emplace_back("Mouse Pressed");
}

void handle(const sf::Event::Resized &resized, State &gs)
{
    sf::FloatRect visibleArea({0.f, 0.f}, sf::Vector2f(resized.size));
    gs.window.setView(sf::View(visibleArea));
    gs.log.emplace_back("Window resized");
}

template <typename T>
void handle(const T &, State &gs)
{
    // All unhandled events will end up here
    gs.log.emplace_back("Other Event");
}
///
////////////////////////////////////////////////////////////

int main()
{
    State gs(800, 600, "CMake SFML Project");
    sf::Text logText{gs.font, "", 20};
    while (gs.window.isOpen()) // main loop
    {
        // event loop and handler through callbacks
        gs.window.handleEvents([&](const auto &event)
                               { handle(event, gs); });

        // Show log
        gs.window.clear();
        if (gs.log.size() > 24u) // Limit the log to 24 entries
            gs.log.erase(gs.log.begin(), gs.log.begin() + static_cast<int>(gs.log.size() - 24u));
        for (std::size_t i = 0; i < gs.log.size(); ++i)
        {
            logText.setPosition({50.f, static_cast<float>(i * 20) + 50.f});
            logText.setString(gs.log[i]);
            gs.window.draw(logText);
        }
        gs.window.display();
    }
}
