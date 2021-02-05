#include "gtest/gtest.h"
#include "EntityProject/ANVIL/drone_delivery_system.h"
#include "EntityProject/ANVIL/drone.h"
#include <EntityProject/project_settings.h>
#include <picojson.h>

#include "entity_observable.h"  // NOLINT
#include "drone.h"  // NOLINT

#include <iostream>

namespace csci3081 {

using entity_project::DroneDeliverySystem;
using entity_project::Entity;

class DroneTest : public ::testing::Test {
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

TEST_F(DroneTest, DroneConstruct) {
    csci3081::Drone drone0;  // Default construct a Drone
    ASSERT_NE(drone0.AsType<entity_project::Drone>(), nullptr);
    picojson::array position;
    position.push_back(picojson::value(1.0));
    position.push_back(picojson::value(2.0));
    position.push_back(picojson::value(3.0));
    picojson::array direction;
    direction.push_back(picojson::value(0.0));
    direction.push_back(picojson::value(1.0));
    picojson::object details;
    // Construct a Drone with parameters
    csci3081::Drone drone1("mydrone", position, direction, 50.0, 2.0, details);
    ASSERT_EQ(drone1.GetName(), "mydrone");
    ASSERT_NEAR(drone1.GetPosition()[0], 1.0, 0.001);
    ASSERT_NEAR(drone1.GetPosition()[1], 2.0, 0.001);
    ASSERT_NEAR(drone1.GetPosition()[2], 3.0, 0.001);
    ASSERT_NEAR(drone1.GetDirection()[0], 0.0, 0.001);
    ASSERT_NEAR(drone1.GetDirection()[1], 1.0, 0.001);
    ASSERT_NEAR(drone1.GetDirection()[2], 0.0, 0.001);
    ASSERT_NEAR(drone1.GetRadius(), 2.0, 0.001);
}

TEST_F(DroneTest, DroneOrder) {
    csci3081::Drone drone0;  // Default construct a Drone
    csci3081::Customer customer0;  // Default construct a Customer
    csci3081::Package package0;  // Default construct a Package
    picojson::object details;
    csci3081::Order order0(&customer0, &package0, details);
    ASSERT_EQ(drone0.GetOrder(), nullptr);
    drone0.SetOrder(&order0);
    ASSERT_EQ(drone0.GetOrder(), &order0);
    ASSERT_EQ(drone0.GetOrder()->GetCustomer(), &customer0);
    ASSERT_EQ(drone0.GetOrder()->GetPackage(), &package0);
}

TEST_F(DroneTest, DroneRoute) {
    csci3081::Drone drone0;  // Default construct a Drone
    std::vector<entity_project::SimpleUMNRoutePoint> path;
    path.push_back(entity_project::SimpleUMNRoutePoint(1, 0, 0));
    path.push_back(entity_project::SimpleUMNRoutePoint(0, 1, 0));
    path.push_back(entity_project::SimpleUMNRoutePoint(0, 0, 1));
    ASSERT_EQ(drone0.GetRoute().size(), 0);
    drone0.SetRoute(path);
    ASSERT_EQ(drone0.GetRoute().size(), 3);
}

TEST_F(DroneTest, DroneUpdate) {
    picojson::array position;
    position.push_back(picojson::value(0.0));
    position.push_back(picojson::value(0.0));
    position.push_back(picojson::value(100.0));
    picojson::array direction;
    picojson::object details;
    csci3081::Drone drone0("mydrone", position, direction, 1.0f, 0.0f, details);
    drone0.Update(10);
    ASSERT_FLOAT_EQ(drone0.GetPosition()[0], 0.0);
    ASSERT_FLOAT_EQ(drone0.GetPosition()[1], 0.0);
    ASSERT_FLOAT_EQ(drone0.GetPosition()[2], 100.0);
    csci3081::Customer customer0;
    csci3081::Package package0;
    picojson::object orderDetails;
    csci3081::Order* order0 = new csci3081::Order(&customer0, &package0, orderDetails);
    drone0.SetOrder(order0);
    drone0.Update(1);
    ASSERT_FLOAT_EQ(drone0.GetPosition()[0], 0.0);
    ASSERT_FLOAT_EQ(drone0.GetPosition()[1], 0.0);
    ASSERT_FLOAT_EQ(drone0.GetPosition()[2], 99);
    drone0.Update(1);
    ASSERT_FLOAT_EQ(drone0.GetPosition()[0], 0.0);
    ASSERT_FLOAT_EQ(drone0.GetPosition()[1], 0.0);
    ASSERT_FLOAT_EQ(drone0.GetPosition()[2], 98);
}

}  // namespace csci3081
