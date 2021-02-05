#ifndef OBSERVABLE_H_
#define OBSERVABLE_H_

#include <EntityProject/entity.h>
#include <EntityProject/entity_observer.h>

#include <unordered_set>

namespace csci3081 {
/// Entities that inherit from this class become observable
/**
 * The EntityObservable class serves as a class that is meant to be inherited from if an Entity wishes
 * to be observable by entity_project::EntityObserver objects. 
 */
class EntityObservable {
 public:
    /**
     * Constructs an EntityObservable object with an associated entity.
     * @param entity const reference to the associated entity
     */
    explicit EntityObservable(const entity_project::Entity& entity);
    /**
     * Pure virtual destructor to prevent the EntityObservable
     * class from being instantiated by itself.
     */
    virtual ~EntityObservable() = 0;
    /**
     * Attaches an observer to the entity.
     * @param observer pointer to the entity_project::EntityObserver to be added
     */ 
    void AddObserver(entity_project::EntityObserver* observer);
    /**
     * Detaches an observer from the entity.
     * @param observer pointer to the entity_project::EntityObserver to be removed
     */ 
    void RemoveObserver(entity_project::EntityObserver* observer);
    /**
     * Notifies all attached observers of an event.
     * @param event JSON data of the event
     */
    void NotifyObservers(const picojson::value& event);

 private:
    std::unordered_set<entity_project::EntityObserver*> observers_;
    const entity_project::Entity& entity_;
};

}  // namespace csci3081
#endif
