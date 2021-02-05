#ifndef DRONE_ATTRIBUTES_H_
#define DRONE_ATTRIBUTES_H_

namespace csci3081 {
/**
 * Helper object representing attributes for drones as outlined in the 
 * <a href="https://github.umn.edu/umn-csci-3081-f20/project-portal/blob/master/Iteration2Requirements.pdf">Iteration 2</a> requirements
 */
struct DroneAttributes {
    float mass;  // Mass of the drone in kg
    float maxSpeed;  // Max speed of the drone in km/h
    float baseAcceleration;  // Base acceleration of the drone in m/s^2
    float weightCapacity;  // Weight capacity of the drone
    float baseBatteryCapacity;  // Base battery capacity in seconds
};
}  // namespace csci3081

#endif
