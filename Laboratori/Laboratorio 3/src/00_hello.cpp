#include <SFML/Graphics.hpp>
#include "../resources/textures.hpp"

//////////////////////
// Initial defaults //
//////////////////////

// window
const char *window_title = "00 - hello";
const unsigned window_width = 800;
const unsigned window_height = 600;
const float max_frame_rate = 60;

// ball
const float ball_radius = 10.0;
const float ball_speed = 300.0;
const sf::Angle ball_start_angle = sf::degrees(-70);

// paddle
const sf::Vector2f paddle_size = {100.0, 16.0};
const float paddle_speed = 400.0;

////////////
// Update //
////////////

sf::Angle reflect_horizontal(sf::Vector2f v)
{
    v.x = -v.x;
    return v.angle();
}

sf::Angle reflect_vertical(sf::Vector2f v)
{
    v.y = -v.y;
    return v.angle();
}

sf::Angle reflect_horizontal (sf::Angle a)
{
    sf::Vector2f v (1.0, a);
    return reflect_horizontal (v);
}

sf::Angle reflect_vertical (sf::Angle a)
{
    sf::Vector2f v (1.0, a);
    return reflect_vertical (v);
}

////////////
// Paddle //
////////////

struct Paddle
{
    sf::Vector2f size;
    sf::Vector2f pos;
    sf::Texture tt;
    float speed;

    Paddle();
    void draw(sf::RenderWindow &window);
    void move_left(float elapsed);
    void move_right(float elapsed);
    bool hit(Ball &ball);
};

Paddle::Paddle()
{
    size = paddle_size;
    float paddle_px = ((float)window_width / 2.0) - (paddle_size.x / 2.0);
    float paddle_py = ((float)window_height - paddle_size.y);

    pos = {paddle_px, paddle_py};
    tt = sf::Texture(paddle_png, paddle_png_len);
    speed = paddle_speed;
}

void Paddle::draw(sf::RenderWindow &window)
{
    sf::RectangleShape paddle(size);
    paddle.setPosition(pos);
    paddle.setTexture(&tt);
    window.draw(paddle);
}

void Paddle::move_left(float elapsed)
{
    if (pos.x < 0)
        pos.x = 0;
    pos.x -= speed * elapsed;
}

void Paddle::move_right(float elapsed)
{
    if (pos.x > window_width - size.x)
        pos.x = window_width - size.x;
    pos.x += speed * elapsed;
}

bool Paddle::hit (Ball& ball)
{
    sf::Vector2f v (1.0, ball.angle);
    return
        v.y > 0 &&
        ball.pos.y + ball.radius * 2.0 >= window_height - size.y &&
        ball.pos.x + ball.radius * 2.0 > pos.x &&
        ball.pos.x < pos.x + size.x;
}

////////////
// Ball //
////////////

struct Ball
{
    float radius;
    sf::Vector2f pos;
    sf::Texture tt;
    float speed;
    sf::Angle angle;

    Ball();
    void draw(sf::RenderWindow &window);
    void move(float elapsed);
};

Ball::Ball()
{
    radius = ball_radius;
    float ball_px = ((float)window_width / 2.0) - ball_radius;
    float ball_py = (float)window_height - paddle_size.y - (ball_radius * 2);

    pos = {ball_px, ball_py};
    tt = sf::Texture(ball_png, ball_png_len);
    speed = ball_speed;
    angle = ball_start_angle;
}

void Ball::draw(sf::RenderWindow &window)
{
    sf::CircleShape ball(radius);
    ball.setPosition(pos);
    ball.setTexture(&tt);
    window.draw(ball);
}

void Ball::move(float elapsed)
{
    sf::Vector2f displacement(speed * elapsed, angle);
    pos += displacement;
}

////////////
// State //
////////////

struct State
{
    Ball ball;
    Paddle paddle;
    bool pause, focus, move_paddle_left, move_paddle_right;

    State()
        : ball(), paddle(), pause(true), focus(true), move_paddle_left(false), move_paddle_right(false) {};
    void draw(sf::RenderWindow &window);
    void update(float elapsed);
    void field_limits();
    void collisions();
};

