#include "game.h"

const sf::Vector2f Game::CENTER = sf::Vector2f(300,300);
const sf::Vector2f Game::SCREENSIZE = sf::Vector2f(600,600);


/**
 * @brief Constructor to set the size of windows
 *        and initialize objects
 */
Game::Game()
    : mWindow(sf::VideoMode(SCREENSIZE.x, SCREENSIZE.y), "Dragon Fractal", sf::Style::Close)
    , mVertices(sf::LinesStrip), zoomDim(10)
{
    updateVertices();
    updateZoomDimension();
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
    else if (key == sf::Keyboard::Space && isPressed) {
        mDragonSets.Rotate();
        updateVertices();
        updateZoomDimension();
    }
}

/**
 * @brief Function to reset vertices to get new sets of points
 */
void Game::updateVertices()
{
    mVertices.clear();    // for now, ignore efficiency
    mVertices.resize(mDragonSets.getSize());
    int i = 0;
    for(point N : mDragonSets.getSeq()) // for every point in sequence
    {
        mVertices[i].position = point(CENTER.x + N.x, CENTER.y - N.y); // SFML's y is inverted
        mVertices[i++].color  = sf::Color::Green;
    }
    updateZoomDimension();
}

/**
 * @brief Helper function to update how much zoom is needed at an iteration
 */
void Game::updateZoomDimension()
{
    zoomDim = (mDragonSets.getIteration() + 1)*10;
    mView.reset(sf::FloatRect( CENTER.x - zoomDim, CENTER.y - zoomDim,
                               zoomDim*2, zoomDim*2) );
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
    mWindow.setView(mView);
    mWindow.clear();
    mWindow.draw(mVertices);
    mWindow.display();
}

