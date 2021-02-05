#ifndef ORDER_H_
#define ORDER_H_

#include <EntityProject/entity.h>
#include <string>

#include "customer.h"  // NOLINT
#include "package.h" // NOLINT

namespace csci3081 {
/// Represents an order in the drone delivery subsystem
/**
 * The Order class is a simple class used to associate a customer with a package. Orders are originally created
 * by the DeliveryScheduler and then later passed onto a Drone when a Drone is availabe. 
 */
class Order {
 public:
    /**
     * Constructs an Order given a customer, package and relevant details.
     * @param customer pointer to the customer associated with the order
     * @param package pointer to the package associated with the order
     * @param details JSON data relevant to the order
     */
    Order(csci3081::Customer* customer, csci3081::Package* package,
        const picojson::object& details);
    /**
     * Returns a pointer to the Package associated with the order.
     * @returns pointer to the Package
     */
    csci3081::Package* GetPackage();
    /**
     * Returns a pointer to the Customer associated with the order.
     * @returns pointer to the Customer
     */
    csci3081::Customer* GetCustomer();
    /**
     * Returns a const reference to the JSON data associated with the order.
     * @returns const reference to a picojson::object 
     */
    const picojson::object& GetDetails();

 private:
    csci3081::Package* package_;
    csci3081::Customer* customer_;
    const picojson::object details_;
};
}  // namespace csci3081

#endif
