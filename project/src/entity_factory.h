#ifndef ENTITY_FACTORY_H_
#define ENTITY_FACTORY_H_

#include <utility>
#include <string>

#include <EntityProject/entity.h>

#include "drone.h"  // NOLINT
#include "customer.h"  // NOLINT
#include "package.h" // NOLINT

namespace csci3081 {
/// The EntityFactory class is responsible for constructing entities
/**
 * The EntityFactory class constructs instances of entity_project::Entity given the relevant 
 * JSON data as described in the <a href="https://pages.github.umn.edu/umn-csci-3081-f20/project-portal/Iteration1Requirements.pdf">Iteration 1</a> requirements.
 * As of writing this documentation, the three main entities in the drone delivery subsystem are Drone, Customer and Package. However, 
 * more entities may be added in the future. 
 */
class EntityFactory {
 public:
    /**
     * Creates an instance of an entity_project::Entity given the relevant JSON data 
     * as described in the <a href="https://pages.github.umn.edu/umn-csci-3081-f20/project-portal/Iteration1Requirements.pdf">
     * Iteration 1</a> requirements.
     * @param object const reference to a picojson::object containing the JSON data of the entity
     * @returns pointer to the newly constructed entity_project::Entity instance
     */
    entity_project::Entity* CreateEntity(const picojson::object& object);
};
}  // namespace csci3081

#endif
