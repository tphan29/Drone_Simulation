#include "drone.h"  // NOLINT
#include "customer.h"  // NOLINT

namespace csci3081 {
    Drone::Drone(const std::string& name, const picojson::array& position,
        const picojson::array& direction, float speed, float radius,
        const picojson::object& object) : EntityObservable(*static_cast<Entity*>(this)),
        maxSpeed_(speed), physicsModel_(VELOCITY), baseBatteryCapacity_(300), currentSpeed_(0),
        remainingBattery_(baseBatteryCapacity_), weightCapacity_(10) {
        AddType<Drone>();
        if (!name.empty()) {
            name_ = name;
        } else {
            name_ = "drone";
        }
        radius_ = radius;
        details_ = object;
        while (position_.size() < 3) {
            position_.push_back(0);
        }
        while (direction_.size() < 3) {
            direction_.push_back(0);
        }
        std::fill_n(position_.begin(), 3, 0);
        std::fill_n(direction_.begin(), 3, 0);
        for (int i = 0; i < position.size() && i < 3 && position[i].is<double>(); i++) {
            position_[i] = position[i].get<double>();
        }
        for (int i = 0; i < direction.size() && i < 3 && direction[i].is<double>(); i++) {
            direction_[i] = direction[i].get<double>();
        }
    }

    Drone::Drone(const std::string& name, const picojson::array& position,
        const picojson::array& direction, float radius,
        const DroneAttributes& droneAttributes, PhysicsModel physicsModel,
        const picojson::object& object) : EntityObservable(*static_cast<Entity*>(this)),
        mass_(droneAttributes.mass), maxSpeed_(droneAttributes.maxSpeed),
        baseAcceleration_(droneAttributes.baseAcceleration),
        weightCapacity_(droneAttributes.weightCapacity),
        baseBatteryCapacity_(droneAttributes.baseBatteryCapacity), currentSpeed_(0),
        remainingCapacity_(weightCapacity_), remainingBattery_(baseBatteryCapacity_),
        physicsModel_(physicsModel) {
        AddType<Drone>();
        if (!name.empty()) {
            name_ = name;
        } else {
            name_ = "drone";
        }
        radius_ = radius;
        details_ = object;
        while (position_.size() < 3) {
            position_.push_back(0);
        }
        while (direction_.size() < 3) {
            direction_.push_back(0);
        }
        std::fill_n(position_.begin(), 3, 0);
        std::fill_n(direction_.begin(), 3, 0);
        for (int i = 0; i < position.size() && i < 3 && position[i].is<double>(); i++) {
            position_[i] = position[i].get<double>();
        }
        for (int i = 0; i < direction.size() && i < 3 && direction[i].is<double>(); i++) {
            direction_[i] = direction[i].get<double>();
        }
    }
    Drone::Drone() : EntityObservable(*static_cast<Entity*>(this)), mass_(50), maxSpeed_(30),
        baseAcceleration_(4), weightCapacity_(10), baseBatteryCapacity_(100000), currentSpeed_(0),
        remainingCapacity_(weightCapacity_), remainingBattery_(baseBatteryCapacity_),
        physicsModel_(VELOCITY) {
        AddType<Drone>();
        radius_ = 1;
        name_ = "drone";
        while (position_.size() < 3) {
            position_.push_back(0);
        }
        while (direction_.size() < 3) {
            direction_.push_back(0);
        }
        std::fill_n(position_.begin(), 3, 0);
        std::fill_n(direction_.begin(), 3, 0);
    }
    void Drone::AddPackage(csci3081::Package* package) {
        pendingPackages_.push_back(package);
        if (pendingPackages_.size() == 1) {
            std::tuple<float, float, float> src(position_[0], position_[1], position_[2]);
            std::tuple<float, float, float> dest(package->GetPosition()[0],
                package->GetPosition()[1], package->GetPosition()[2]);
            SetRoute(RouteManager::GetRoute(src, dest));
        }
    }

