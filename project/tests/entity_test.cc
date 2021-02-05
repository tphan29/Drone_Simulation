#include "gtest/gtest.h"
#include <EntityProject/ANVIL2/drone_delivery_system.h>
#include <EntityProject/ANVIL2/drone.h>
#include <EntityProject/project_settings.h>
#include <picojson.h>

#include "../src/drone.h"  // NOLINT
#include "../src/customer.h"  // NOLINT
#include "../src/package.h"  // NOLINT

#include <iostream>
#include <unordered_set>

namespace csci3081 {

using entity_project::DroneDeliverySystem;
using entity_project::Entity;

class EntityTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    system = GetDroneDeliverySystem("default");
  }
  virtual void TearDown() {}

  DroneDeliverySystem* system;
};
/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(EntityTest, GetEntityId) {
    int n_each = 150;  // Number of each entity
    for (int i = 0; i < n_each; i++) {
        picojson::object obj;
        obj["type"] = picojson::value("drone");
        Entity* entity = system->CreateEntity(obj);
        system->AddEntity(entity);
    }
    for (int i = 0; i < n_each; i++) {
        picojson::object obj;
        obj["type"] = picojson::value("customer");
        Entity* entity = system->CreateEntity(obj);
        system->AddEntity(entity);
    }
    for (int i = 0; i < n_each; i++) {
        picojson::object obj;
        obj["type"] = picojson::value("package");
        Entity* entity = system->CreateEntity(obj);
        system->AddEntity(entity);
    }

    std::unordered_set<int> entityIds;
    ASSERT_EQ(system->GetEntities().size(), n_each * 3);
    // Check to make sure all of the entity ids are unique
    for (auto e : system->GetEntities()) {
        ASSERT_EQ(entityIds.find(e->GetId()), entityIds.end());
        entityIds.insert(e->GetId());
    }
}

TEST_F(EntityTest, GetEntityName) {
    picojson::object obj0;
    obj0["type"] = picojson::value("drone");
    obj0["name"]  = picojson::value("mydrone");
    Entity* drone = system->CreateEntity(obj0);
    ASSERT_EQ(drone->GetName(), "mydrone");

    picojson::object obj1;
    obj1["type"] = picojson::value("package");
    obj1["name"]  = picojson::value("mypackage");
    Entity* package = system->CreateEntity(obj1);
    ASSERT_EQ(package->GetName(), "mypackage");

    picojson::object obj2;
    obj2["type"] = picojson::value("customer");
    obj2["name"]  = picojson::value("lukas");
    Entity* customer = system->CreateEntity(obj2);
    ASSERT_EQ(customer->GetName(), "lukas");

    delete drone;
    delete package;
    delete customer;
}

TEST_F(EntityTest, GetEntityPosition) {
    picojson::object obj0;
    obj0["type"] = picojson::value("drone");

    picojson::array dronePosition;

    dronePosition.push_back(picojson::value(1.0));
    dronePosition.push_back(picojson::value(2.0));
    dronePosition.push_back(picojson::value(3.0));

    obj0["position"] = picojson::value(dronePosition);

    Entity* drone = system->CreateEntity(obj0);
    ASSERT_NEAR(drone->GetPosition()[0], 1.0, 0.001);
    ASSERT_NEAR(drone->GetPosition()[1], 2.0, 0.001);
    ASSERT_NEAR(drone->GetPosition()[2], 3.0, 0.001);

    picojson::object obj1;
    obj1["type"] = picojson::value("package");

    picojson::array packagePosition;

    packagePosition.push_back(picojson::value(4.0));
    packagePosition.push_back(picojson::value(5.0));
    packagePosition.push_back(picojson::value(6.0));

    obj1["position"] = picojson::value(packagePosition);

    Entity* package = system->CreateEntity(obj1);
    ASSERT_NEAR(package->GetPosition()[0], 4.0, 0.001);
    ASSERT_NEAR(package->GetPosition()[1], 5.0, 0.001);
    ASSERT_NEAR(package->GetPosition()[2], 6.0, 0.001);

    picojson::object obj2;
    obj2["type"] = picojson::value("customer");

    picojson::array customerPosition;

    customerPosition.push_back(picojson::value(7.0));
    customerPosition.push_back(picojson::value(8.0));
    customerPosition.push_back(picojson::value(9.0));

    obj2["position"] = picojson::value(customerPosition);

    Entity* customer = system->CreateEntity(obj2);
    ASSERT_NEAR(customer->GetPosition()[0], 7.0, 0.001);
    ASSERT_NEAR(customer->GetPosition()[1], 8.0, 0.001);
    ASSERT_NEAR(customer->GetPosition()[2], 9.0, 0.001);

    delete drone;
    delete package;
    delete customer;
}

