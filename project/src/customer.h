#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#ifndef ENTITY_USE_VECTOR
#define ENTITY_USE_VECTOR
#endif

#include <string>

#include <EntityProject/ANVIL2/customer.h>

#include "entity_observable.h"  // NOLINT

namespace csci3081 {
/// Represents a customer in the drone delivery subsystem
/**
 * The Customer class is a simple class representing a customer in the drone delivery subsystem.
 * The Customer class inherits from the entity_project::Customer class, allowing Customer classes 
 * to interact with the facade of the drone delivery subsystem. Furthermore, the Customer class inherits
 * from EntityObservable, allowing it to be observed by entity_project::EntityObserver objects.
*/
class Customer : public entity_project::Customer, public EntityObservable {
 public:
    /** Constructs a Customer class given the relevant parameters. If the position or 
     *  direction vectors are provided with fewer than 3 entries, the remaining 
     *  entries will be set to 0.
     * @param name reference to a string containing the name of the customer
     * @param position reference to a picojson::array containing the position of the customer
     * @param direction reference to a picojson::array containing the direction of the customer
     * @param radius float containing the radius of the customer
     * @param object reference to a picojson::object containing the JSON data of the customer
     */
    explicit Customer(const std::string& name, const picojson::array& position,
        const picojson::array& direction, float radius, const picojson::object& object);
    /** Default constructor for the Customer class. The customer radius is set to 1. Dynamic is 
     *  set to false and all other variables are either set to 0 or default constructed.
     */
    Customer();
    /** Updates the current Customer
     * by the time interval dt. This 
     * function usually does nothing,
     * for the Customer is usually static.
     * @param dt time interval
     */
    void Update(float dt);
    /** Sets the dynamic state of the Customer.
     *  @param dynamic new dynamic state of the Customer.
     */
    void SetDynamic(bool dynamic) { dynamic_ = dynamic; }
    /** Determines if the Customer is dynamic.
     *  @returns boolean indicating if the Customer is dynamic
     */
    bool IsDynamic() const override { return dynamic_; }

 private:
    bool dynamic_;
};

}  // namespace csci3081

#endif
