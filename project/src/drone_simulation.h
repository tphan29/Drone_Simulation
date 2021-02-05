#ifndef DRONE_SIMULATION_H_
#define DRONE_SIMULATION_H_

#include <vector>
#include <string>

#include <EntityProject/ANVIL/drone_delivery_system.h>

#include "entity_factory.h"  // NOLINT
#include "delivery_scheduler.h"  // NOLINT

namespace csci3081 {


/// The concrete implementation of the entity_project::DroneDeliverySystem facade
/**
 * The DroneSimulation class provides a simple to use iterface to abstract away the 
 * details of the drone delivery subsystem. 
 */
class DroneSimulation : public entity_project::DroneDeliverySystem {
 public:
    /// Constructs a DroneSimulation class.
    DroneSimulation();
    /// Retrieves the team name associated with the DroneSimulation
    /**
     * @returns team name as a std::string
     */
    const std::string& GetTeamName() const { return teamName_; }
    /// Creates an entity from JSON data
    /**
     * @param val JSON data of the entity as specified in the <a href="https://pages.github.umn.edu/umn-csci-3081-f20/project-portal/Iteration1Requirements.pdf">Iteration 1</a> requirements.
     * @returns pointer to an instance of entity_project::Entity
     */
    entity_project::Entity* CreateEntity(const picojson::object& val);
    /// Adds an entity to the drone simulation
    /**
     * @param entity pointer to the entity
     */
    void AddEntity(entity_project::Entity* entity);
    /// Schedules a delivery by making use of the DeliveryScheduler
    /**
     * @param package pointer to the package
     * @param dest pointer to the customer the package is intended for
     * @param details reference to the JSON data containing the details of the delivery
     */
    void ScheduleDelivery(entity_project::Package* package,
    entity_project::Customer* dest, const picojson::object& details);
    /// Attaches an observer to an entity
    /**
     * @param entity pointer to the entity
     * @param observer pointer to the observer to be added
     */
    void AddObserver(entity_project::Entity* entity, entity_project::EntityObserver* observer);
    /// Detaches an observer from an entity
    /**
     * @param entity pointer to the entity
     * @param observer pointer to the observer to be removed
     */
    void RemoveObserver(entity_project::Entity* entity, entity_project::EntityObserver* observer);
    /// Returns the entities in the drone delivery subsystem
    /**
     * @returns std::vector of pointers to entity_project::Entity
     */
    const std::vector<entity_project::Entity*>& GetEntities() const { return entities_; }
    /// Updates the simulation by time interval dt. The DeliveryScheduler is updated, then
    /// all of the entities in the subsystem are updated by time interval dt.
    /**
     * @param dt time interval
     */
    void Update(float dt);

 private:
    std::string teamName_;
    std::vector<entity_project::Entity*> entities_;
    EntityFactory entityFactory_;
    DeliveryScheduler deliveryScheduler_;
};

}  // namespace csci3081


#endif  // DRONE_SIMULATION_H_
