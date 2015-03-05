#include "game.h"


/**
 * @brief Constructor to set the size of windows
 *        and initialize objects
 */
Game::Game()
    : mWindow(sf::VideoMode(750,500), "SFML Application", sf::Style::Close)
{
    // Example
    mRect.setSize(sf::Vector2f(50,50));
    mRect.setFillColor(sf::Color::Green);
    mRect.setOutlineThickness(2.0);
    mRect.setOutlineColor(sf::Color::Red);
    mRect.setPosition(sf::Vector2f(50,50));
}

/**
 * @brief a function to start the whole game mode
 */
void Game::run()
{
    while (mWindow.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

/**
 * @brief receives events and
 *          and acts accordingly
 */
void Game::processEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::KeyPressed:
            handlePlayerInput(event.key.code, true);
            break;

        case sf::Event::KeyReleased:
            handlePlayerInput(event.key.code, false);
            break;

        case sf::Event::Closed:
            mWindow.close();
            break;
        }
    }
}

/**
 * @brief Based on the key inputs, do actions
 * @param key inputted, whether key is pressed or released
 */
void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
    if (key == sf::Keyboard::Escape)
        mWindow.close();
    else if (key == sf::Keyboard::BackSpace)
        mWindow.close();
}

/**
 * @brief update informations to next thread
 */
void Game::update()
{
}

/**
 * @brief a function to draw objects
 */
void Game::render()
{
    mWindow.clear();
    mWindow.draw(mRect);
    mWindow.display();
}

