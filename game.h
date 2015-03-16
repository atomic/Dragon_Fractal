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

    void					updateZoomDimension();
    void					updateVertices();
    void 				    prepareAnimation(sf::Time elapsedTime);
    void 				    updatePhase();

private:
    // Settings Default
    static const sf::Vector2f CENTER;
    static const sf::Vector2f SCREENSIZE;

    FractalSequence           mDragonSets;

    // Graphics
    size_t                    zoomDim; // keep track of how much screen is zoomed
    sf::RenderWindow		  mWindow;
    sf::View         	      mView;
    sf::VertexArray           mVertices;

    // Animation
    static const sf::Time	  TimePerFrame;
    static const float        angularFrameSpeed;
    sf::Time                  timeSinceLastUpdate;
    sf::Transform             mRotation;
    sf::Vector2f              mRotationOrigin;
    bool                      mIsRotating;
    float                     mDegreesRotated;

    // Stats
    sf::Font                  mFont;
    sf::Text                  mTextIter;
};

#endif // GAME_H

