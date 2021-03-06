#include "fractalsequence.h"

FractalSequence::FractalSequence() : iteration(0)
{
    // initialize the first 2 points, or, iteration 0
    mSequence.push_back(point(0,0));
    mSequence.push_back(point(1,0));
}

/**
 * Implemented by : Nancy
 * @brief Function to populate mSequence with new members generated by iteration
 */
void FractalSequence::Rotate()
{
    //X,Y are the coordinates of the point
    //x_last and y_last are the coordinates of the rotate point
    //x_rotate and y_rotate are the coordinates after rotating
    int X = 0,Y = 0;
    int last = mSequence.size();
    int x_turning = mSequence[last-1].x,y_turning = mSequence[last-1].y;
    int x_rotating = 0,y_rotating = 0;

    for (int i=last-2;i>=0;i--) {
        //get the point
        X = mSequence[i].x;
        Y = mSequence[i].y;

        //change to the new system
        X = X - x_turning;
        Y = Y - y_turning;
        y_rotating = -X;
        x_rotating = Y;

        //change back to the original system
        y_rotating = y_rotating+y_turning;
        x_rotating = x_rotating+x_turning;

        //put the value into vector
        mSequence.push_back(sf::Vector2f(x_rotating,y_rotating));
    }

    iteration++;
}

/**
 * @brief Reset the sets, and internal data
 */
void FractalSequence::Reset()
{
    mSequence.clear(); iteration = 0;
    mSequence.push_back(point(0,0));
    mSequence.push_back(point(1,0));
}

/**
 * @brief Function to calculate the number of points for given iteration
 * @param iteration points
 * @return number of points
 */
size_t FractalSequence::getSizeAt(size_t atIteration)
{
    // tested, working
    // series expansion 2 + 2*i_prev - 1, i_prev is defined recursively
    if(atIteration == 0) return 2;
    else return 2*getSizeAt(atIteration - 1) - 1;
}

/**
 * @brief Needed to rotate about last point
 */
sf::Vector2f FractalSequence::getLastPoint()
{
    return *(mSequence.end());
}

FractalSequence::~FractalSequence()
{
    mSequence.clear();
}

