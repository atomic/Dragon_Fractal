#include "game.h"

const sf::Time Game::TimePerFrame   = sf::seconds(1.f/60.f); // 60 fps
const float Game::angularFrameSpeed = 130;
const sf::Vector2f Game::CENTER     = sf::Vector2f(300,300);
const sf::Vector2f Game::SCREENSIZE = sf::Vector2f(1024,768);
const size_t       Game::MAXITER    = 20;

/**
    at 0 : 2
    at 1 : 3
    at 2 : 5
    at 3 : 9
    at 4 : 17
    at 5 : 33
    at 6 : 65
    at 7 : 129
    at 8 : 257
    at 9 : 513
    at 10 : 1,025
    at 11 : 2,049
    at 12 : 4,097
    at 13 : 8,193
    at 14 : 16,385
    at 15 : 32,769
    at 16 : 65,537
    at 17 : 131,073
    at 18 : 262,145
    at 19 : 524,289
    at 20 : 1,048,577     Do, able
    at 21 : 2,097,153     Do, able
    at 22 : 4,194,305     Do, able
    at 23 : 8,388,609     Roughly 5 seconds to calculate, Drawable
    at 24 : 16,777,217    -- Limit
*/

/**
 * @brief Constructor to set the size of windows
 *        and initialize objects
 */
Game::Game()
    : mWindow(sf::VideoMode(SCREENSIZE.x, SCREENSIZE.y), "Dragon Fractal", sf::Style::Close)
    , zoomDim(10), mIsRotating(false), mIsDrawn(false), mDegreesRotated(0)
    , mIteration(0), mCurrentSetSize(2)
{
    mFont.loadFromFile("../Dragon_Fractal/proximanova.ttf");
    mTextIter.setFont(mFont);
    mTextIter.setString("Iteration : " + 0);
    mTextIter.setColor(sf::Color::Red);

    prepareSequenceAndVertices(); // may use multithread later on
    mRotationOrigin = mVertices[1].position;
    updateZoomDimension();
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
        case Keyboard::Tab:           mIsRotating = !mIsRotating;                break;
        case Keyboard::Up:     zoomDim *= 2        ; updateZoomDimension();      break;
        case Keyboard::Down:   zoomDim /= 2        ; updateZoomDimension();      break;
        default:
            break;
        }
    }
}

/** Logic
 * DEPRECIATED
 * @brief Function to reset vertices to get new sets of points
 *        NOTE: This function should not be used in new implementation
 */
//void Game::updateVertices()
//{
//    exit(1); // **DEPRECIATED**
//    mVertices.clear();    // for now, ignore efficiency
//    mVertices.resize(mDragonSets.getSize());
//    int i = 0;
//    for(point N : mDragonSets.getSeq()) // for every point in sequence
//    {
//        mVertices[i].position = point(CENTER.x + N.x, CENTER.y - N.y); // SFML's y is inverted
//        mVertices[i++].color  = sf::Color::Green;
//    }
//}

/**
 * NOTE: Function will only be called once in one simulation
 *
 * @brief this will populate the mDragonSets with sets N_i, i:[0,#[mIteration]]
 *        #[_] depends on how much iteration has passed, see fractalsequence.h
 *        #[_] is FractalSequence.getSizeAt()
 */
void Game::prepareSequenceAndVertices()
{
    size_t N = 0;
    while(N++ < MAXITER)        // populate sequence first (see how long)
        mDragonSets.Rotate(); // NOTE : alternatively, use multithreadin
    mVertices.clear();
    for(point P : mDragonSets.getSeq()) // for every point in sequence
    {
        mVertices.push_back(sf::Vertex(point(CENTER.x + P.x, CENTER.y - P.y), sf::Color::Green));
//        mVertices[i].position = point(CENTER.x + P.x, CENTER.y - P.y); // SFML's y is inverted
//        mVertices[i++].color  = sf::Color::Green;
    }
}

/** Animation
 * This is called every frame (depending on the time)
 * @brief a function to render the animation of next degrees of rotation
 */
void Game::prepareAnimation(sf::Time elapsedTime)
{
    float frame_delta = angularFrameSpeed*elapsedTime.asSeconds();
    mDegreesRotated  += frame_delta;
    mRotation.rotate(frame_delta, mRotationOrigin); // for now test rotating about the center
}

/** Animation
 * @brief Function will get new origin for the rotation, and other stuffs
 *        update mCurrentSetSize to reflect the size for current iteration
 */
void Game::updatePhase()
{
    mIteration++;
    mCurrentSetSize = mDragonSets.getSizeAt(mIteration);
    // setting up new origin, last point of certain iteration
    mRotationOrigin = mVertices[mCurrentSetSize - 1].position;
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
    mIsDrawn = false;
}


/**
 * @brief update informations to next thread
 */
void Game::update(sf::Time elapsedTime)
{
    if(mIsRotating) {
        prepareAnimation(elapsedTime);
        if(mDegreesRotated > 90 && mIteration < MAXITER) {
            updatePhase();
        } else if (mIteration == MAXITER) { // stop animation
            mIsRotating = false;
            mDegreesRotated = 0;
        }
    }
}



/** View
 * @brief a function to draw objects
 */
void Game::render()
{
    mWindow.setView(mView);
    if(mIsRotating) {
        mWindow.clear(); // improve performance?
        mWindow.draw(&mVertices[0], mCurrentSetSize, sf::LinesStrip, mRotation);
        mIsDrawn = false;
    }
    if(!mIsDrawn) {
        if(!mIsRotating) mWindow.clear();
        mWindow.draw(&mVertices[0], mCurrentSetSize, sf::LinesStrip);
        mIsDrawn = true; // since in this case we don't draw anything new
    }
//    mWindow.draw(mTextIter); // hard to draw
    mWindow.display();
}
