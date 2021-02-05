#include "gtest/gtest.h"
#include "EntityProject/ANVIL2/drone_delivery_system.h"
#include "EntityProject/ANVIL2/drone.h"
#include <EntityProject/project_settings.h>
#include <picojson.h>

#include <iostream>

#include "../src/package.h"  // NOLINT
#include "../src/drone.h"  // NOLINT

namespace csci3081 {

using entity_project::DroneDeliverySystem;
using entity_project::Entity;

class PackageTest : public ::testing::Test {
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

TEST_F(PackageTest, ConstructPackage) {
    csci3081::Package package0;  // Default construct a Package
    ASSERT_NE(package0.AsType<entity_project::Package>(), nullptr);
    picojson::array position;
    position.push_back(picojson::value(1.0));
    position.push_back(picojson::value(2.0));
    position.push_back(picojson::value(3.0));
    picojson::array direction;
    direction.push_back(picojson::value(0.0));
    direction.push_back(picojson::value(1.0));
    picojson::object details;
    // Construct a Package with Paramters
    csci3081::Package package1("mypackage", position, direction, 1.0, details, 0.0);
    ASSERT_EQ(package1.GetName(), "mypackage");
    ASSERT_NEAR(package1.GetPosition()[0], 1.0, 0.001);
    ASSERT_NEAR(package1.GetPosition()[1], 2.0, 0.001);
    ASSERT_NEAR(package1.GetPosition()[2], 3.0, 0.001);
    ASSERT_NEAR(package1.GetDirection()[0], 0.0, 0.001);
    ASSERT_NEAR(package1.GetDirection()[1], 1.0, 0.001);
    ASSERT_NEAR(package1.GetDirection()[2], 0.0, 0.001);
    ASSERT_NEAR(package1.GetRadius(), 1.0, 0.001);
}

TEST_F(PackageTest, UpdatePackage) {
    picojson::array position0;
    position0.push_back(picojson::value(1.0));
    position0.push_back(picojson::value(2.0));
    position0.push_back(picojson::value(3.0));
    picojson::array direction0;
    picojson::object details0;
    csci3081::Package package0("mypackage", position0, direction0, 1.0, details0, 0.0);
    picojson::array position1;
    position1.push_back(picojson::value(0.0));
    position1.push_back(picojson::value(0.0));
    position1.push_back(picojson::value(0.0));
    picojson::array direction1;
    picojson::object details1;
    // Construct a Drone with parameters
    csci3081::Drone drone0("mydrone", position1, direction1, 50.0, 2.0, details1);
    package0.Update(1);
    ASSERT_NEAR(package0.GetPosition()[0], 1.0, 0.001);
    ASSERT_NEAR(package0.GetPosition()[1], 2.0, 0.001);
    ASSERT_NEAR(package0.GetPosition()[2], 3.0, 0.001);
    package0.SetDrone(&drone0);
    package0.Update(1);
    // After this Update call, the package should be the same position as the drone
    ASSERT_NEAR(package0.GetPosition()[0], drone0.GetPosition()[0], 0.001);
    ASSERT_NEAR(package0.GetPosition()[1], drone0.GetPosition()[1], 0.001);
    ASSERT_NEAR(package0.GetPosition()[2], drone0.GetPosition()[2], 0.001);
}

TEST_F(PackageTest, DynamicPackage) {
    csci3081::Package package0;
    ASSERT_FALSE(package0.IsDynamic());
    package0.SetDynamic(true);
    ASSERT_TRUE(package0.IsDynamic());
}

}  // namespace csci3081