void State::draw(sf::RenderWindow &window)
{
    ball.draw(window);
    paddle.draw(window);
}

void State::field_limits()
{
    if (paddle.pos.x < 0.0)
        paddle.pos.x = 0.0;
    if (paddle.pos.x + paddle.size.x > window_width)
        paddle.pos.x = window_width - paddle.size.x;

    sf::Vector2f v = {1.0, ball.angle};
    if (ball.pos.x <= 0.0 && v.x < 0)
        ball.angle = reflect_horizontal(v);
    if (ball.pos.x + ball.radius * 2.0 >= window_width && v.x > 0)
        ball.angle = reflect_horizontal(v);
    if (ball.pos.y <= 0.0 && v.y < 0)
        ball.angle = reflect_vertical(v);
    if (ball.pos.y + ball.radius * 2.0 >= window_height - paddle_size.y && v.y > 0)
        ball.angle = reflect_vertical(v);
}

void State::collisions()
{
    field_limits();
}

void State::update(float elapsed)
{
    if (pause)
        return;

    ball.move(elapsed);

    if (move_paddle_left)
        paddle.move_left(elapsed);
    if (move_paddle_right)
        paddle.move_right(elapsed);

    collisions();
}

////////////
// Events //
////////////

void handle_close(sf::RenderWindow &window)
{
    window.close();
}

void handle_resize(const sf::Event::Resized &resized, sf::RenderWindow &window)
{ // constrain aspect ratio and map always the same portion of the world
    float aspect = static_cast<float>(window_width) / static_cast<float>(window_height);
    sf::Vector2u ws = resized.size;
    float new_aspect = static_cast<float>(ws.x) / static_cast<float>(ws.y);
    if (new_aspect < aspect)
        ws = {ws.x, static_cast<unsigned>(ws.x / aspect)};
    else
        ws = {static_cast<unsigned>(ws.y * aspect), ws.y};
    window.setSize(ws);
}

template <typename T>
void handle(T &event, State &state) {}

void handle(const sf::Event::KeyPressed &key, State &state)
{
    switch (key.scancode)
    {
    case sf::Keyboard::Scancode::Space:
        state.pause = !state.pause;
        return;
    case sf::Keyboard::Scancode::Left:
        state.move_paddle_left = true;
        return;
    case sf::Keyboard::Scancode::Right:
        state.move_paddle_right = true;
        return;
    default:
        return;
    }
}

void handle(const sf::Event::KeyReleased &key, State &state)
{
    switch (key.scancode)
    {
    case sf::Keyboard::Scancode::Left:
        state.move_paddle_left = false;
        return;
    case sf::Keyboard::Scancode::Right:
        state.move_paddle_right = false;
        return;
    default:
        return;
    }
}

void handle(const sf::Event::FocusGained &, State &state)
{
    state.focus = true;
}

void handle(const sf::Event::FocusLost &, State &state)
{
    state.focus = false;
    state.pause = true;
}

//////////
// Loop //
//////////

int main()
{
    sf::RenderWindow window(sf::VideoMode({window_width, window_height}), window_title);
    window.setFramerateLimit(max_frame_rate);
    window.setMinimumSize(window.getSize()); // Da' errore ma compila comunque

    State S;
    sf::Clock clock;

    while (window.isOpen())
    {
        // events
        window.handleEvents(
            [&window](const sf::Event::Closed &)
            { handle_close(window); },
            [&window](const sf::Event::Resized &event)
            { handle_resize(event, window); },
            [&S](const sf::Event::KeyPressed &event)
            { handle(event, S); },
            [&S](const sf::Event::FocusGained &event)
            { handle(event, S); },
            [&S](const sf::Event::FocusLost &event)
            { handle(event, S); },
            [&S](const sf::Event::KeyReleased &event)
            { handle(event, S); });

        // update
        S.update(clock.restart().asSeconds());

        // display
        window.clear(sf::Color::Black);
        S.draw(window);
        window.display();
    }
}
