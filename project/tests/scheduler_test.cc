#include "gtest/gtest.h"
#include "EntityProject/ANVIL2/drone_delivery_system.h"
#include "EntityProject/ANVIL2/drone.h"
#include <EntityProject/project_settings.h>
#include <picojson.h>

#include "../src/entity_observable.h"  // NOLINT
#include "../src/drone.h"  // NOLINT
#include "../src/customer.h"  // NOLINT
#include "../src/delivery_scheduler.h"  // NOLINT

#include <iostream>

namespace csci3081 {

using entity_project::DroneDeliverySystem;
using entity_project::Entity;

class SchedulerTest : public ::testing::Test {
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

TEST_F(SchedulerTest, ScheduleDelivery) {
    // Create vector of entities to keep track of
    std::vector<entity_project::Entity*> entities;
    // Make the scheduler object
    DeliveryScheduler scheduler(&entities);

    picojson::array position0;
    position0.push_back(picojson::value(100.0));
    position0.push_back(picojson::value(0.0));
    position0.push_back(picojson::value(100.0));
    picojson::array direction0;
    picojson::object details0;
    // Construct a Drone with parameters
    csci3081::Drone drone0("mydrone", position0, direction0, 50.0, 2.0, details0);

    entities.push_back(&drone0);
    scheduler.Update(1.0);  // Shouldn't do anything, we haven't scheduled anything
    ASSERT_TRUE(drone0.GetPendingPackages().empty());

    picojson::array position1;
    position1.push_back(picojson::value(-100.0));
    position1.push_back(picojson::value(0.0));
    position1.push_back(picojson::value(-100.0));
    picojson::array direction1;
    picojson::object details1;
    // Construct a Customer with parameters
    csci3081::Customer customer0("lukas", position1, direction1, 2.0, details1);

    entities.push_back(&customer0);

    picojson::array position2;
    position2.push_back(picojson::value(-100.0));
    position2.push_back(picojson::value(0.0));
    position2.push_back(picojson::value(100.0));
    picojson::array direction2;
    picojson::object details2;
    // Construct a Package with parameters
    csci3081::Package package0("mypackage", position2, direction2, 2.0, details2, 0.0);

    entities.push_back(&package0);

    picojson::object details3;
    // Now, we will schedule the delivery
    scheduler.ScheduleDelivery(&package0, &customer0, details3);
    scheduler.Update(0);

    ASSERT_EQ(drone0.GetPendingPackages()[0], &package0);
    ASSERT_EQ(drone0.GetPendingPackages()[0]->GetCustomer(), &customer0);
}

TEST_F(SchedulerTest, ScheduleCloseDelivery) {
    // Test the case where the package is already in
    // range of the customer
    // Create vector of entities to keep track of
    std::vector<entity_project::Entity*> entities;
    // Make the scheduler object
    DeliveryScheduler scheduler(&entities);

    picojson::array position0;
    position0.push_back(picojson::value(100.0));
    position0.push_back(picojson::value(0.0));
    position0.push_back(picojson::value(100.0));
    picojson::array direction0;
    picojson::object details0;
    // Construct a Drone with parameters
    csci3081::Drone drone0("mydrone", position0, direction0, 50.0, 2.0, details0);

    entities.push_back(&drone0);
    scheduler.Update(1.0);  // Shouldn't do anything, we haven't scheduled anything
    ASSERT_TRUE(drone0.GetPendingPackages().empty());

    picojson::array position1;
    position1.push_back(picojson::value(-100.0));
    position1.push_back(picojson::value(0.0));
    position1.push_back(picojson::value(-100.0));
    picojson::array direction1;
    picojson::object details1;
    // Construct a Customer with parameters
    csci3081::Customer customer0("lukas", position1, direction1, 2.0, details1);

    entities.push_back(&customer0);

    picojson::array position2;
    position2.push_back(picojson::value(-100.0));
    position2.push_back(picojson::value(0.0));
    position2.push_back(picojson::value(-100.0));
    picojson::array direction2;
    picojson::object details2;
    // Construct a Package with parameters
    csci3081::Package* package0 = new csci3081::Package("mypackage", position2, direction2, 2.0,
        details2, 0.0);

    entities.push_back(package0);

    picojson::object details3;
    // Now, we will schedule the delivery
    scheduler.ScheduleDelivery(package0, &customer0, details3);
    scheduler.Update(0);

    // Our drone shouldn't get the order
    // it was already in range of the customer
    ASSERT_TRUE(drone0.GetPendingPackages().empty());
    // The package should not be in our entity list
    // anymore because it should have been immedietly delivered
    auto iter = std::find(entities.begin(), entities.end(), package0);
    ASSERT_EQ(iter, entities.end());
}

}  // namespace csci3081
