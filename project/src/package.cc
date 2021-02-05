#include "package.h"  // NOLINT
#include "drone.h"  // NOLINT
#include "customer.h"  // NOLINT

namespace csci3081 {
    Package::Package(const std::string& name, const picojson::array& position,
        const picojson::array& direction, float radius, const picojson::object& object,
        float weight) : EntityObservable(*static_cast<Entity*>(this)), drone_(nullptr),
        customer_(nullptr), dynamic_(false), weight_(weight) {
        AddType<Package>();
        if (!name.empty()) {
            name_ = name;
        } else {
            name_ = "package";
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

    Package::Package() : EntityObservable(*static_cast<Entity*>(this)), dynamic_(false),
        weight_(0) {
        AddType<Package>();
        radius_ = 1.0;
        name_ = "package";
        while (position_.size() < 3) {
            position_.push_back(0);
        }
        while (direction_.size() < 3) {
            direction_.push_back(0);
        }
        std::fill_n(position_.begin(), 3, 0);
        std::fill_n(direction_.begin(), 3, 0);
    }

    void Package::Update(float dt) {
        if (drone_ != nullptr) {
            position_[0] = drone_->GetPosition()[0];
            position_[1] = drone_->GetPosition()[1];
            position_[2] = drone_->GetPosition()[2];

            direction_[0] = drone_->GetDirection()[0];
            direction_[1] = drone_->GetDirection()[1];
            direction_[2] = drone_->GetDirection()[2];
        }
    }
}  // namespace csci3081
