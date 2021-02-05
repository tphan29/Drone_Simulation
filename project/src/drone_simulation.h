#ifndef DRONE_SIMULATION_H_
#define DRONE_SIMULATION_H_

#include <vector>
#include <string>

#include <EntityProject/entity_console_logger.h>
#include <EntityProject/ANVIL2/drone_delivery_system.h>
#include <EntityProject/graph.h>

#include "entity_factory.h"  // NOLINT
#include "delivery_scheduler.h"  // NOLINT
#include "route_manager.h"  // NOLINT

namespace csci3081 {
/// The concrete implementation of the entity_project::DroneDeliverySystem facade
/**
 * The DroneSimulation class provides a simple to use iterface to abstract away the
 * details of the drone delivery subsystem.
 */
class DroneSimulation : public entity_project::DroneDeliverySystem {
 public:
    /// Constructs a DroneSimulation class.
    /**
     * Sets up the DroneSimulation class by assigning the team name
     * and passing the entities_ vector to the DeliveryScheduler constructor
     * @param entity const reference to the associated entity
     */
    DroneSimulation();
    /// Destructs a DroneSimulation classs.
    /**
     * Upon destruction of the DroneSimulation class, all entities that
     * remain in the subsystem will be deleted.
     */
    ~DroneSimulation();
    /// Retrieves the team name associated with the DroneSimulation
    /**
     * Used for returning the team name.
     * @returns team name as a std::string
     */
    const std::string& GetTeamName() const { return teamName_; }
    /// Creates an entity from JSON data
    /**
     * This method will delegate the creation of entities to entityFactory.
     * @param val JSON data of the entity as specified in the <a href="https://github.umn.edu/umn-csci-3081-f20/project-portal/blob/master/Iteration2Requirements.pdf">Iteration 2</a> requirements.
     * @returns pointer to an instance of entity_project::Entity
     */
    entity_project::Entity* CreateEntity(const picojson::object& val);
    /// Adds an entity to the drone simulation
    /**
     * This method will add the entity parameter to the entities_ vector.
     * In addition it will make calls to attach an observer to the entity.
     * @param entity pointer to the entity
     */
    void AddEntity(entity_project::Entity* entity);
    /// Sets the underlying IGraph object that the simulation should use for calculating the
    /// shortest path between points.
    /// The pointer to the graph is handed off to the route manager so that it can effectively
    /// calculate shortest path between points.
    /**
     * Used to set the IGraph object that the simulation will use to calculate
     * the shortest path between two points. This method calls RouteManager's
     * SetGraph method, which is where the actual calculation is done.
     * @param graph const pointer to the entity_project::IGraph instance
     */
    void SetGraph(const entity_project::IGraph* graph);
    /// Schedules a delivery by making use of the DeliveryScheduler
    /**
     * This method calls DeliveryScheduler's ScheduleDelivery method which
     * assigns drones with packages.
     * @param package pointer to the package
     * @param dest pointer to the customer the package is intended for
     * @param details reference to the JSON data containing the details of the delivery
     */
    void ScheduleDelivery(entity_project::Package* package,
    entity_project::Customer* dest, const picojson::object& details);
    /// Attaches an observer to an entity
    /**
     * This method can be used to attach an observer to an entity.
     * @param entity pointer to the entity
     * @param observer pointer to the observer to be added
     */
    void AddObserver(entity_project::Entity* entity, entity_project::EntityObserver* observer);
    /// Detaches an observer from an entity
    /**
     * This method can be used to detach an observer from an entity.
     * @param entity pointer to the entity
     * @param observer pointer to the observer to be removed
     */
    void RemoveObserver(entity_project::Entity* entity, entity_project::EntityObserver* observer);
    /// Returns the entities in the drone delivery subsystem
    /**
     * This method is used to get the vector containing all of the current entities in
     * the simulation.
     * @returns std::vector of pointers to entity_project::Entity
     */
    const std::vector<entity_project::Entity*>& GetEntities() const { return entities_; }
    /// Updates the simulation by time interval dt. The DeliveryScheduler is updated, then
    /// all of the entities in the subsystem are updated by time interval dt.
    /**
     * This Update method will be called repeatedly throughout the similuation.
     * It will subsequently call entity's respective update methods in order to
     * update their positions, as well as DeliveryScheduler's update method to assign
     * packages to drones.
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
