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
    void					update();
    void					render();

    void					handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

    void					updateZoomDimension();
    void					updateVertices();

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
};

#endif // GAME_H

