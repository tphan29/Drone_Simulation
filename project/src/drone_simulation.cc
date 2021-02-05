#include "drone_simulation.h"  // NOLINT
#include <stdio.h>

namespace csci3081 {
    DroneSimulation::DroneSimulation() : deliveryScheduler_(&entities_), teamName_("team17") {
    }
    DroneSimulation::~DroneSimulation() {
        for (auto e : entities_) {
            delete e;
        }
    }
    entity_project::Entity* DroneSimulation::CreateEntity(const picojson::object& val) {
        return entityFactory_.CreateEntity(val);
    }
    void DroneSimulation::AddEntity(entity_project::Entity* entity) {
        static entity_project::EntityConsoleLogger logger;
        if (entity != nullptr) {
                AddObserver(entity, &logger);
                entities_.push_back(entity);
        }
    }

    void DroneSimulation::SetGraph(const entity_project::IGraph* graph) {
        RouteManager::SetGraph(graph);
    }

    void DroneSimulation::ScheduleDelivery(entity_project::Package* package,
        entity_project::Customer* dest, const picojson::object& details) {
        if (package != nullptr && dest != nullptr)
            deliveryScheduler_.ScheduleDelivery(package, dest, details);
    }

    void DroneSimulation::AddObserver(entity_project::Entity* entity,
        entity_project::EntityObserver* observer) {
        if (entity == nullptr || observer == nullptr)
            return;
        if (entity->AsType<csci3081::Drone>()) {
            entity->AsType<csci3081::Drone>()->AddObserver(observer);
        } else if (entity->AsType<csci3081::Customer>()) {
            entity->AsType<csci3081::Customer>()->AddObserver(observer);
        } else if (entity->AsType<csci3081::Package>()) {
            entity->AsType<csci3081::Package>()->AddObserver(observer);
        }
    }

    void DroneSimulation::RemoveObserver(entity_project::Entity* entity,
        entity_project::EntityObserver* observer) {
        if (entity == nullptr || observer == nullptr)
            return;
        if (entity->AsType<csci3081::Drone>()) {
            entity->AsType<csci3081::Drone>()->RemoveObserver(observer);
        } else if (entity->AsType<csci3081::Customer>()) {
            entity->AsType<csci3081::Customer>()->RemoveObserver(observer);
        } else if (entity->AsType<csci3081::Package>()) {
            entity->AsType<csci3081::Package>()->RemoveObserver(observer);
        }
    }

    void DroneSimulation::Update(float dt) {
        deliveryScheduler_.Update(dt);  // Update the delivery scheduler
        std::vector<entity_project::Entity*> deletedEntities_;
        for (entity_project::Entity* e : entities_) {
            csci3081::Drone* drone = e->AsType<csci3081::Drone>();
            if (drone != nullptr) {
                drone->Update(dt);
                if (!drone->GetDeliveredPackages().empty()) {
                    for (auto p : drone->GetDeliveredPackages()) {
                        deletedEntities_.push_back(p);
                    }
                    drone->GetDeliveredPackages().clear();
                }
                if (drone->GetRemainingBattery() == 0) {
                    if (!drone->GetPendingPackages().empty()) {
                        for (auto p : drone->GetPendingPackages()) {
                            deliveryScheduler_.RescheduleDelivery(p);
                        }
                        drone->GetPendingPackages().clear();
                    }
                    if (!drone->GetCarriedPackages().empty()) {
                        for (auto p : drone->GetCarriedPackages()) {
                            deliveryScheduler_.RescheduleDelivery(p);
                        }
                        drone->GetCarriedPackages().clear();
                    }
                }
                continue;
            }
            csci3081::Package* package = e->AsType<csci3081::Package>();
            if (package != nullptr) {
                package->Update(dt);
                continue;
            }
            csci3081::Customer* customer = e->AsType<csci3081::Customer>();
            if (customer != nullptr) {
                customer->Update(dt);
                continue;
            }
        }

        for (auto e : deletedEntities_) {
            entities_.erase(std::remove(entities_.begin(), entities_.end(), e), entities_.end());
            // delete e;
        }
    }
}  // namespace csci3081
