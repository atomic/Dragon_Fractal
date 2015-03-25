#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "fractalsequence.h"


// Will be implemented later
class Game : private sf::NonCopyable
{
public:
    Game();
    void					run();

private:
    void					processEvents();
    void					update(sf::Time elapsedTime);
    void					render();

    void					handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

    void					updateZoomDimension(sf::Time elapsedTime = sf::Time::Zero);
//    void					updateVertices();
    void					prepareSequenceAndVertices();
    void 				    prepareAnimation(sf::Time elapsedTime);
    void 				    updatePhase(bool isRewind = false);
    void 				    reversePhase(bool fromOrigin = true);

private:
    // Settings Default
    static const sf::Vector2f CENTER;
    static const sf::Vector2f SCREENSIZE;
    static const size_t       MAXITER;

    FractalSequence           mDragonSets;


    // Graphics
    sf::RenderWindow		  mWindow;
    float                     zoomDim; // keep track of how much screen is zoomed
    sf::View         	      mView;
    std::vector<sf::Vertex>   mVertices;

    // Animation
    static const sf::Time	  TimePerFrame;
    static const float        angularFrameSpeed;
    sf::Time                  timeSinceLastUpdate;
    sf::Transform             mRotation;
    sf::Vector2f              mRotationOrigin;
    bool                      mIsRotating;
    bool                      mIsRewind;
    bool                      mIsDrawn;
    float                     mDegreesRotated;
    size_t                    mIteration;
    size_t                    mCurrentSetSize;

    // Stats
    sf::Font                  mFont;
    sf::Text                  mTextIter;
};

#endif // GAME_H

