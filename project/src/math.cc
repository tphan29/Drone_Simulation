#include "math.h"  // NOLINT
#include <cmath>

namespace csci3081 {

    float Dist(float x0, float y0, float z0, float x1, float y1, float z1) {
        return std::sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0) + (z1 - z0) * (z1 - z0));
    }
    float Norm(float x, float y, float z) {
        return std::sqrt(x * x + y * y + z * z);
    }
    std::tuple<float, float, float> Direction(float x0, float y0, float z0,
        float x1, float y1, float z1) {
        float distance = Dist(x0, y0, z0, x1, y1, z1);
        float x = (x1 - x0) / distance;
        float y = (y1 - y0) / distance;
        float z = (z1 - z0) / distance;
        return std::make_tuple(x, y, z);
    }
}  // namespace csci3081
