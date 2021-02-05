#include "gtest/gtest.h"
#include <EntityProject/ANVIL2/drone_delivery_system.h>
#include <EntityProject/ANVIL2/drone.h>
#include <EntityProject/project_settings.h>
#include <picojson.h>

#include "../src/drone.h"  // NOLINT
#include "../src/customer.h"  // NOLINT

#include <iostream>

namespace csci3081 {

using entity_project::DroneDeliverySystem;
using entity_project::Entity;

class FactoryTest : public ::testing::Test {
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

TEST_F(FactoryTest, DroneCreated) {
    std::size_t numEntities = system->GetEntities().size();
    picojson::object obj;
    obj["type"] = picojson::value("drone");
    Entity* entity = system->CreateEntity(obj);
    ASSERT_NE(entity, nullptr);
    Drone* drone = entity->AsType<Drone>();
    ASSERT_NE(drone, nullptr);
    Customer* customer = entity->AsType<Customer>();
    ASSERT_EQ(customer, nullptr);
    ASSERT_EQ(system->GetEntities().size(), numEntities);
    system->AddEntity(drone);
    ASSERT_EQ(system->GetEntities().size(), numEntities + 1);
    entity = nullptr;
    drone = nullptr;
    customer = nullptr;
    picojson::array pos;
    pos.push_back(picojson::value(1.0));
    pos.push_back(picojson::value(2.0));
    pos.push_back(picojson::value(3.0));
    picojson::array direction;
    direction.push_back(picojson::value(0.0));
    direction.push_back(picojson::value(1.0));

    obj["position"] = picojson::value(pos);
    obj["direction"] = picojson::value(direction);
    obj["name"] = picojson::value("mydrone");
    obj["radius"] = picojson::value(2.0);

    entity = system->CreateEntity(obj);
    ASSERT_NE(entity, nullptr);
    drone = entity->AsType<Drone>();
    ASSERT_NE(drone, nullptr);
    customer = entity->AsType<Customer>();
    ASSERT_EQ(customer, nullptr);
    ASSERT_EQ(drone->GetPosition()[0], 1.0);
    ASSERT_EQ(drone->GetPosition()[1], 2.0);
    ASSERT_EQ(drone->GetPosition()[2], 3.0);
    ASSERT_EQ(drone->GetDirection()[0], 0.0);
    ASSERT_EQ(drone->GetDirection()[1], 1.0);
    ASSERT_EQ(drone->GetDirection()[2], 0.0);
    ASSERT_EQ(drone->GetName(), "mydrone");
    ASSERT_EQ(drone->GetRadius(), 2.0);
}

TEST_F(FactoryTest, ModelDroneCreated) {
    std::size_t numEntities = system->GetEntities().size();
    picojson::object obj;
    obj["type"] = picojson::value("drone");
    picojson::array pos;
    pos.push_back(picojson::value(1.0));
    pos.push_back(picojson::value(2.0));
    pos.push_back(picojson::value(3.0));
    picojson::array direction;
    direction.push_back(picojson::value(0.0));
    direction.push_back(picojson::value(1.0));

    obj["position"] = picojson::value(pos);
    obj["direction"] = picojson::value(direction);
    obj["name"] = picojson::value("mydrone");
    obj["radius"] = picojson::value(2.0);
    obj["model"] = picojson::value("Q-36-04");

    Entity* entity = system->CreateEntity(obj);
    ASSERT_NE(entity, nullptr);
    csci3081::Drone* drone = entity->AsType<csci3081::Drone>();
    ASSERT_NE(drone, nullptr);
    Customer* customer = entity->AsType<Customer>();
    ASSERT_EQ(customer, nullptr);
    ASSERT_EQ(drone->GetPosition()[0], 1.0);
    ASSERT_EQ(drone->GetPosition()[1], 2.0);
    ASSERT_EQ(drone->GetPosition()[2], 3.0);
    ASSERT_EQ(drone->GetDirection()[0], 0.0);
    ASSERT_EQ(drone->GetDirection()[1], 1.0);
    ASSERT_EQ(drone->GetDirection()[2], 0.0);
    ASSERT_EQ(drone->GetName(), "mydrone");
    ASSERT_EQ(drone->GetRadius(), 2.0);
    ASSERT_EQ(drone->GetMass(), 120);
    ASSERT_NEAR(drone->GetMaxSpeed(), 8.3333, 0.001);
    ASSERT_EQ(drone->GetBaseAcceleration(), 6);
    ASSERT_EQ(drone->GetMaxCapacity(), 19);
    ASSERT_EQ(drone->GetRemainingCapacity(), 19);
    ASSERT_EQ(drone->GetBaseBatteryCapacity(), 90);
    ASSERT_EQ(drone->GetRemainingBattery(), 90);

    delete drone;

    obj["model"] = picojson::value("Q-36-01");
    entity = system->CreateEntity(obj);
    ASSERT_NE(entity, nullptr);
    drone = entity->AsType<csci3081::Drone>();
    ASSERT_NE(drone, nullptr);
    customer = entity->AsType<Customer>();
    ASSERT_EQ(customer, nullptr);
    ASSERT_EQ(drone->GetPosition()[0], 1.0);
    ASSERT_EQ(drone->GetPosition()[1], 2.0);
    ASSERT_EQ(drone->GetPosition()[2], 3.0);
    ASSERT_EQ(drone->GetDirection()[0], 0.0);
    ASSERT_EQ(drone->GetDirection()[1], 1.0);
    ASSERT_EQ(drone->GetDirection()[2], 0.0);
    ASSERT_EQ(drone->GetName(), "mydrone");
    ASSERT_EQ(drone->GetRadius(), 2.0);
    ASSERT_EQ(drone->GetMass(), 50);
    ASSERT_NEAR(drone->GetMaxSpeed(), 16.66666, 0.001);
    ASSERT_EQ(drone->GetBaseAcceleration(), 4);
    ASSERT_EQ(drone->GetMaxCapacity(), 10);
    ASSERT_EQ(drone->GetRemainingCapacity(), 10);
    ASSERT_EQ(drone->GetBaseBatteryCapacity(), 300);
    ASSERT_EQ(drone->GetRemainingBattery(), 300);

    delete drone;
}

TEST_F(FactoryTest, CustomerCreated) {
    std::size_t numEntities = system->GetEntities().size();
    picojson::object obj;
    obj["type"] = picojson::value("customer");
    Entity* entity = system->CreateEntity(obj);
    ASSERT_NE(entity, nullptr);
    Customer* customer = entity->AsType<Customer>();
    ASSERT_NE(customer, nullptr);
    Drone* drone = entity->AsType<Drone>();
    ASSERT_EQ(drone, nullptr);
    ASSERT_EQ(system->GetEntities().size(), numEntities);
    system->AddEntity(customer);
    ASSERT_EQ(system->GetEntities().size(), numEntities + 1);
    entity = nullptr;
    customer = nullptr;
    drone = nullptr;
    picojson::array pos;
    pos.push_back(picojson::value(1.0));
    pos.push_back(picojson::value(2.0));
    pos.push_back(picojson::value(3.0));
    picojson::array direction;
    direction.push_back(picojson::value(0.0));
    direction.push_back(picojson::value(1.0));

    obj["position"] = picojson::value(pos);
    obj["direction"] = picojson::value(direction);
    obj["name"] = picojson::value("lukas");
    obj["radius"] = picojson::value(2.0);

    entity = system->CreateEntity(obj);
    system->AddEntity(entity);
    ASSERT_NE(entity, nullptr);
    customer = entity->AsType<Customer>();
    ASSERT_NE(customer, nullptr);
    drone = entity->AsType<Drone>();
    ASSERT_EQ(drone, nullptr);
    ASSERT_EQ(customer->GetPosition()[0], 1.0);
    ASSERT_EQ(customer->GetPosition()[1], 2.0);
    ASSERT_EQ(customer->GetPosition()[2], 3.0);
    ASSERT_EQ(customer->GetDirection()[0], 0.0);
    ASSERT_EQ(customer->GetDirection()[1], 1.0);
    ASSERT_EQ(customer->GetDirection()[2], 0.0);
    ASSERT_EQ(customer->GetName(), "lukas");
    ASSERT_EQ(customer->GetRadius(), 2.0);
}

TEST_F(FactoryTest, PackageCreated) {
    std::size_t numEntities = system->GetEntities().size();
    picojson::object obj;
    obj["type"] = picojson::value("package");
    Entity* entity = system->CreateEntity(obj);
    ASSERT_NE(entity, nullptr);
    Package* package = entity->AsType<Package>();
    ASSERT_NE(package, nullptr);
    Customer* customer = entity->AsType<Customer>();
    ASSERT_EQ(customer, nullptr);
    ASSERT_EQ(system->GetEntities().size(), numEntities);
    system->AddEntity(package);
    ASSERT_EQ(system->GetEntities().size(), numEntities + 1);
    entity = nullptr;
    package = nullptr;
    customer = nullptr;
    picojson::array pos;
    pos.push_back(picojson::value(1.0));
    pos.push_back(picojson::value(2.0));
    pos.push_back(picojson::value(3.0));
    picojson::array direction;
    direction.push_back(picojson::value(0.0));
    direction.push_back(picojson::value(1.0));

    obj["position"] = picojson::value(pos);
    obj["direction"] = picojson::value(direction);
    obj["name"] = picojson::value("mypackage");
    obj["radius"] = picojson::value(2.0);

    entity = system->CreateEntity(obj);
    ASSERT_NE(entity, nullptr);
    package = entity->AsType<Package>();
    ASSERT_NE(package, nullptr);
    customer = entity->AsType<Customer>();
    ASSERT_EQ(customer, nullptr);
    ASSERT_EQ(package->GetPosition()[0], 1.0);
    ASSERT_EQ(package->GetPosition()[1], 2.0);
    ASSERT_EQ(package->GetPosition()[2], 3.0);
    ASSERT_EQ(package->GetDirection()[0], 0.0);
    ASSERT_EQ(package->GetDirection()[1], 1.0);
    ASSERT_EQ(package->GetDirection()[2], 0.0);
    ASSERT_EQ(package->GetName(), "mypackage");
    ASSERT_EQ(package->GetRadius(), 2.0);
}

}  // namespace csci3081
