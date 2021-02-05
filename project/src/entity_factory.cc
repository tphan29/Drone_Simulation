#include "entity_factory.h" // NOLINT

namespace csci3081 {
    EntityFactory::EntityFactory() {}

    entity_project::Entity* EntityFactory::CreateEntity(const picojson::object& object) {
        droneAttributesMap_.clear();
        std::ifstream droneFile("data/planet-x.csv");
        if (!droneFile.is_open()) {
            std::cout << "[Error] Unable to open data/planet-x.csv" << std::endl;
        }
        if (!droneFile.good()) {
            std::cout << "[Error] Unable to read from data/planet-x.csv" << std::endl;
        }

        std::string line;
        std::getline(droneFile, line);  // Read first line

        std::string fieldName;
        std::vector<std::string> fields;
        std::stringstream fieldStream(line);

        while (std::getline(fieldStream, fieldName, ','))
            fields.push_back(fieldName);

        std::string modelNumber;
        std::string massStr;
        std::string maxSpeedStr;
        std::string baseAccelerationStr;
        std::string weightCapacityStr;
        std::string baseBatteryCapacityStr;

        auto fieldIterator = fields.begin();

        while (std::getline(droneFile, line)) {
            std::stringstream stringStream(line);

            modelNumber.clear();
            massStr.clear();
            maxSpeedStr.clear();
            baseAccelerationStr.clear();
            weightCapacityStr.clear();
            baseBatteryCapacityStr.clear();

            fieldIterator = fields.begin();
            std::string fieldValue;
            while (std::getline(stringStream, fieldValue, ',') && fieldIterator != fields.end()) {
                if (*fieldIterator == "Model #") {
                    modelNumber = fieldValue;
                } else if (*fieldIterator == "Mass (kg)") {
                    massStr = fieldValue;
                } else if (*fieldIterator == "Max Speed (km/h)") {
                    maxSpeedStr = fieldValue;
                } else if (*fieldIterator == "Base Acceleration (m/s^2)") {
                    baseAccelerationStr = fieldValue;
                } else if (*fieldIterator == "WeightCapacity (kg)") {
                    weightCapacityStr = fieldValue;
                } else if (*fieldIterator == "Base Battery Capacity (seconds)") {
                    baseBatteryCapacityStr = fieldValue;
                }
                fieldIterator++;
            }

            float mass = 0;
            float maxSpeed = 0;
            float baseAcceleration = 0;
            float weightCapacity = 0;
            float baseBatteryCapacity = 0;

            try {
                mass = std::stof(massStr);
                maxSpeed = std::stof(maxSpeedStr) * (1000.0f / 3600.0f);
                baseAcceleration = std::stof(baseAccelerationStr);
                weightCapacity = std::stof(weightCapacityStr);
                baseBatteryCapacity = std::stof(baseBatteryCapacityStr);

                if (!modelNumber.empty()) {
                    if (droneAttributesMap_.find(modelNumber) == droneAttributesMap_.end()) {
                        droneAttributesMap_.insert({modelNumber, {mass, maxSpeed, baseAcceleration,
                            weightCapacity, baseBatteryCapacity}});
                    }
                }
            } catch(...) {}
        }

        droneFile.close();

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
            auto model = object.find("model");
            const DroneAttributes& droneAttributes = (model != object.end() &&
                model->second.is<std::string>() && droneAttributesMap_.find(
                model->second.get<std::string>()) != droneAttributesMap_.end())
                ? droneAttributesMap_.find(model->second.get<std::string>())->second :
                DroneAttributes({50, speedVal, 4, 10, 30000});
            Drone::PhysicsModel dronePhysicsModel;
            auto physicsModel = object.find("physics-model");
            if (physicsModel != object.end() && physicsModel->second.is<std::string>()) {
                if (physicsModel->second.get<std::string>() == "acceleration") {
                    dronePhysicsModel = Drone::ACCELERATION;
                } else if (physicsModel->second.get<std::string>() == "force") {
                    dronePhysicsModel = Drone::FORCE;
                } else {
                    dronePhysicsModel = Drone::VELOCITY;
                }
            } else {
                dronePhysicsModel = Drone::VELOCITY;
            }
            Drone* drone = new Drone(nameStr, positionVec, directionVec,
                radiusVal, droneAttributes, dronePhysicsModel, object);
            return drone;
        } else if (typeStr == "customer") {
            Customer* customer = new Customer(nameStr, positionVec, directionVec,
                radiusVal, object);
            return customer;
        } else if (typeStr == "package") {
            auto weight = object.find("weight");
            float weightVal = (weight != object.end() && weight->second.is<double>()) ?
                weight->second.get<double>() : 0;
            Package* package = new Package(nameStr, positionVec, directionVec,
                radiusVal, object, weightVal);
            return package;
        } else {
            return nullptr;
        }
    }
}  // namespace csci3081
