#include "drone.h"  // NOLINT

namespace csci3081 {
    entity_project::SimpleUMNRouteManager Drone::routeManager_;

    Drone::Drone(const std::string& name, const picojson::array& position,
        const picojson::array& direction, float speed, float radius,
        const picojson::object& object)
        : EntityObservable(*static_cast<Entity*>(this)), speed_(speed), order_(nullptr),
        package_(nullptr) {
        AddType<Drone>();
        std::fill_n(position_, 3, 0);
        std::fill_n(direction_, 3, 0);
        name_ = name;
        for (int i = 0; i < position.size() && i < 3 && position[i].is<double>(); i++) {
            position_[i] = position[i].get<double>();
        }
        for (int i = 0; i < direction.size() && i < 3 && direction[i].is<double>(); i++) {
            direction_[i] = direction[i].get<double>();
        }
        radius_ = radius;
        details_ = object;
    }
    Drone::Drone() : EntityObservable(*static_cast<Entity*>(this)), speed_(30), order_(nullptr),
        package_(nullptr) {
        AddType<Drone>();
        std::fill_n(position_, 3, 0);
        std::fill_n(direction_, 3, 0);
        radius_ = 1;
        speed_ = 30;
    }
    void Drone::SetOrder(csci3081::Order* order) {
        order_ = order;
        entity_project::SimpleUMNRoutePoint src(position_[0], position_[1], position_[2]);
        entity_project::SimpleUMNRoutePoint dst(order->GetPackage()->GetPosition()[0],
            order->GetPackage()->GetPosition()[1], order->GetPackage()->GetPosition()[2]);
        SetRoute(routeManager_.GetRoute(src, dst));
    }
    csci3081::Order* Drone::GetOrder() {
        return order_;
    }
    csci3081::Package* Drone::GetPackage() {
        return package_;
    }
    std::vector<entity_project::SimpleUMNRoutePoint>& Drone::GetRoute() {
        return route_;
    }
    void Drone::SetRoute(const std::vector<entity_project::SimpleUMNRoutePoint>& route) {
        route_ = route;
        routeIter_ = route_.begin();
    }
    void Drone::Update(float dt) {
        if (order_ != nullptr) {
            // First check to see if the drone is close enough to drop off or pick up a package
            if (package_ == nullptr) {
                Package* package = order_->GetPackage();
                float packageDist = Dist(position_[0], position_[1], position_[2],
                    package->GetPosition()[0], package->GetPosition()[1],
                    package->GetPosition()[2]);
                if (packageDist <= radius_ + package->GetRadius()) {
                    package_ = package;
                    package_->SetDrone(this);

                    // Notify package observers that the package is en route
                    picojson::object packageEvent;
                    packageEvent["type"] = picojson::value("notify");
                    packageEvent["value"] = picojson::value("en route");
                    package_->NotifyObservers(picojson::value(packageEvent));

                    // Notify drone observers that the drone is delivering a package
                    picojson::object droneEvent;
                    droneEvent["type"] = picojson::value("notify");
                    droneEvent["value"] = picojson::value("delivering");
                    NotifyObservers(picojson::value(droneEvent));

                    entity_project::SimpleUMNRoutePoint src(position_[0], position_[1],
                        position_[2]);
                    entity_project::SimpleUMNRoutePoint dst(order_->GetCustomer()->GetPosition()[0],
                        order_->GetCustomer()->GetPosition()[1],
                        order_->GetCustomer()->GetPosition()[2]);
                    SetRoute(routeManager_.GetRoute(src, dst));
                }
            } else {
                Customer* customer = order_->GetCustomer();
                float customerDist = Dist(position_[0], position_[1], position_[2],
                    customer->GetPosition()[0], customer->GetPosition()[1],
                    customer->GetPosition()[2]);
                if (customerDist <= radius_ + customer->GetRadius()) {
                    order_->GetPackage()->SetDrone(nullptr);
                    order_->GetPackage()->SetDynamic(false);
                    order_->GetCustomer()->SetDynamic(false);
                    delete order_;
                    order_ = nullptr;

                    // Notify package, drone and customer observers
                    // that the package has been delivered
                    picojson::object packageEvent;
                    packageEvent["type"] = picojson::value("notify");
                    packageEvent["value"] = picojson::value("delivered");
                    package_->NotifyObservers(picojson::value(packageEvent));
                    NotifyObservers(picojson::value(packageEvent));
                    package_ = nullptr;
                    return;  // We don't need to update our position, we are done
                }
            }

            // Now we will update the drone's position
            if (route_.size() != 0 && routeIter_ != route_.end()) {
                float displacement = speed_ * dt;
                while (routeIter_ != route_.end()) {
                    const entity_project::SimpleUMNRoutePoint& routePoint = *routeIter_;
                    float pointDist = Dist(position_[0], position_[1], position_[2],
                        routePoint.x, routePoint.y, routePoint.z);
                    if (pointDist <= displacement) {
                        routeIter_++;

                        position_[0] = routePoint.x;
                        position_[1] = routePoint.y;
                        position_[2] = routePoint.z;

                        displacement -= pointDist;
                    } else {
                        std::tuple<float, float, float> facingDirection = Direction(
                            position_[0], position_[1], position_[2],
                            routePoint.x, routePoint.y, routePoint.z);

                        direction_[0] = std::get<0>(facingDirection);
                        direction_[1] = std::get<1>(facingDirection);
                        direction_[2] = std::get<2>(facingDirection);

                        position_[0] += direction_[0] * displacement;
                        position_[1] += direction_[1] * displacement;
                        position_[2] += direction_[2] * displacement;
                        break;
                    }
                }
                // Notify drone observers that the drone has moved
                // picojson::object droneEvent;
                // droneEvent["type"] = picojson::value("movement");
                // NotifyObservers(picojson::value(droneEvent));
                if (package_ != nullptr)
                    package_->Update(dt);
            } else {
                float displacement = speed_ * dt;
                if (package_ == nullptr) {
                    Package* package = order_->GetPackage();
                    float packageDist = Dist(position_[0], position_[1], position_[2],
                        package->GetPosition()[0], package->GetPosition()[1],
                        package->GetPosition()[2]);
                    if (packageDist <= displacement) {
                        position_[0] = package->GetPosition()[0];
                        position_[1] = package->GetPosition()[1];
                        position_[2] = package->GetPosition()[2];
                    } else {
                        std::tuple<float, float, float> facingDirection = Direction(
                            position_[0], position_[1], position_[2],
                            package->GetPosition()[0], package->GetPosition()[1],
                            package->GetPosition()[2]);

                        direction_[0] = std::get<0>(facingDirection);
                        direction_[1] = std::get<1>(facingDirection);
                        direction_[2] = std::get<2>(facingDirection);

                        position_[0] += direction_[0] * displacement;
                        position_[1] += direction_[1] * displacement;
                        position_[2] += direction_[2] * displacement;
                    }
                } else {
                    Customer* customer = order_->GetCustomer();
                    float customerDist = Dist(position_[0], position_[1], position_[2],
                        customer->GetPosition()[0], customer->GetPosition()[1],
                        customer->GetPosition()[2]);
                    if (customerDist <= displacement) {
                        position_[0] = customer->GetPosition()[0];
                        position_[1] = customer->GetPosition()[1];
                        position_[2] = customer->GetPosition()[2];
                    } else {
                        std::tuple<float, float, float> facingDirection = Direction(
                            position_[0], position_[1], position_[2],
                            customer->GetPosition()[0], customer->GetPosition()[1],
                            customer->GetPosition()[2]);

                        direction_[0] = std::get<0>(facingDirection);
                        direction_[1] = std::get<1>(facingDirection);
                        direction_[2] = std::get<2>(facingDirection);

                        position_[0] += direction_[0] * displacement;
                        position_[1] += direction_[1] * displacement;
                        position_[2] += direction_[2] * displacement;
                    }
                }
            }
        }
    }
}  // namespace csci3081
