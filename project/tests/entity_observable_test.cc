#include "gtest/gtest.h"
#include "EntityProject/ANVIL2/drone_delivery_system.h"
#include "EntityProject/ANVIL2/drone.h"
#include <EntityProject/project_settings.h>
#include <picojson.h>

#include <iostream>

#include "../src/drone.h"  // NOLINT
#include "../src/customer.h"  // NOLINT

namespace csci3081 {

using entity_project::DroneDeliverySystem;
using entity_project::Entity;

class EntityObservableTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    system = GetDroneDeliverySystem("default");
  }
  virtual void TearDown() {}

  DroneDeliverySystem* system;
};

class TestObserver : public entity_project::EntityObserver {
 public:
    void OnEvent(const picojson::value& event, const Entity& entity) override {
        std::cout << "test observer" << std::endl;
    }
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(EntityObservableTest, AddObserver) {
    csci3081::Drone drone0;  // Default construct a Drone
    picojson::value eventValue;
    TestObserver observer;
    drone0.AddObserver(&observer);
    testing::internal::CaptureStdout();
    drone0.NotifyObservers(eventValue);
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "test observer\n");
}

TEST_F(EntityObservableTest, RemoveObserver) {
    csci3081::Drone drone0;  // Default construct a Drone
    picojson::value eventValue;
    TestObserver observer;
    drone0.AddObserver(&observer);
    drone0.RemoveObserver(&observer);
    testing::internal::CaptureStdout();
    drone0.NotifyObservers(eventValue);
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "");
}


}  // namespace csci3081
