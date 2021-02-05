#include "gtest/gtest.h"
#include "EntityProject/ANVIL2/drone_delivery_system.h"
#include <EntityProject/project_settings.h>
#include <EntityProject/osm_graph_parser.h>
#include <picojson.h>

#include "../src/entity_observable.h"  // NOLINT
#include "../src/drone.h"  // NOLINT
#include "../src/customer.h"  // NOLINT
#include "../src/delivery_scheduler.h"  // NOLINT

#include <iostream>

namespace csci3081 {

using entity_project::DroneDeliverySystem;
using entity_project::Entity;

class DronePhysicsTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    system = GetDroneDeliverySystem("default");
  }
  virtual void TearDown() {}

  DroneDeliverySystem* system;
};

TEST_F(DronePhysicsTest, DronePhysicsFunctionality) {
    entity_project::OSMGraphParser parser;
    const entity_project::IGraph* graph = parser.CreateGraph("data/umn.osm", "data/umn-height.csv");

    float droneMass = 100;
    float droneAcceleration = 3;
    csci3081::Drone drone("", picojson::array(), picojson::array(), 3,
        {droneMass, 100, droneAcceleration, 100, 300},
        csci3081::Drone::FORCE, picojson::object());
    float packageMass = 10;
    csci3081::Package package("", picojson::array(), picojson::array(), 3, picojson::object(),
        packageMass);
    csci3081::Customer customer("", picojson::array({picojson::value(1000.0), picojson::value(0.0),
        picojson::value(0.0)}), picojson::array(), 3, picojson::object());
    package.SetCustomer(&customer);
    drone.GetCarriedPackages().push_back(&package);
    drone.SetRoute(RouteManager::GetRoute({0, 0, 0}, {1000, 0, 0}, graph));
    ASSERT_NEAR(drone.GetCurrentSpeed(), 0, 0.001);
    drone.Update(1);
    float droneForce = droneMass * droneAcceleration;
    float newDroneMass = droneMass + packageMass;
    float adjustedAcceleration = droneForce / newDroneMass;
    ASSERT_NEAR(drone.GetCurrentSpeed(), adjustedAcceleration, 0.001);
}

}  // namespace csci3081

