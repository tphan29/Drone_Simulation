#include "gtest/gtest.h"
#include "EntityProject/ANVIL2/drone_delivery_system.h"
#include "EntityProject/ANVIL2/drone.h"
#include <EntityProject/project_settings.h>
#include <picojson.h>

#include "../src/entity_observable.h"  // NOLINT
#include "../src/drone.h"  // NOLINT
#include "../src/customer.h"  // NOLINT

#include <iostream>

namespace csci3081 {

using entity_project::DroneDeliverySystem;
using entity_project::Entity;

class SimulationTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    system = GetDroneDeliverySystem("default");
  }
  virtual void TearDown() {}

  DroneDeliverySystem* system;
};

class TestSimulationObserver : public entity_project::EntityObserver {
 public:
    void OnEvent(const picojson::value& event, const Entity& entity) override {
        std::cout << "test observer\n";
    }
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(SimulationTest, CreateEntityDrone) {
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

    Entity* entity = system->CreateEntity(obj);
    csci3081::Drone* drone = entity->AsType<csci3081::Drone>();
    ASSERT_NE(entity, nullptr);
    ASSERT_NE(drone, nullptr);
    ASSERT_NEAR(drone->GetPosition()[0], 1.0, 0.001);
    ASSERT_NEAR(drone->GetPosition()[1], 2.0, 0.001);
    ASSERT_NEAR(drone->GetPosition()[2], 3.0, 0.001);
    ASSERT_NEAR(drone->GetDirection()[0], 0.0, 0.001);
    ASSERT_NEAR(drone->GetDirection()[1], 1.0, 0.001);
    ASSERT_NEAR(drone->GetDirection()[2], 0.0, 0.001);
    ASSERT_NEAR(drone->GetRadius(), 2.0, 0.001);
    ASSERT_EQ(drone->GetName(), "mydrone");
    ASSERT_EQ(picojson::value(obj).serialize(), picojson::value(drone->GetDetails()).serialize());
}

TEST_F(SimulationTest, CreateEntityPackage) {
    picojson::object obj;
    obj["type"] = picojson::value("package");

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

    Entity* entity = system->CreateEntity(obj);
    csci3081::Package* package = entity->AsType<csci3081::Package>();
    ASSERT_NE(entity, nullptr);
    ASSERT_NE(package, nullptr);
    ASSERT_NEAR(package->GetPosition()[0], 1.0, 0.001);
    ASSERT_NEAR(package->GetPosition()[1], 2.0, 0.001);
    ASSERT_NEAR(package->GetPosition()[2], 3.0, 0.001);
    ASSERT_NEAR(package->GetDirection()[0], 0.0, 0.001);
    ASSERT_NEAR(package->GetDirection()[1], 1.0, 0.001);
    ASSERT_NEAR(package->GetDirection()[2], 0.0, 0.001);
    ASSERT_NEAR(package->GetRadius(), 2.0, 0.001);
    ASSERT_EQ(package->GetName(), "mypackage");
    ASSERT_EQ(picojson::value(obj).serialize(), picojson::value(package->GetDetails()).serialize());
}

TEST_F(SimulationTest, CreateEntityCustomer) {
    picojson::object obj;
    obj["type"] = picojson::value("customer");

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

    Entity* entity = system->CreateEntity(obj);
    csci3081::Customer* customer = entity->AsType<csci3081::Customer>();
    ASSERT_NE(entity, nullptr);
    ASSERT_NE(customer, nullptr);
    ASSERT_NEAR(customer->GetPosition()[0], 1.0, 0.001);
    ASSERT_NEAR(customer->GetPosition()[1], 2.0, 0.001);
    ASSERT_NEAR(customer->GetPosition()[2], 3.0, 0.001);
    ASSERT_NEAR(customer->GetDirection()[0], 0.0, 0.001);
    ASSERT_NEAR(customer->GetDirection()[1], 1.0, 0.001);
    ASSERT_NEAR(customer->GetDirection()[2], 0.0, 0.001);
    ASSERT_NEAR(customer->GetRadius(), 2.0, 0.001);
    ASSERT_EQ(customer->GetName(), "lukas");
    ASSERT_EQ(picojson::value(obj).serialize(),
        picojson::value(customer->GetDetails()).serialize());
}

TEST_F(SimulationTest, AddEntity) {
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

    Entity* entity = system->CreateEntity(obj);
    ASSERT_EQ(system->GetEntities().size(), 0);
    system->AddEntity(entity);
    ASSERT_EQ(system->GetEntities().size(), 1);
    ASSERT_EQ(system->GetEntities()[0], entity);
}

TEST_F(SimulationTest, ScheduleDelivery) {
    picojson::array position0;
    position0.push_back(picojson::value(100.0));
    position0.push_back(picojson::value(0.0));
    position0.push_back(picojson::value(100.0));
    picojson::array direction0;
    picojson::object details0;
    // Construct a Drone with parameters
    csci3081::Drone* drone0 = new csci3081::Drone("mydrone", position0, direction0,
        50.0, 2.0, details0);

    system->AddEntity(drone0);

    picojson::array position1;
    position1.push_back(picojson::value(-100.0));
    position1.push_back(picojson::value(0.0));
    position1.push_back(picojson::value(-100.0));
    picojson::array direction1;
    picojson::object details1;
    // Construct a Customer with parameters
    csci3081::Customer* customer0 = new csci3081::Customer("lukas", position1, direction1,
        2.0, details1);

    system->AddEntity(customer0);

    picojson::array position2;
    position2.push_back(picojson::value(-100.0));
    position2.push_back(picojson::value(0.0));
    position2.push_back(picojson::value(100.0));
    picojson::array direction2;
    picojson::object details2;
    // Construct a Package with parameters
    csci3081::Package* package0 = new csci3081::Package("mypackage", position2, direction2,
        2.0, details2, 0.0);

    system->AddEntity(package0);

    ASSERT_TRUE(drone0->GetPendingPackages().empty());
    picojson::object deliveryDetails;
    system->ScheduleDelivery(package0, customer0, deliveryDetails);
    ASSERT_EQ(drone0->GetPendingPackages()[0], package0);
    ASSERT_EQ(drone0->GetPendingPackages()[0]->GetCustomer(), customer0);
}

TEST_F(SimulationTest, AddObserver) {
    picojson::array position0;
    position0.push_back(picojson::value(100.0));
    position0.push_back(picojson::value(0.0));
    position0.push_back(picojson::value(100.0));
    picojson::array direction0;
    picojson::object details0;
    // Construct a Drone with parameters
    csci3081::Drone* drone0 = new csci3081::Drone("mydrone", position0, direction0,
        50.0, 2.0, details0);

    system->AddEntity(drone0);

    TestSimulationObserver observer;
    system->AddObserver(drone0, &observer);

    picojson::value eventValue;
    testing::internal::CaptureStdout();
    drone0->NotifyObservers(eventValue);
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_TRUE((output.find("test observer\n") != std::string::npos));
}

TEST_F(SimulationTest, RemoveObserver) {
    picojson::array position0;
    position0.push_back(picojson::value(100.0));
    position0.push_back(picojson::value(0.0));
    position0.push_back(picojson::value(100.0));
    picojson::array direction0;
    picojson::object details0;
    // Construct a Drone with parameters
    csci3081::Drone* drone0 = new csci3081::Drone("mydrone", position0, direction0,
        50.0, 2.0, details0);

    system->AddEntity(drone0);

    TestSimulationObserver observer;
    system->AddObserver(drone0, &observer);
    system->RemoveObserver(drone0, &observer);

    picojson::value eventValue;
    testing::internal::CaptureStdout();
    drone0->NotifyObservers(eventValue);
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_TRUE((output.find("test observer\n") == std::string::npos));
}

TEST_F(SimulationTest, Update) {
    picojson::array position0;
    position0.push_back(picojson::value(100.0));
    position0.push_back(picojson::value(0.0));
    position0.push_back(picojson::value(100.0));
    picojson::array direction0;
    picojson::object details0;
    // Construct a Drone with parameters
    csci3081::Drone* drone0 = new csci3081::Drone("mydrone", position0, direction0,
        50.0, 2.0, details0);

    system->AddEntity(drone0);

    picojson::array position1;
    position1.push_back(picojson::value(100.0));
    position1.push_back(picojson::value(0.0));
    position1.push_back(picojson::value(-100.0));
    picojson::array direction1;
    picojson::object details1;
    // Construct a Customer with parameters
    csci3081::Customer* customer0 = new csci3081::Customer("lukas", position1, direction1,
        2.0, details1);

    system->AddEntity(customer0);

    picojson::array position2;
    position2.push_back(picojson::value(-100.0));
    position2.push_back(picojson::value(0.0));
    position2.push_back(picojson::value(100.0));
    picojson::array direction2;
    picojson::object details2;
    // Construct a Package with parameters
    csci3081::Package* package0 = new csci3081::Package("mypackage", position2, direction2,
        2.0, details2, 0.0);


    system->AddEntity(package0);

    system->Update(1.0);

    ASSERT_NEAR(drone0->GetPosition()[0], 100, 0.001);
    ASSERT_NEAR(drone0->GetPosition()[1], 0, 0.001);
    ASSERT_NEAR(drone0->GetPosition()[2], 100, 0.001);

    ASSERT_NEAR(customer0->GetPosition()[0], 100, 0.001);
    ASSERT_NEAR(customer0->GetPosition()[1], 0, 0.001);
    ASSERT_NEAR(customer0->GetPosition()[2], -100, 0.001);

    ASSERT_NEAR(package0->GetPosition()[0], -100, 0.001);
    ASSERT_NEAR(package0->GetPosition()[1], 0, 0.001);
    ASSERT_NEAR(package0->GetPosition()[2], 100, 0.001);

    drone0->AddPackage(package0);
    drone0->SetRoute({});

    system->Update(1.0);

    // The drone should move speed * dt = 50 units
    // closer to the package. All other
    ASSERT_NEAR(drone0->GetPosition()[0], 50, 0.001);
    ASSERT_NEAR(drone0->GetPosition()[1], 0, 0.001);
    ASSERT_NEAR(drone0->GetPosition()[2], 100, 0.001);

    ASSERT_NEAR(customer0->GetPosition()[0], 100, 0.001);
    ASSERT_NEAR(customer0->GetPosition()[1], 0, 0.001);
    ASSERT_NEAR(customer0->GetPosition()[2], -100, 0.001);

    ASSERT_NEAR(package0->GetPosition()[0], -100, 0.001);
    ASSERT_NEAR(package0->GetPosition()[1], 0, 0.001);
    ASSERT_NEAR(package0->GetPosition()[2], 100, 0.001);
}

}  // namespace csci3081