TEST_F(EntityTest, GetEntityDirection) {
    picojson::object obj0;
    obj0["type"] = picojson::value("drone");

    picojson::array droneDirection;

    droneDirection.push_back(picojson::value(1.0));
    droneDirection.push_back(picojson::value(0.0));
    droneDirection.push_back(picojson::value(0.0));

    obj0["direction"] = picojson::value(droneDirection);

    Entity* drone = system->CreateEntity(obj0);
    ASSERT_NEAR(drone->GetDirection()[0], 1.0, 0.001);
    ASSERT_NEAR(drone->GetDirection()[1], 0.0, 0.001);
    ASSERT_NEAR(drone->GetDirection()[2], 0.0, 0.001);

    picojson::object obj1;
    obj1["type"] = picojson::value("package");

    picojson::array packageDirection;

    packageDirection.push_back(picojson::value(0.0));
    packageDirection.push_back(picojson::value(1.0));
    packageDirection.push_back(picojson::value(0.0));

    obj1["direction"] = picojson::value(packageDirection);

    Entity* package = system->CreateEntity(obj1);
    ASSERT_NEAR(package->GetDirection()[0], 0.0, 0.001);
    ASSERT_NEAR(package->GetDirection()[1], 1.0, 0.001);
    ASSERT_NEAR(package->GetDirection()[2], 0.0, 0.001);

    picojson::object obj2;
    obj2["type"] = picojson::value("customer");

    picojson::array customerDirection;

    customerDirection.push_back(picojson::value(0.0));
    customerDirection.push_back(picojson::value(0.0));
    customerDirection.push_back(picojson::value(1.0));

    obj2["direction"] = picojson::value(customerDirection);

    Entity* customer = system->CreateEntity(obj2);
    ASSERT_NEAR(customer->GetDirection()[0], 0.0, 0.001);
    ASSERT_NEAR(customer->GetDirection()[1], 0.0, 0.001);
    ASSERT_NEAR(customer->GetDirection()[2], 1.0, 0.001);

    delete drone;
    delete package;
    delete customer;
}

TEST_F(EntityTest, GetEntityRadius) {
    picojson::object obj0;
    obj0["type"] = picojson::value("drone");
    obj0["radius"]  = picojson::value(23.51);
    Entity* drone = system->CreateEntity(obj0);
    ASSERT_NEAR(drone->GetRadius(), 23.51, 0.001);

    picojson::object obj1;
    obj1["type"] = picojson::value("package");
    obj1["radius"]  = picojson::value(13.12);
    Entity* package = system->CreateEntity(obj1);
    ASSERT_NEAR(package->GetRadius(), 13.12, 0.001);

    picojson::object obj2;
    obj2["type"] = picojson::value("customer");
    obj2["radius"]  = picojson::value(0.52);
    Entity* customer = system->CreateEntity(obj2);
    ASSERT_NEAR(customer->GetRadius(), 0.52, 0.001);

    delete drone;
    delete package;
    delete customer;
}

TEST_F(EntityTest, GetEntityDetails) {
    picojson::object obj0;
    obj0["type"] = picojson::value("drone");
    obj0["radius"]  = picojson::value(23.51);
    Entity* drone = system->CreateEntity(obj0);

    for (auto e : drone->GetDetails()) {
        ASSERT_TRUE((e.first == "type" || e.first == "radius"));
        if (e.first == "type") {
            ASSERT_TRUE(e.second.is<std::string>());
            ASSERT_EQ(e.second.get<std::string>(), "drone");
        } else if (e.first == "radius") {
            ASSERT_TRUE(e.second.is<double>());
            ASSERT_NEAR(e.second.get<double>(), 23.51, 0.001);
        }
    }

    picojson::object obj1;
    obj1["type"] = picojson::value("package");
    obj1["radius"]  = picojson::value(13.23);
    Entity* package = system->CreateEntity(obj1);

    for (auto e : package->GetDetails()) {
        ASSERT_TRUE((e.first == "type" || e.first == "radius"));
        if (e.first == "type") {
            ASSERT_TRUE(e.second.is<std::string>());
            ASSERT_EQ(e.second.get<std::string>(), "package");
        } else if (e.first == "radius") {
            ASSERT_TRUE(e.second.is<double>());
            ASSERT_NEAR(e.second.get<double>(), 13.23, 0.001);
        }
    }

    picojson::object obj2;
    obj2["type"] = picojson::value("customer");
    obj2["radius"]  = picojson::value(0.13);
    Entity* customer = system->CreateEntity(obj2);

    for (auto e : customer->GetDetails()) {
        ASSERT_TRUE((e.first == "type" || e.first == "radius"));
        if (e.first == "type") {
            ASSERT_TRUE(e.second.is<std::string>());
            ASSERT_EQ(e.second.get<std::string>(), "customer");
        } else if (e.first == "radius") {
            ASSERT_TRUE(e.second.is<double>());
            ASSERT_NEAR(e.second.get<double>(), 0.13, 0.001);
        }
    }

    delete drone;
    delete package;
    delete customer;
}

TEST_F(EntityTest, GetEntityDynamic) {
    picojson::object obj0;
    obj0["type"] = picojson::value("drone");
    Entity* drone = system->CreateEntity(obj0);
    ASSERT_TRUE(drone->IsDynamic());

    picojson::object obj1;
    obj1["type"] = picojson::value("package");
    obj1["radius"]  = picojson::value(16.23);
    Entity* package = system->CreateEntity(obj1);
    ASSERT_FALSE(package->IsDynamic());

    picojson::object obj2;
    obj2["type"] = picojson::value("customer");
    obj2["radius"]  = picojson::value(0.31);
    Entity* customer = system->CreateEntity(obj2);
    ASSERT_FALSE(customer->IsDynamic());

    delete drone;
    delete package;
    delete customer;
}

}  // namespace csci3081
