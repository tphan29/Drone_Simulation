#ifndef MATH_H_
#define MATH_H_

#include <tuple>

namespace csci3081 {
    /** Helper function to calculate the distance between 
     *  two points in three dimensions.
     *  @param x0 x coordinate of the first point
     *  @param y0 y coordinate of the first point
     *  @param z0 z coordinate of the first point
     *  @param x1 x coordinate of the second point
     *  @param y1 y coordinate of the second point
     *  @param z1 z coordinate of the second point
     *  @returns distances between the two points as a float
     */
    float Dist(float x0, float y0, float z0, float x1, float y1, float z1);
    /** Helper function to calculate the magnitude of a vector in three
     *  dimensions.
     *  @param x x coordinate of the point
     *  @param y y coordinate of the point
     *  @param z z coordinate of the point
     *  @returns magnitude of the vector
     */
    float Norm(float x, float y, float z);
    /** Helper function to calculate the unit vector pointing from 
     *  one point to another point.
     *  @param x0 x coordinate of the first point
     *  @param y0 y coordinate of the first point
     *  @param z0 z coordinate of the first point
     *  @param x1 x coordinate of the second point
     *  @param y1 y coordinate of the second point
     *  @param z1 z coordinate of the second point
     *  @returns the unit vector pointing from (x0, y0, z0) to (x1, y1, z1)
     *  as a tuple.
     */
    std::tuple<float, float, float>  Direction(float x0, float y0, float z0,
        float x1, float y1, float z1);
}  // namespace csci3081
#endif
