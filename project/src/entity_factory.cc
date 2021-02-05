#include "entity_factory.h" // NOLINT

namespace csci3081 {
    entity_project::Entity* EntityFactory::CreateEntity(const picojson::object& object) {
        auto type = object.find("type");
        const std::string& typeStr = (type != object.end() && type->second.is<std::string>())
            ? type->second.get<std::string>() : "";
        auto name = object.find("name");
        const std::string& nameStr = (name != object.end() && name->second.is<std::string>())
            ? name->second.get<std::string>() : "";
        auto position = object.find("position");
        const picojson::array& positionVec = (position != object.end() &&
            position->second.is<picojson::array>())
            ? position->second.get<picojson::array>() : picojson::array();
        auto direction = object.find("direction");
        const picojson::array& directionVec = (direction != object.end() &&
            direction->second.is<picojson::array>())
            ? direction->second.get<picojson::array>() : picojson::array();
        auto radius = object.find("radius");
        float radiusVal = (radius != object.end() &&
            radius->second.is<double>()) ? radius->second.get<double>() : 1;
        if (typeStr == "drone") {
            auto speed = object.find("speed");
            float speedVal = (speed != object.end() && speed->second.is<double>()) ?
                speed->second.get<double>() : 30;
            Drone* drone = new Drone(nameStr, positionVec, directionVec,
                speedVal, radiusVal, object);
            return drone;
        } else if (typeStr == "customer") {
            Customer* customer = new Customer(nameStr, positionVec, directionVec,
                radiusVal, object);
            return customer;
        } else if (typeStr == "package") {
            Package* package = new Package(nameStr, positionVec, directionVec,
                radiusVal, object);
            return package;
        } else {
            return nullptr;
        }
    }
}  // namespace csci3081
