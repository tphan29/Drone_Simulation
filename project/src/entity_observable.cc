#include "entity_observable.h"  // NOLINT

namespace csci3081 {
    EntityObservable::EntityObservable(const entity_project::Entity& entity)
        : entity_(entity) {}
    EntityObservable::~EntityObservable() {}
    void EntityObservable::AddObserver(entity_project::EntityObserver* observer) {
        observers_.insert(observer);
    }
    void EntityObservable::RemoveObserver(entity_project::EntityObserver* observer) {
        observers_.erase(observer);
    }
    void EntityObservable::NotifyObservers(const picojson::value& event) {
        for (entity_project::EntityObserver* observer : observers_)
            observer->OnEvent(event, entity_);
    }
}  // namespace csci3081
