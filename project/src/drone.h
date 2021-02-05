#ifndef DRONE_H_
#define DRONE_H_

#include <string>
#include <vector>
#include <tuple>

#include <EntityProject/ANVIL/drone.h>
#include <EntityProject/simple_UMN_route_manager.h>

#include "math.h"  // NOLINT
#include "package.h"  // NOLINT
#include "order.h"  // NOLINT
#include "entity_observable.h"  // NOLINT

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
      const picojson::array& direction, float speed, float radius, const picojson::object& object);
    /** Default constructor for the Drone class. By default, the drone radius is set to 1.
     *  The speed is set to 30 and all other variables are either default constructed or set to 0. 
     *  (The position and direction vectors of the drone are all set to 0)
     */
    Drone();
    /**
     * Associates an order with the given Drone. When associating an order with a drone, it is important
     * to check if the drone is not already associated with another order. Attempting to associate an 
     * order with a drone that is currently processing an order can result in undefined behavior. 
     * @param order pointer to the order
     */
    void SetOrder(csci3081::Order* order);
    /**
     * Returns a pointer to the order that the drone is currently processing. GetOrder will return nullptr if 
     * the drone is not processing an order.
     * @returns pointer to the order associated with the drone
     */
    csci3081::Order* GetOrder();
    /**
     * Returns a pointer to the package that a drone is carrying. GetPackage will return nullptr if
     * the drone is not carrying a package. It is important to note that GetPackage returning nullptr
     * does not imply that the drone is not currently processing an order. 
     * @returns pointer to the package carried by the drone
     */
    csci3081::Package* GetPackage();
    /**
     * Returns a reference to a vector of entity_project::SimpleUMNRoutePoint representing
     * the current route that the drone is traversing.
     * GetRoute will return an empty vector if the drone is not currently traversing a route.
     * @returns reference to a std::vector of entity_project::SimpleUMNRoutePoint
     */
    std::vector<entity_project::SimpleUMNRoutePoint>& GetRoute();
    /**
     * Sets the route that a drone should traverse. Subsequent calls to Update will 
     * result in the drone moving along the given route.
     * @param route const reference to a std::vector of entity_project::SimpleUMNRoutePoint
     */
    void SetRoute(const std::vector<entity_project::SimpleUMNRoutePoint>& route);
    /** Updates the Drone class
     * by the time interval dt. 
     * If the drone has a route with non-zero length, it will move along this route until it reaches
     * the last point in the route. Furthermore, if the drone is in range of a package to pick up,
     * it will set its internal package pointer to that package. Once the drone is in range of 
     * the customer, it will notify observers of the event and then delete its internal order 
     * and set it to nullptr. The caller is responsible to determine if a drone has delivered a package
     * and as a result remove the package from the entity list.
     * @param dt time interval
     */
    void Update(float dt);

 private:
    csci3081::Order* order_;
    csci3081::Package* package_;
    static entity_project::SimpleUMNRouteManager routeManager_;
    std::vector<entity_project::SimpleUMNRoutePoint> route_;
    std::vector<entity_project::SimpleUMNRoutePoint>::iterator routeIter_;
    float speed_;
};

}  // namespace csci3081
#endif
