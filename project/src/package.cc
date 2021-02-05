#include "package.h"  // NOLINT
#include "drone.h"  // NOLINT

namespace csci3081 {
    Package::Package(const std::string& name, const picojson::array& position,
      const picojson::array& direction, float radius, const picojson::object& object)
      : EntityObservable(*static_cast<Entity*>(this)), drone_(nullptr), dynamic_(false) {
        AddType<Package>();
        name_ = name;
        std::fill_n(position_, 3, 0);
        std::fill_n(direction_, 3, 0);
        for (int i = 0; i < position.size() && i < 3 && position[i].is<double>(); i++) {
            position_[i] = position[i].get<double>();
        }
        for (int i = 0; i < direction.size() && i < 3 && direction[i].is<double>(); i++) {
            direction_[i] = direction[i].get<double>();
        }
        radius_ = radius;
        details_ = object;
    }

    Package::Package() : EntityObservable(*static_cast<Entity*>(this)), dynamic_(false) {
        AddType<Package>();
        std::fill_n(position_, 3, 0);
        std::fill_n(direction_, 3, 0);
        radius_ = 1.0;
    }

    void Package::SetDrone(Drone* drone) {
        drone_ = drone;
    }
    void Package::Update(float dt) {
        if (drone_ != nullptr) {
            position_[0] = drone_->GetPosition()[0];
            position_[1] = drone_->GetPosition()[1];
            position_[2] = drone_->GetPosition()[2];

            direction_[0] = drone_->GetPosition()[0];
            direction_[1] = drone_->GetPosition()[1];
            direction_[2] = drone_->GetPosition()[2];
        }
    }
}  // namespace csci3081
