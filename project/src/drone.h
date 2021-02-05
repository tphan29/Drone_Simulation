#ifndef DRONE_H_
#define DRONE_H_

#ifndef ENTITY_USE_VECTOR
#define ENTITY_USE_VECTOR
#endif

#include <string>
#include <vector>
#include <tuple>
#include <queue>

#include <EntityProject/ANVIL2/drone.h>
#include <EntityProject/simple_UMN_route_manager.h>
#include <EntityProject/graph.h>

#include "math.h"  // NOLINT
#include "package.h"  // NOLINT
#include "entity_observable.h"  // NOLINT
#include "drone_attributes.h"  // NOLINT
#include "route_manager.h"  // NOLINT

namespace csci3081 {

/// Represents a drone in the drone delivery subsystem
/**
 * The Drone class is a class representing the drone in the drone delivery subsystem.
 * The Drone class inherits from the entity_project::Drone class, allowing Drone classes 
 * to interact with the facade of the drone delivery subsystem. Furthermore, the Drone class inherits
 * from EntityObservable, allowing it to be observed by entity_project::EntityObserver objects. The purpose of the drone
 * is to complete orders handed to it by the DeliveryScheduler. When given an order, the drone navigates 
 * to the package, picks it up and delivers it to the customer associated with the order. Once completed,
 * the drone is ready to accept new orders from the DeliveryScheduler.
 */
class Drone : public entity_project::Drone, public EntityObservable {
 public:
    enum PhysicsModel { VELOCITY, ACCELERATION, FORCE };
    /** Constructs a Drone class given the relevant parameters. If the position or direction vectors
     *  are provided with fewer than 3 entries, the remaining entries will be set to 0.
     * @param name reference to a string containing the name of the drone
     * @param position reference to a picojson::array containing the position of the drone
     * @param direction reference to a picojson::array containing the direction of the drone
     * @param speed float containing the speed of the drone
     * @param radius float containing the radius of the drone
     * @param object reference to a picojson::object containing the JSON data of the drone
     */
    explicit Drone(const std::string& name, const picojson::array& position,
        const picojson::array& direction, float speed, float radius,
        const picojson::object& object);
    /** Constructs a Drone class given the relevant parameters. If the position or direction vectors
     *  are provided with fewer than 3 entries, the remaining entries will be set to 0.
     * @param name reference to a string containing the name of the drone
     * @param position reference to a picojson::array containing the position of the drone
     * @param direction reference to a picojson::array containing the direction of the drone
     * @param speed float containing the speed of the drone
     * @param radius float containing the radius of the drone
     * @param droneAttributes drone attributes parsed from the csv file data/planet-x.csv
     * @param object reference to a picojson::object containing the JSON data of the drone
     */
    explicit Drone(const std::string& name, const picojson::array& position,
        const picojson::array& direction, float radius, const DroneAttributes& droneAttributes,
        PhysicsModel physicsModel, const picojson::object& object);
    /** Default constructor for the Drone class. By default, the drone radius is set to 1.
     *  The speed is set to 30 and all other variables are either default constructed or set to 0. 
     *  (The position and direction vectors of the drone are all set to 0)
     */
    Drone();
    /**
     * Associates a package with the given Drone. When associating an package with a drone, it is important
     * to check if the drone can hold the package. Attempting to make the drone hold more than its capacity 
     * can result in undefined behavior.
     * @param package pointer to the package
     */
    void AddPackage(csci3081::Package* package);
    /**
     * This function determines if a package can be delivered by the drone by checking 
     * if the remaining capacity of the drone is greater than or equal to the weight of
     * the package. This function should always be called before attempting to add a 
     * package to a drone.
     * @returns boolean indicating if the package can be delivered by the drone
     */
    bool CanDeliverPackage(csci3081::Package* package);
    /**
     * Returns a vector containing all of the packages that are waiting to be picked up by
     * the drone.
     * This function should be called in order to reschedule pending packages when a drone
     * runs out of battery. To prevent dangling pointers, this vector shoudl also be cleared
     * after the packages are rescheduled.
     * @returns reference to a vector of Package pointers
     */
    std::vector<csci3081::Package*>& GetPendingPackages() { return pendingPackages_; }
    /**
     * Returns a vector containing all of the packages that the drone is currently carrying.
     * This function should be called in order to reschedule carried packages when a drone
     * runs out of battery. To prevent dangling pointers, this vector shoudl also be cleared
     * after the packages are rescheduled. 
     * @returns reference to a vector of Package pointers
     */
    std::vector<csci3081::Package*>& GetCarriedPackages() { return carriedPackages_; }
    /** 
     * Returns a vector containing all of the packages that the drone has recently delivered. 
     * This function should be called after calling the Drone's Update function to remove the 
     * delivered packages from the subsystem. To prevent dangling pointers, this vector
     * should also be cleared after removing the packages from the subsystem.
     * @returns reference to a vector of Package pointers
     */
    std::vector<csci3081::Package*>& GetDeliveredPackages() { return deliveredPackages_; }
    /**
     * Returns a reference to a vector of entity_project::SimpleUMNRoutePoint representing
     * the current route that the drone is traversing.
     * GetRoute will return an empty vector if the drone is not currently traversing a route.
     * @returns reference to a std::vector of entity_project::SimpleUMNRoutePoint
     */
    const std::vector<const entity_project::IGraphNode*>& GetRoute();
    /**
     * Sets the route that a drone should traverse. Subsequent calls to Update will 
     * result in the drone moving along the given route.
     * @param route const reference to a std::vector of entity_project::SimpleUMNRoutePoint
     */
    void SetRoute(const std::vector<const entity_project::IGraphNode*>& route);
    /**
     * Retrieves the current route that the drone is traversing. The route is given as a 
     * vector of strings, where each string contains the corresponding name of the IGraphNode.
     * @returns the route as a const reference to a vector of strings
     */
    const std::vector<std::string>& GetCurrentRoute() const { return currentRoute_; }
    /**
     * Returns the mass of the drone in kg.
     * @returns mass of drone in kg as a float
     */
    float GetMass() const { return mass_; }
    /**
     * Returns the maximum speed of the drone in m/s
     * @returns maximum speed of drone in m/s as a float
     */
    float GetMaxSpeed() const { return maxSpeed_; }
    /**
     * Returns the base acceleration of the drone in m/s^2.
     * @returns base accleration in m/s^2 as a float
     */
    float GetBaseAcceleration() const { return baseAcceleration_; }
    /**
     * Returns the maximum capacity in kg that the drone can carry.
     * @returns maximum capacity in kg as a float
     */
    float GetMaxCapacity() const { return weightCapacity_; }
    /**
     * Returns the base battery capacity of the drone in seconds.
     * @returns base battery capacity in seconds as a float
     */
    float GetBaseBatteryCapacity() const { return baseBatteryCapacity_; }
    /**
     * Returns the current speed in kh/h of the drone.
     * @returns current speed in km/h as a float
     */
    float GetCurrentSpeed() const { return currentSpeed_; }
    /**
     * Returns the remaining capacity of the drone in kg.
     * @returns remaining capacity in kg as a float
     */
    float GetRemainingCapacity() const { return remainingCapacity_; }
    /**
     * Returns the remaining battery life in seconds of the drone.
     * @returns remaining battery life in seconds as a float
     */
    float GetRemainingBattery() const { return remainingBattery_; }
    /** Updates the Drone class
     * by the time interval dt.
     * If the drone has a route with non-zero length, it will move along this route until it reaches
     * the last point in the route. The drone will attempt to pick up all of its packages in the order
     * that they were assigned to the drone. After picking up all of the drone's assigned packages,
     * the drone will traverse to the package destinations in the order that they were assigned to
     * the drone. The caller is responsible to determine if a drone has delivered a package by
     * iterating through the vector of packages returned from GetDeliveredPackages. Once, the
     * caller has removed these packages from the subsystem,
     * the caller should also clear the vector returned from GetDeliveredPackages.
     * and as a result remove the package from the entity list.
     * @param dt time interval
     */
    void Update(float dt);

 private:
    float mass_;
    float maxSpeed_;
    float baseAcceleration_;
    float weightCapacity_;
    float baseBatteryCapacity_;
    float currentSpeed_;
    float remainingCapacity_;
    float remainingBattery_;
    std::vector<csci3081::Package*> pendingPackages_;
    std::vector<csci3081::Package*> carriedPackages_;
    std::vector<csci3081::Package*> deliveredPackages_;
    std::vector<const entity_project::IGraphNode*> route_;
    std::vector<const entity_project::IGraphNode*>::iterator routeIter_;
    std::vector<std::string> currentRoute_;  // Placeholder
    PhysicsModel physicsModel_;
};

}  // namespace csci3081
#endif
