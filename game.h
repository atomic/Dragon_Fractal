#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>


class Game : private sf::NonCopyable
{
public:
    Game();
    void					run();

private:
    void					processEvents();
    void					update();
    void					render();

    void					handlePlayerInput(sf::Keyboard::Key key, bool isPressed);


private:
    sf::RenderWindow		mWindow;
    sf::RectangleShape      mRect;
};

#endif // GAME_H

