#include "delivery_scheduler.h"  // NOLINT

namespace csci3081 {
    DeliveryScheduler::DeliveryScheduler(std::vector<entity_project::Entity*>* entities)
        : entities_(entities) {}
    void DeliveryScheduler::ScheduleDelivery(entity_project::Package* package,
     entity_project::Customer* dest, const picojson::object& details) {
        csci3081::Package* packageCast = package->AsType<csci3081::Package>();
        csci3081::Customer* destCast = dest->AsType<csci3081::Customer>();
        if (packageCast && destCast && packageCast->GetCustomer() == nullptr) {
            float packageDist = Dist(packageCast->GetPosition()[0], packageCast->GetPosition()[1],
                packageCast->GetPosition()[2], destCast->GetPosition()[0],
                destCast->GetPosition()[1],
                destCast->GetPosition()[2]);
            // Notify package observers
            // that the package has been scheduled
            picojson::object packageEvent;
            packageEvent["type"] = picojson::value("notify");
            packageEvent["value"] = picojson::value("scheduled");
            packageCast->NotifyObservers(picojson::value(packageEvent));

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
                delete packageCast;
                return;
            }
            packageCast->SetCustomer(destCast);
            orderQueue_.push(packageCast);
            // Notify package observers that the package is en route
            packageCast->SetDynamic(true);
            destCast->SetDynamic(true);
            Update(0);
        }
    }
    void DeliveryScheduler::RescheduleDelivery(entity_project::Package* package) {
        csci3081::Package* packageCast = package->AsType<csci3081::Package>();
        float packageDist = Dist(packageCast->GetPosition()[0], packageCast->GetPosition()[1],
            packageCast->GetPosition()[2], packageCast->GetCustomer()->GetPosition()[0],
            packageCast->GetCustomer()->GetPosition()[1],
            packageCast->GetCustomer()->GetPosition()[2]);
        // Check if the package is already in range of the customer
        if (packageDist <= packageCast->GetRadius() + packageCast->GetCustomer()->GetRadius()) {
            // Notify package observers
            // that the package has been delivered
            picojson::object packageEvent;
            packageEvent["type"] = picojson::value("notify");
            packageEvent["value"] = picojson::value("delivered");
            packageCast->NotifyObservers(picojson::value(packageEvent));

            entities_->erase(std::remove(entities_->begin(), entities_->end(), packageCast),
                    entities_->end());
            delete packageCast;
            return;
        }

        orderQueue_.push(packageCast);
        packageCast->SetDynamic(true);
        packageCast->GetCustomer()->SetDynamic(true);
        Update(0);
    }

    void DeliveryScheduler::Update(float dt) {
        auto iter = entities_->begin();
        while (!orderQueue_.empty() && iter != entities_->end()) {
            csci3081::Drone* drone = (*iter)->AsType<csci3081::Drone>();
            if (drone != nullptr && drone->GetRemainingBattery() > 0 &&
                drone->CanDeliverPackage(orderQueue_.front())) {
                drone->AddPackage(orderQueue_.front());
                orderQueue_.pop();
            }
            iter++;
        }
    }
}  // namespace csci3081
