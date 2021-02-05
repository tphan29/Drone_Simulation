#include "customer.h"  // NOLINT

namespace csci3081 {
    Customer::Customer(const std::string& name, const picojson::array& position,
        const picojson::array& direction, float radius, const picojson::object& object)
        : EntityObservable(*static_cast<Entity*>(this)), dynamic_(false) {
        AddType<Customer>();
        if (!name.empty()) {
            name_ = name;
        } else {
            name_ = "customer";
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

    Customer::Customer() : EntityObservable(*static_cast<Entity*>(this)), dynamic_(false) {
        AddType<Customer>();
        radius_ = 1.0;
        name_ = "customer";
        while (position_.size() < 3) {
            position_.push_back(0);
        }
        while (direction_.size() < 3) {
            direction_.push_back(0);
        }
        std::fill_n(position_.begin(), 3, 0);
        std::fill_n(direction_.begin(), 3, 0);
    }

    void Customer::Update(float dt) {}
}  // namespace csci3081
