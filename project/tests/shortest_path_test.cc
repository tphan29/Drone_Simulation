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

class ShortestPathTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    system = GetDroneDeliverySystem("default");
  }
  virtual void TearDown() {}

  DroneDeliverySystem* system;
};

class PathObserver : public entity_project::EntityObserver {
 public:
    void OnEvent(const picojson::value& event, const Entity& entity) override {
        if (event.is<picojson::object>()) {
            auto obj = event.get<picojson::object>();
            auto path = obj.find("path");
            if (path != obj.end() && path->second.is<picojson::array>()) {
                auto array = path->second.get<picojson::array>();
                for (auto e : array) {
                    if (e.is<picojson::array>()) {
                        for (auto p : e.get<picojson::array>()) {
                            if (p.is<double>()) {
                                std::cout << p.get<double>() << ' ';
                            }
                        }
                        std::cout << '\n';
                    }
                }
            }
        }
    }
};
TEST_F(ShortestPathTest, ShortestPathObserver) {
    entity_project::OSMGraphParser parser;
    const entity_project::IGraph* graph = parser.CreateGraph("data/umn.osm", "data/umn-height.csv");

    csci3081::Drone drone;
    PathObserver observer;
    drone.AddObserver(&observer);
    testing::internal::CaptureStdout();
    drone.SetRoute(RouteManager::GetRoute({0, 0, 0}, {100, 100, 100}, graph));
    std::string output1 = testing::internal::GetCapturedStdout();
    testing::internal::CaptureStdout();
    for (auto p : drone.GetRoute()) {
        for (auto q : p->GetPosition()) {
            std::cout << q << ' ';
        }
        std::cout << '\n';
    }
    std::string output2 = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output1, output2);
}

}  // namespace csci3081
