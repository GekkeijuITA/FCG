////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>

#include <vector>
#include <string>

////////////////////////////////////////////////////////////
/// GUI State
const int FONT_SIZE = 20;
const int FONT_WIDTH = 14;
const std::string FONT_NAME = "../resources/DejavuSansMono-5m7L.ttf";

struct State
{
    // General resources
    sf::RenderWindow window;
    const sf::Font font{FONT_NAME};
    // Text buffer
    std::vector<std::string> log;
    sf::IntRect text_view;
    sf::Vector2i cursor_pos;

    State(unsigned w, unsigned h, std::string title)
    {
        window = sf::RenderWindow(sf::VideoMode({w, h}), title);
        // window.setVerticalSyncEnabled(true); // alternative to setFramerateLimit
        window.setFramerateLimit(60);
        log.resize(1, "");
        text_view = {
            {0,0}, {
                static_cast<int>(w / FONT_WIDTH - 2), 
                static_cast<int>(h / FONT_SIZE - 2)
            }
        };
        cursor_pos = {0, 0};
    }

    void adjustView() {
        text_view.size = {
            static_cast<int>(window.getSize().x / FONT_WIDTH - 2),
            static_cast<int>(window.getSize().y / FONT_SIZE - 2)
        };

        text_view.position.x = std::min(text_view.position.x, cursor_pos.x);
        text_view.position.x = std::max(text_view.position.x, cursor_pos.x - text_view.size.x + 1);

        text_view.position.y = std::min(text_view.position.y, cursor_pos.y);
        text_view.position.y = std::max(text_view.position.y, cursor_pos.y - text_view.size.y + 1);
    }
};
///
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
/// Callback functions
void handle(const sf::Event::Closed &, State &gs)
{
    gs.window.close();
}

void handle(const sf::Event::TextEntered &textEnter, State &gs)
{
    unsigned last = gs.log.size() - 1;
    // if (textEnter.unicode == 10 || textEnter.unicode == 13)
    if (textEnter.unicode == '\n' || textEnter.unicode == '\r') { // enter
        gs.log.emplace_back("");
        gs.cursor_pos = {0, gs.cursor_pos.y + 1};
    }
    else if (textEnter.unicode >= ' ' && textEnter.unicode <= '~') { // printable char
        gs.log[last] += static_cast<char>(textEnter.unicode);
        gs.cursor_pos.x++;
    }
    gs.adjustView();
}

// void handle(const sf::Event::KeyPressed &keyPressed, State &gs)
// {
// }

// void handle(const sf::Event::MouseMoved &mouseMoved, State &gs)
// {
// }

// void handle(const sf::Event::MouseButtonPressed &, State &gs)
// {
// }

void handle(const sf::Event::Resized &resized, State &gs)
{
    sf::FloatRect visibleArea({0.f, 0.f}, sf::Vector2f(resized.size));
    gs.window.setView(sf::View(visibleArea));
    gs.adjustView();
}

template <typename T>
void handle(const T &, State &gs)
{
    // All unhandled events will end up here
}
///
////////////////////////////////////////////////////////////

void doGraphics(State &gs)
{
    sf::Text logText{gs.font, "", FONT_SIZE};
    // Show log
    gs.window.clear();

    unsigned lines_to_print = std::min(
        static_cast<unsigned>(gs.log.size() - gs.text_view.position.y), 
        static_cast<unsigned>(gs.text_view.size.y));

    for (std::size_t i = 0; i < lines_to_print; ++i)
    {
        logText.setPosition({FONT_WIDTH, static_cast<float>(i * FONT_SIZE) + FONT_SIZE});
        if(gs.text_view.position.x < gs.log[i + gs.text_view.position.y].size()) {
            logText
                .setString(gs.log[i + gs.text_view.position.y]
                .substr((size_t) gs.text_view.position.x, (size_t) gs.text_view.size.x));
            gs.window.draw(logText);
        }
    }
    // Show cursor
    // ISSUE: il cursore man mano che si scrive va sempre più a destra
    logText.setString("_");
    logText.setFillColor(sf::Color::Green);
    logText.setPosition({
        static_cast<float>((gs.cursor_pos.x - gs.text_view.position.x + 1)) * FONT_WIDTH,
        static_cast<float>((gs.cursor_pos.y - gs.text_view.position.y + 1)) * FONT_SIZE + 3
    });
    gs.window.draw(logText);

    gs.window.display();
}

int main()
{
    State gs(800, 600, "My Editor");
    while (gs.window.isOpen()) // main loop
    {
        // event loop and handler through callbacks
        gs.window.handleEvents([&](const auto &event)
                               { handle(event, gs); });
                               
        doGraphics(gs);
    }
}