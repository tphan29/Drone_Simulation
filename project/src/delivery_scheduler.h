#ifndef DELIVERY_SCHEDULER_H_
#define DELIVERY_SCHEDULER_H_

#include <vector>
#include <string>
#include <queue>

#include <EntityProject/entity.h>

#include "drone.h"  // NOLINT
#include "customer.h"  // NOLINT
#include "package.h" // NOLINT

namespace csci3081 {
/// The delivery scheduler in the drone delivery subsystem
/**
 * The DeliveryScheduler class is responsible for handling orders produced by clients
 * and dispatching drones to fulfill these orders. The DeliveryScheduler schedules deliveries by 
 * first placing each order onto an order queue. Once the Update function is called, the scheduler 
 * takes orders out of the order queue and attempts to assign
 * each order to a Drone until either there are no more drones available or the order queue is empty.
*/
class DeliveryScheduler {
 public:
    /** Constructs a DeliveryScheduler class.
     * @param entities a pointer to the list of entities in the drone delivery subsystem
     */   
    explicit DeliveryScheduler(std::vector<entity_project::Entity*>* entities);
    /** Schedules a delivery. If there are a limited number of drones available,
     * deliveries will be assigned to drones in a first in first out manner.
     * @param package the package to be delivered
     * @param dest the customer the package should be delivered to
     * @param details relevant details of the delivery in JSON format
     */
    void ScheduleDelivery(entity_project::Package* package,
        entity_project::Customer* dest, const picojson::object& details);
    /** Reschedules a delivery. This method should be called to reschedule
     *  a delivery if a Drone goes idle while still processing packages.
     *  @param package the package to be rescheduled
     */
    void RescheduleDelivery(entity_project::Package* package);
    /** Updates the DeliveryScheduler by time dt. 
      * Calls to Update will attempt to assign 
      * orders to drones in the order that the 
      * orders were scheduled. Update should be 
      * called at the beginning of the main Update
      * call for the subsystem to ensure that any 
      * orders waiting in the order queue are 
      * assigned to drones if there are drones available.
      * @param dt time interval
      */
    void Update(float dt);

 private:
    std::queue<csci3081::Package*> orderQueue_;  // queue of orders
    std::vector<entity_project::Entity*>* entities_;  // pointer to entities in the system
};

}  // namespace csci3081

#endif
