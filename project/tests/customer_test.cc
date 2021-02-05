#include "gtest/gtest.h"
#include "EntityProject/ANVIL2/drone_delivery_system.h"
#include "EntityProject/ANVIL2/drone.h"
#include <EntityProject/project_settings.h>
#include <picojson.h>

#include <iostream>

#include "../src/customer.h"  // NOLINT

namespace csci3081 {

using entity_project::DroneDeliverySystem;
using entity_project::Entity;

class CustomerTest : public ::testing::Test {
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

TEST_F(CustomerTest, ConstructCustomer) {
    csci3081::Customer customer0;  // Default construct a Customer
    ASSERT_NE(customer0.AsType<entity_project::Customer>(), nullptr);
    picojson::array position;
    position.push_back(picojson::value(1.0));
    position.push_back(picojson::value(2.0));
    position.push_back(picojson::value(3.0));
    picojson::array direction;
    direction.push_back(picojson::value(0.0));
    direction.push_back(picojson::value(1.0));
    picojson::object details;
    // Construct a Customer with Paramters
    csci3081::Customer customer1("lukas", position, direction, 2.0f, details);
    ASSERT_EQ(customer1.GetName(), "lukas");
    ASSERT_NEAR(customer1.GetPosition()[0], 1.0, 0.001);
    ASSERT_NEAR(customer1.GetPosition()[1], 2.0, 0.001);
    ASSERT_NEAR(customer1.GetPosition()[2], 3.0, 0.001);
    ASSERT_NEAR(customer1.GetDirection()[0], 0.0, 0.001);
    ASSERT_NEAR(customer1.GetDirection()[1], 1.0, 0.001);
    ASSERT_NEAR(customer1.GetDirection()[2], 0.0, 0.001);
    ASSERT_NEAR(customer1.GetRadius(), 2.0, 0.001);
}

TEST_F(CustomerTest, UpdateCustomer) {
    csci3081::Customer customer0;  // Default construct a Customer
    ASSERT_NEAR(customer0.GetPosition()[0], 0, 0.001);
    ASSERT_NEAR(customer0.GetPosition()[1], 0, 0.001);
    ASSERT_NEAR(customer0.GetPosition()[2], 0, 0.001);
    customer0.Update(100);
    ASSERT_NEAR(customer0.GetPosition()[0], 0, 0.001);
    ASSERT_NEAR(customer0.GetPosition()[1], 0, 0.001);
    ASSERT_NEAR(customer0.GetPosition()[2], 0, 0.001);
    customer0.SetDynamic(true);
    customer0.Update(100);
    ASSERT_NEAR(customer0.GetPosition()[0], 0, 0.001);
    ASSERT_NEAR(customer0.GetPosition()[1], 0, 0.001);
    ASSERT_NEAR(customer0.GetPosition()[2], 0, 0.001);
}

TEST_F(CustomerTest, DynamicCustomer) {
    csci3081::Customer customer0;  // Default construct a Customer
    ASSERT_FALSE(customer0.IsDynamic());
    customer0.SetDynamic(true);
    ASSERT_TRUE(customer0.IsDynamic());
}

}  // namespace csci3081
