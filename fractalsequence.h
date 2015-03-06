#ifndef FRACTALSEQUENCE_H
#define FRACTALSEQUENCE_H
#include <SFML/Graphics.hpp>

/**
 * @brief The class will be used to store the sequence of points generated at n iteration
 *
 * note : member variable naming start with m
 */
class FractalSequence
{
private:
    typedef size_t iteration;
    iteration n;
    sf::Vector2f<int> mSequence;
    // To be implemented

public:
    // TODO :
    // 1. Construct with only 2 points, mSequence has 2 initial points
    // 2. Define a function to generate/populate sequence for next iteration
    //
    FractalSequence();
    ~FractalSequence();
};

#endif // FRACTALSEQUENCE_H
