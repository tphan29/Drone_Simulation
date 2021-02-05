#include "drone_simulation.h"  // NOLINT

namespace csci3081 {
    DroneSimulation::DroneSimulation() : deliveryScheduler_(&entities_), teamName_("team17") {
    }
    entity_project::Entity* DroneSimulation::CreateEntity(const picojson::object& val) {
        return entityFactory_.CreateEntity(val);
    }
    void DroneSimulation::AddEntity(entity_project::Entity* entity) {
        if (entity != nullptr)
            entities_.push_back(entity);
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
        auto position = std::find(entities_.begin(), entities_.end(), entity);
        if (position != entities_.end()) {
            if ((*position)->AsType<csci3081::Drone>()) {
                (*position)->AsType<csci3081::Drone>()->AddObserver(observer);
            } else if ((*position)->AsType<csci3081::Customer>()) {
                (*position)->AsType<csci3081::Customer>()->AddObserver(observer);
            } else if ((*position)->AsType<csci3081::Package>()) {
                (*position)->AsType<csci3081::Package>()->AddObserver(observer);
            }
        }
    }

    void DroneSimulation::RemoveObserver(entity_project::Entity* entity,
        entity_project::EntityObserver* observer) {
        if (entity == nullptr || observer == nullptr)
            return;
        auto position = std::find(entities_.begin(), entities_.end(), entity);
        if (position != entities_.end()) {
            if ((*position)->AsType<csci3081::Drone>()) {
                (*position)->AsType<csci3081::Drone>()->RemoveObserver(observer);
            } else if ((*position)->AsType<csci3081::Customer>()) {
                (*position)->AsType<csci3081::Customer>()->RemoveObserver(observer);
            } else if ((*position)->AsType<csci3081::Package>()) {
                (*position)->AsType<csci3081::Customer>()->RemoveObserver(observer);
            }
        }
    }

    void DroneSimulation::Update(float dt) {
        deliveryScheduler_.Update(dt);  // Update the delivery scheduler
        for (entity_project::Entity* e : entities_) {
            csci3081::Drone* drone = e->AsType<csci3081::Drone>();
            if (drone != nullptr) {
                csci3081::Package* dronePackage = drone->GetPackage();
                drone->Update(dt);
                if (dronePackage != nullptr && drone->GetPackage() == nullptr) {
                    entities_.erase(std::remove(entities_.begin(), entities_.end(), dronePackage),
                        entities_.end());
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
    }

}  // namespace csci3081
