#include "delivery_scheduler.h"  // NOLINT

namespace csci3081 {
    DeliveryScheduler::DeliveryScheduler(std::vector<entity_project::Entity*>* entities)
        : entities_(entities) {}
    void DeliveryScheduler::ScheduleDelivery(entity_project::Package* package,
     entity_project::Customer* dest, const picojson::object& details) {
        csci3081::Package* packageCast = package->AsType<csci3081::Package>();
        csci3081::Customer* destCast = dest->AsType<csci3081::Customer>();
        if (packageCast != nullptr && destCast != nullptr) {
            float packageDist = Dist(packageCast->GetPosition()[0], packageCast->GetPosition()[1],
                packageCast->GetPosition()[2], destCast->GetPosition()[0],
                destCast->GetPosition()[1],
                destCast->GetPosition()[2]);
            // Check if the package is already in range of the customer
            if (packageDist <= packageCast->GetRadius() + destCast->GetRadius()) {
                // Notify package observers
                // that the package has been delivered
                picojson::object packageEvent;
                packageEvent["type"] = picojson::value("notify");
                packageEvent["value"] = picojson::value("delivered");
                packageCast->NotifyObservers(picojson::value(packageEvent));

                entities_->erase(std::remove(entities_->begin(), entities_->end(), packageCast),
                        entities_->end());
                return;
            }
            orderQueue_.push(new csci3081::Order(destCast, packageCast, details));
            // Notify package observers that the package is en route
            packageCast->SetDynamic(true);
            destCast->SetDynamic(true);
            picojson::object packageEvent;
            packageEvent["type"] = picojson::value("notify");
            packageEvent["value"] = picojson::value("en route");
            packageCast->NotifyObservers(picojson::value(packageEvent));
            Update(0);
        }
     }
    void DeliveryScheduler::Update(float dt) {
        auto iter = entities_->begin();
        while (!orderQueue_.empty() && iter != entities_->end()) {
            csci3081::Drone* drone = (*iter)->AsType<csci3081::Drone>();
            if (drone != nullptr && drone->GetOrder() == nullptr) {
                drone->SetOrder(orderQueue_.front());
                orderQueue_.pop();
                // Notify drone observers that the drone
                // is currently en route to pick up the package
                picojson::object droneEvent;
                droneEvent["type"] = picojson::value("notify");
                droneEvent["value"] = picojson::value("en route");
                drone->NotifyObservers(picojson::value(droneEvent));
            }
            iter++;
        }
    }
}  // namespace csci3081
