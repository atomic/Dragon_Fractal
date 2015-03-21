#ifndef FRACTALSEQUENCE_H
#define FRACTALSEQUENCE_H
#include <SFML/Graphics.hpp>


typedef sf::Vector2f point;
typedef std::vector<point> sequence;

/**
 * @brief The class will be used to store the sequence of points generated at n iteration
 *
 * note : member variable naming start with m
 */
class FractalSequence
{
private:
    size_t                 iteration;
    sequence               mSequence;

public:
    // TODO :
    // 1. Construct with only 2 points, mSequence has 2 initial points
    // 2. Define a function to generate/populate sequence for next iteration
    //
    FractalSequence();

    void               Rotate();
    void               Reset();
    const sequence &   getSeq()       { return mSequence;        }
    const size_t       getIteration() { return iteration;        }
    const size_t       getSize()      { return mSequence.size(); }
    const size_t       getSizeAt(size_t atIteration);
    sf::Vector2f       getLastPoint();

    ~FractalSequence();
};

#endif // FRACTALSEQUENCE_H
