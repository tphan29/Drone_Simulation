#ifndef PACKAGE_H_
#define PACKAGE_H_

#ifndef ENTITY_USE_VECTOR
#define ENTITY_USE_VECTOR
#endif

#include <string>

#include <EntityProject/ANVIL2/package.h>

#include "entity_observable.h"  // NOLINT

namespace csci3081 {

class Drone;
class Customer;

/// Represents a package in the drone delivery subsystem
/**
 * The Package class is a simple class representing a package in the drone delivery subsystem.
 * The Package class inherits from the entity_project::Package class, allowing Package classes
 * to interact with the facade of the drone delivery subsystem. Furthermore, the Package class inherits
 * from EntityObservable, allowing it to be observed by entity_project::EntityObserver objects.
 */
class Package : public entity_project::Package, public EntityObservable {
 public:
    /** Constructs a Package class given the relevant parameters. If the position or
     *  direction vectors are provided with fewer than 3 entries, the remaining
     *  entries will be set to 0.
     * @param name reference to a string containing the name of the package
     * @param position reference to a picojson::array containing the position of the package
     * @param direction reference to a picojson::array containing the direction of the package
     * @param radius float containing the radius of the package
     * @param object reference to a picojson::object containing the JSON data of the package
     */
    explicit Package(const std::string& name, const picojson::array& position,
      const picojson::array& direction, float radius, const picojson::object& object, float weight);
    /** Default constructor for the Package class. The package radius is set to 1. Dynamic is
     *  set to false and all other variables are either set to 0 or default constructed.
     */
    Package();
    /** Sets the Drone that is currently carrying the package.
     *  This function is usually called by a Drone when it picks
     *  up a package to allow the package to synchronize its position
     *  with the position of the drone after every call to Update.
     *  @param drone pointer to the Drone that is now carrying the package
     */
    void SetDrone(Drone* drone) { drone_ = drone; }
    /** Sets the Customer that is associated with the package. 
     *  This function should only be called in the package's 
     *  current customer pointer is nullptr to ensure that 
     *  a package only belongs to at most one customer.
     *  @param customer pointer to the Customer that the package
     *  should now be associated to.
     */
    void SetCustomer(Customer* customer) { customer_ = customer; }
    /** Sets the order details of the package. 
     *  @param orderDetails a const reference to the JSON object 
     *  corresponding to the order details of the package.\
     */
    void SetOrderDetails(const picojson::object& orderDetails) { orderDetails_ = orderDetails; }
    /** Used to set the dynamic state of a Package. Usually, this function is called
     * when the package is handled by a Drone to change its dynamic state.
     * @param dynamic boolean indicating if the package is dynamic
     */
    void SetDynamic(bool dynamic) { dynamic_ = dynamic; }
    /** Returns a boolean indicating if the package is dynamic
     * @returns boolean indicating if the package is dynamic
     */
    bool IsDynamic() const override { return dynamic_; }
    /** Returns the weight of the package in kg
     * @returns weight of the package in kg as a float
     */
    float GetWeight() const { return weight_; }
    /** Returns the drone that is currently carrying the package.
     *  This function will return nullptr if the package is not
     *  currently being carried by a drone.
     *  @returns pointer to the Drone object that is carrying the package
     */
    Drone* GetDrone() { return drone_; }
    /** Returns the customer that the package is intended for.
     *  This function will return nullptr if the package is not
     *  currently associated with a customer.
     *  @returns pointer to the customer that the package is intended for.
     */
    Customer* GetCustomer() { return customer_; }
    /** Returns a const reference to the order details of the package. 
     *  This function should only be called if GetCustomer() is not nullptr, 
     *  otherwise orderDetails_ will be empty.
     *  @returns const reference to a picojson::object containing the order
     *  details associated with the package.
     */
    const picojson::object& GetOrderDetails() const { return orderDetails_; }
    /** Updates the current Package class
     * by the time interval dt. If the package
     * is currently being carried by a drone, it
     * will update its position to match the position
     * of the drone that is carrying it.
     * @param dt time interval
     */
    void Update(float dt);

 private:
    Drone* drone_;
    Customer* customer_;
    picojson::object orderDetails_;
    bool dynamic_;
    float weight_;
};

}  // namespace csci3081
#endif