    bool Drone::CanDeliverPackage(csci3081::Package* package) {
        float remaining = weightCapacity_;
        for (auto p : pendingPackages_) {
            remaining -= p->GetWeight();
        }
        for (auto p : carriedPackages_) {
            remaining -= p->GetWeight();
        }
        remaining -= package->GetWeight();
        return remaining >= 0;
    }
    const std::vector<const entity_project::IGraphNode*>& Drone::GetRoute() {
        return route_;
    }
    void Drone::SetRoute(const std::vector<const entity_project::IGraphNode*>& route) {
        route_ = route;
        routeIter_ = route_.begin();
        // notifying that the drone is moving
        // didn't want to do this in update because it would send an alert
        // everytime drone changed position
        picojson::object droneEvent;
        droneEvent["type"] = picojson::value("notify");
        droneEvent["value"] = picojson::value("moving");
        picojson::array obsRoute;
        currentRoute_.clear();
        for (auto p : route_) {
            currentRoute_.push_back(p->GetName());
            std::vector<picojson::value> routePoint;
            routePoint.push_back(picojson::value(p->GetPosition()[0]));
            routePoint.push_back(picojson::value(p->GetPosition()[1]));
            routePoint.push_back(picojson::value(p->GetPosition()[2]));
            obsRoute.push_back(picojson::value(routePoint));
        }
        droneEvent["path"] = picojson::value(obsRoute);
        NotifyObservers(picojson::value(droneEvent));
    }
    void Drone::Update(float dt) {
        if (remainingBattery_ == 0)
            return;

        while (true) {
            if (!pendingPackages_.empty()) {
                csci3081::Package* package = *pendingPackages_.begin();
                float packageDist = Dist(position_[0], position_[1], position_[2],
                    package->GetPosition()[0], package->GetPosition()[1],
                    package->GetPosition()[2]);
                if (packageDist <= radius_ + package->GetRadius()) {
                    package->SetDrone(this);
                    carriedPackages_.push_back(package);
                    pendingPackages_.erase(pendingPackages_.begin());

                    // Notify package observers that the package is en route
                    picojson::object packageEvent;
                    packageEvent["type"] = picojson::value("notify");
                    packageEvent["value"] = picojson::value("en route");
                    package->NotifyObservers(picojson::value(packageEvent));

                    if (pendingPackages_.empty()) {
                        csci3081::Customer* cust = (*carriedPackages_.begin())->GetCustomer();
                        std::tuple<float, float, float> src(position_[0], position_[1],
                            position_[2]);
                        std::tuple<float, float, float> dest(cust->GetPosition()[0],
                            cust->GetPosition()[1], cust->GetPosition()[2]);
                        SetRoute(RouteManager::GetRoute(src, dest));
                    } else {
                        csci3081::Package* pkg = *pendingPackages_.begin();
                        std::tuple<float, float, float> src(position_[0], position_[1],
                            position_[2]);
                        std::tuple<float, float, float> dest(pkg->GetPosition()[0],
                            pkg->GetPosition()[1], pkg->GetPosition()[2]);
                        SetRoute(RouteManager::GetRoute(src, dest));
                    }
                } else {
                    break;
                }
            } else if (!carriedPackages_.empty()) {
                csci3081::Customer* customer = (*carriedPackages_.begin())->GetCustomer();
                float customerDist = Dist(position_[0], position_[1], position_[2],
                    customer->GetPosition()[0], customer->GetPosition()[1],
                    customer->GetPosition()[2]);
                if (customerDist <= radius_ + customer->GetRadius()) {
                    (*carriedPackages_.begin())->SetDrone(nullptr);
                    (*carriedPackages_.begin())->SetDynamic(false);
                    (*carriedPackages_.begin())->GetCustomer()->SetDynamic(false);

                    // Notify package, drone and customer observers
                    // that the package has been delivered
                    picojson::object packageEvent;
                    packageEvent["type"] = picojson::value("notify");
                    packageEvent["value"] = picojson::value("delivered");
                    (*carriedPackages_.begin())->NotifyObservers(picojson::value(packageEvent));

                    carriedPackages_.erase(carriedPackages_.begin());
                    deliveredPackages_.push_back(*carriedPackages_.begin());

                    if (!carriedPackages_.empty()) {
                        csci3081::Customer* cust = (*carriedPackages_.begin())->GetCustomer();
                        std::tuple<float, float, float> src(position_[0], position_[1],
                            position_[2]);
                        std::tuple<float, float, float> dest(cust->GetPosition()[0],
                            cust->GetPosition()[1], cust->GetPosition()[2]);
                        SetRoute(RouteManager::GetRoute(src, dest));
                    } else {
                        picojson::object idleEvent;
                        idleEvent["type"] = picojson::value("notify");
                        idleEvent["value"] = picojson::value("idle");
                        NotifyObservers(picojson::value(idleEvent));
                        return;
                    }
                } else {
                    break;
                }
            } else {
                return;
            }
        }

        remainingBattery_ -= dt;
        if (remainingBattery_ <= 0) {
            remainingBattery_ = 0;

            picojson::object idleEvent;
            idleEvent["type"] = picojson::value("notify");
            idleEvent["value"] = picojson::value("idle");
            NotifyObservers(picojson::value(idleEvent));

            return;
        }
        // Now we will update the drone's position
        switch (physicsModel_) {
            default:  // Use velocity if for some reason physicsModel_ is not set
            case VELOCITY: {
                if (route_.size() != 0 && routeIter_ != route_.end()) {
                    float displacement = maxSpeed_ * dt;
                    while (routeIter_ != route_.end()) {
                        const entity_project::IGraphNode* routePoint = *routeIter_;
                        float pointDist = Dist(position_[0], position_[1], position_[2],
                            routePoint->GetPosition()[0], routePoint->GetPosition()[1],
                            routePoint->GetPosition()[2]);
                        if (pointDist <= displacement) {
                            routeIter_++;

                            position_[0] = routePoint->GetPosition()[0];
                            position_[1] = routePoint->GetPosition()[1];
                            position_[2] = routePoint->GetPosition()[2];

                            displacement -= pointDist;
                        } else {
                            std::tuple<float, float, float> facingDirection = Direction(
                                position_[0], position_[1], position_[2],
                                routePoint->GetPosition()[0], routePoint->GetPosition()[1],
                                routePoint->GetPosition()[2]);

                            direction_[0] = std::get<0>(facingDirection);
                            direction_[1] = std::get<1>(facingDirection);
                            direction_[2] = std::get<2>(facingDirection);

                            position_[0] += direction_[0] * displacement;
                            position_[1] += direction_[1] * displacement;
                            position_[2] += direction_[2] * displacement;
                            break;
                        }
                    }
                } else {
                    float displacement = maxSpeed_ * dt;
                    if (!pendingPackages_.empty()) {
                        Package* package = *pendingPackages_.begin();
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
                    } else if (!carriedPackages_.empty()) {
                        Customer* customer = (*carriedPackages_.begin())->GetCustomer();
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
                    } else {
                        return;
                    }
                }
                for (auto p : carriedPackages_) {
                    p->Update(dt);
                }
                return;
            }
            case ACCELERATION: {
                while (route_.size() != 0 && routeIter_ != route_.end()) {
                    const entity_project::IGraphNode* routePoint = *routeIter_;
                    float distance = Dist(position_[0], position_[1], position_[2],
                        routePoint->GetPosition()[0], routePoint->GetPosition()[1],
                        routePoint->GetPosition()[2]);
                    // Check if we are close enough to the next point to advance the route iterator
                    if (distance < maxSpeed_ * dt) {
                        routeIter_++;
                    } else {
                        break;
                    }
                }
                if (route_.size() != 0 && routeIter_ != route_.end()) {
                    const entity_project::IGraphNode* routePoint = *routeIter_;
                    // Get target direction vector that points from our drone to the next point
                    std::tuple<float, float, float> targetDirection = Direction(position_[0],
                        position_[1], position_[2], routePoint->GetPosition()[0],
                        routePoint->GetPosition()[1], routePoint->GetPosition()[2]);

                    std::tuple<float, float, float> velocity(direction_[0] * currentSpeed_,
                        direction_[1] * currentSpeed_, direction_[2] * currentSpeed_);

                    // Velocity = Velocity + direction * acceleration * dt
                    std::get<0>(velocity) += std::get<0>(targetDirection) * baseAcceleration_ * dt;
                    std::get<1>(velocity) += std::get<1>(targetDirection) * baseAcceleration_ * dt;
                    std::get<2>(velocity) += std::get<2>(targetDirection) * baseAcceleration_ * dt;

                    // Get the speed and cap it at maxSpeed_
                    float currentSpeed_ = Norm(std::get<0>(velocity), std::get<1>(velocity),
                        std::get<2>(velocity));
                    // Check if the speed is greater than maxSpeed_
                    // If it is change the speed to maxSpeed_
                    if (currentSpeed_ > maxSpeed_) {
                        std::get<0>(velocity) *= (maxSpeed_ / currentSpeed_);
                        std::get<1>(velocity) *= (maxSpeed_ / currentSpeed_);
                        std::get<2>(velocity) *= (maxSpeed_ / currentSpeed_);
                        currentSpeed_ = maxSpeed_;
                    }
                    position_[0] += std::get<0>(velocity) * dt;
                    position_[1] += std::get<1>(velocity) * dt;
                    position_[2] += std::get<2>(velocity) * dt;

                    direction_[0] = std::get<0>(velocity) / currentSpeed_;
                    direction_[1] = std::get<1>(velocity) / currentSpeed_;
                    direction_[2] = std::get<2>(velocity) / currentSpeed_;
                } else {
                    if (!pendingPackages_.empty() || !carriedPackages_.empty()) {
                        std::tuple<float, float, float> targetDirection;
                        if (!pendingPackages_.empty()) {
                            targetDirection = Direction(position_[0],
                                position_[1], position_[2],
                                (*pendingPackages_.begin())->GetPosition()[0],
                                (*pendingPackages_.begin())->GetPosition()[1],
                                (*pendingPackages_.begin())->GetPosition()[2]);
                        } else {
                            targetDirection = Direction(position_[0],
                                position_[1], position_[2],
                                (*carriedPackages_.begin())->GetCustomer()->GetPosition()[0],
                                (*carriedPackages_.begin())->GetCustomer()->GetPosition()[1],
                                (*carriedPackages_.begin())->GetCustomer()->GetPosition()[2]);
                        }
                        std::tuple<float, float, float> velocity(direction_[0] * currentSpeed_,
                            direction_[1] * currentSpeed_, direction_[2] * currentSpeed_);

                        // Velocity = Velocity + direction * acceleration * dt
                        std::get<0>(velocity) += std::get<0>(targetDirection)
                            * baseAcceleration_ * dt;
                        std::get<1>(velocity) += std::get<1>(targetDirection)
                            * baseAcceleration_ * dt;
                        std::get<2>(velocity) += std::get<2>(targetDirection)
                            * baseAcceleration_ * dt;

                        // Get the speed and cap it at maxSpeed_
                        float currentSpeed_ = Norm(std::get<0>(velocity), std::get<1>(velocity),
                            std::get<2>(velocity));
                        // Check if the speed is greater than maxSpeed_
                        // If it is change the speed to maxSpeed_
                        if (currentSpeed_ > maxSpeed_) {
                            std::get<0>(velocity) *= (maxSpeed_ / currentSpeed_);
                            std::get<1>(velocity) *= (maxSpeed_ / currentSpeed_);
                            std::get<2>(velocity) *= (maxSpeed_ / currentSpeed_);
                            currentSpeed_ = maxSpeed_;
                        }
                        position_[0] += std::get<0>(velocity) * dt;
                        position_[1] += std::get<1>(velocity) * dt;
                        position_[2] += std::get<2>(velocity) * dt;

                        direction_[0] = std::get<0>(velocity) / currentSpeed_;
                        direction_[1] = std::get<1>(velocity) / currentSpeed_;
                        direction_[2] = std::get<2>(velocity) / currentSpeed_;
                    } else {
                        if (currentSpeed_ < baseAcceleration_) {
                            currentSpeed_ = 0;
                        } else {
                            currentSpeed_ -= baseAcceleration_;
                            std::tuple<float, float, float> velocity(direction_[0] * currentSpeed_,
                                direction_[1] * currentSpeed_, direction_[2] * currentSpeed_);

                            position_[0] += std::get<0>(velocity) * dt;
                            position_[1] += std::get<1>(velocity) * dt;
                            position_[2] += std::get<2>(velocity) * dt;
                        }
                    }
                }
                for (auto p : carriedPackages_) {
                    p->Update(dt);
                }
                return;
            }
            case FORCE: {
                while (route_.size() != 0 && routeIter_ != route_.end()) {
                    const entity_project::IGraphNode* routePoint = *routeIter_;
                    float distance = Dist(position_[0], position_[1], position_[2],
                        routePoint->GetPosition()[0], routePoint->GetPosition()[1],
                        routePoint->GetPosition()[2]);
                    // Check if we are close enough to the next point to advance the route iterator
                    if (distance < maxSpeed_ * dt) {
                        routeIter_++;
                    } else {
                        break;
                    }
                }
                float droneForce = mass_ * baseAcceleration_;
                float totalMass = mass_;
                for (auto p : carriedPackages_) {
                    totalMass += p->GetWeight();
                }
                float adjustedAcceleration = droneForce / totalMass;
                if (route_.size() != 0 && routeIter_ != route_.end()) {
                    const entity_project::IGraphNode* routePoint = *routeIter_;
                    // Get target direction vector that points from our drone to the next point
                    std::tuple<float, float, float> targetDirection = Direction(position_[0],
                        position_[1], position_[2], routePoint->GetPosition()[0],
                        routePoint->GetPosition()[1], routePoint->GetPosition()[2]);

                    std::tuple<float, float, float> velocity(direction_[0] * currentSpeed_,
                        direction_[1] * currentSpeed_, direction_[2] * currentSpeed_);

                    // Velocity = Velocity + direction * acceleration * dt
                    std::get<0>(velocity) += std::get<0>(targetDirection)
                        * adjustedAcceleration * dt;
                    std::get<1>(velocity) += std::get<1>(targetDirection)
                        * adjustedAcceleration * dt;
                    std::get<2>(velocity) += std::get<2>(targetDirection)
                        * adjustedAcceleration * dt;

                    // Get the speed and cap it at maxSpeed_
                    currentSpeed_ = Norm(std::get<0>(velocity), std::get<1>(velocity),
                        std::get<2>(velocity));
                    // Check if the speed is greater than maxSpeed_
                    // If it is change the speed to maxSpeed_
                    if (currentSpeed_ > maxSpeed_) {
                        std::get<0>(velocity) *= (maxSpeed_ / currentSpeed_);
                        std::get<1>(velocity) *= (maxSpeed_ / currentSpeed_);
                        std::get<2>(velocity) *= (maxSpeed_ / currentSpeed_);
                        currentSpeed_ = maxSpeed_;
                    }
                    position_[0] += std::get<0>(velocity) * dt;
                    position_[1] += std::get<1>(velocity) * dt;
                    position_[2] += std::get<2>(velocity) * dt;

                    direction_[0] = std::get<0>(velocity) / currentSpeed_;
                    direction_[1] = std::get<1>(velocity) / currentSpeed_;
                    direction_[2] = std::get<2>(velocity) / currentSpeed_;
                } else {
                    if (!pendingPackages_.empty() || !carriedPackages_.empty()) {
                        std::tuple<float, float, float> targetDirection;
                        if (!pendingPackages_.empty()) {
                            targetDirection = Direction(position_[0],
                                position_[1], position_[2],
                                (*pendingPackages_.begin())->GetPosition()[0],
                                (*pendingPackages_.begin())->GetPosition()[1],
                                (*pendingPackages_.begin())->GetPosition()[2]);
                        } else {
                            targetDirection = Direction(position_[0],
                                position_[1], position_[2],
                                (*carriedPackages_.begin())->GetCustomer()->GetPosition()[0],
                                (*carriedPackages_.begin())->GetCustomer()->GetPosition()[1],
                                (*carriedPackages_.begin())->GetCustomer()->GetPosition()[2]);
                        }
                        std::tuple<float, float, float> velocity(direction_[0] * currentSpeed_,
                            direction_[1] * currentSpeed_, direction_[2] * currentSpeed_);

                        // Velocity = Velocity + direction * acceleration * dt
                        std::get<0>(velocity) += std::get<0>(targetDirection)
                            * adjustedAcceleration * dt;
                        std::get<1>(velocity) += std::get<1>(targetDirection)
                            * adjustedAcceleration * dt;
                        std::get<2>(velocity) += std::get<2>(targetDirection)
                            * adjustedAcceleration * dt;

                        // Get the speed and cap it at maxSpeed_
                        float currentSpeed_ = Norm(std::get<0>(velocity), std::get<1>(velocity),
                            std::get<2>(velocity));
                        // Check if the speed is greater than maxSpeed_
                        // If it is change the speed to maxSpeed_
                        if (currentSpeed_ > maxSpeed_) {
                            std::get<0>(velocity) *= (maxSpeed_ / currentSpeed_);
                            std::get<1>(velocity) *= (maxSpeed_ / currentSpeed_);
                            std::get<2>(velocity) *= (maxSpeed_ / currentSpeed_);
                            currentSpeed_ = maxSpeed_;
                        }
                        position_[0] += std::get<0>(velocity) * dt;
                        position_[1] += std::get<1>(velocity) * dt;
                        position_[2] += std::get<2>(velocity) * dt;

                        direction_[0] = std::get<0>(velocity) / currentSpeed_;
                        direction_[1] = std::get<1>(velocity) / currentSpeed_;
                        direction_[2] = std::get<2>(velocity) / currentSpeed_;
                    } else {
                        if (currentSpeed_ < adjustedAcceleration) {
                            currentSpeed_ = 0;
                        } else {
                            currentSpeed_ -= adjustedAcceleration;
                            std::tuple<float, float, float> velocity(direction_[0] * currentSpeed_,
                                direction_[1] * currentSpeed_, direction_[2] * currentSpeed_);

                            position_[0] += std::get<0>(velocity) * dt;
                            position_[1] += std::get<1>(velocity) * dt;
                            position_[2] += std::get<2>(velocity) * dt;
                        }
                    }
                }
                return;
            }
        }
    }
}  // namespace csci3081
