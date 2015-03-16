#include "game.h"

const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f); // 60 fps
const float Game::angularFrameSpeed = 14;
const sf::Vector2f Game::CENTER = sf::Vector2f(300,300);
const sf::Vector2f Game::SCREENSIZE = sf::Vector2f(600,600);


/**
 * @brief Constructor to set the size of windows
 *        and initialize objects
 */
Game::Game()
    : mWindow(sf::VideoMode(SCREENSIZE.x, SCREENSIZE.y), "Dragon Fractal", sf::Style::Close)
    , mVertices(sf::LinesStrip), zoomDim(10), mIsRotating(false), mDegreesRotated(0)
{
    mFont.loadFromFile("../Dragon_Fractal/proximanova.ttf");
    mTextIter.setFont(mFont);
    mTextIter.setString("Iteration : " + 0);
    mTextIter.setColor(sf::Color::Red);

    updateVertices();
    updateZoomDimension();
    mRotationOrigin = mVertices[mVertices.getVertexCount() - 1].position;
}

/**
 * @brief a function to start the whole game mode
 */
void Game::run()
{
    sf::Clock clock;
    timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen())
    {
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;

            processEvents();
            update(TimePerFrame);
        }
        render();
    }
}

/** Controller
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

/** Controller
 * @brief Based on the key inputs, do actions
 * @param key inputted, whether key is pressed or released
 */
void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
    using namespace sf;
    if(isPressed) {
        switch (key) {
        case Keyboard::Escape:        mWindow.close();     break;
        case Keyboard::BackSpace:     mWindow.close();     break;
        case Keyboard::Space:         mDragonSets.Rotate(); updateVertices();
            //            updateZoomDimension();
            break;
        case Keyboard::Tab:           mIsRotating = !mIsRotating;                break;
        case Keyboard::Up:            zoomDim += 5 ; updateZoomDimension();      break;
        case Keyboard::Down:          zoomDim -= 5 ; updateZoomDimension();      break;
        default:
            break;
        }
    }
}

/** Logic
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
}

/** Animation
 * This is called every frame (depending on the time)
 * @brief a function to render the animation of next degrees of rotation
 */
void Game::prepareAnimation(sf::Time elapsedTime)
{
    float frame_delta = angularFrameSpeed*elapsedTime.asSeconds();
    mDegreesRotated += frame_delta;
    mRotation.rotate(frame_delta, mRotationOrigin); // for now test rotating about the center
}

/** Animation
 * @brief Function will get new origin for the rotation, and other stuffs
 */
void Game::updatePhase()
{
    mDragonSets.Rotate();
    // setting up new origin
    updateVertices();
    mRotationOrigin = mVertices[mVertices.getVertexCount() - 1].position;
    mDegreesRotated = 0;
    mRotation = sf::Transform::Identity;
//    updateZoomDimension(); // temporary, might switch to key based
    mIsRotating = true;
}

/** View
 * @brief Helper function to update how much zoom is needed at an iteration
 */
void Game::updateZoomDimension()
{
//    zoomDim = pow(mDragonSets.getIteration() + 1, 2)*1; // need better function to approximate this changes
    mView.reset(sf::FloatRect( CENTER.x - zoomDim, CENTER.y - zoomDim,
                               zoomDim*2, zoomDim*2) );
}


/**
 * @brief update informations to next thread
 */
void Game::update(sf::Time elapsedTime)
{
    if(mIsRotating) {
        prepareAnimation(elapsedTime);
        if(mDegreesRotated > 90) {
            updatePhase();
        }
    }
}



/** View
 * @brief a function to draw objects
 */
void Game::render()
{
    mWindow.setView(mView);
    mWindow.clear();
    if(mIsRotating)
        mWindow.draw(mVertices, mRotation);
    mWindow.draw(mVertices);
//    mWindow.draw(mTextIter); // hard to draw
    mWindow.display();
}

