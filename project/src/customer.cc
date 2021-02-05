#include "customer.h"  // NOLINT

namespace csci3081 {
    Customer::Customer(const std::string& name, const picojson::array& position,
        const picojson::array& direction, float radius, const picojson::object& object)
        : EntityObservable(*static_cast<Entity*>(this)), dynamic_(false) {
        AddType<Customer>();
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

    Customer::Customer() : EntityObservable(*static_cast<Entity*>(this)), dynamic_(false) {
        AddType<Customer>();
        std::fill_n(position_, 3, 0);
        std::fill_n(direction_, 3, 0);
        radius_ = 1.0;
    }

    void Customer::Update(float dt) {}
}  // namespace csci3081
