#include <EntityProject/project_settings.h>
#include <EntityProject/web_scene_viewer.h>

#include <cmath>
#include <iostream>
// using namespace csci3081;

int main(int argc, char**argv) {
  std::cout << "Usage: ./build/web-app 8081 web" << std::endl;

  if (argc > 2) {
    int port = std::atoi(argv[1]);
    std::string webDir(argv[2]);
    entity_project::DroneDeliverySystem* entitySystem = GetDroneDeliverySystem("default");

    entity_project::WebSceneViewer viewer(port, webDir);
    viewer.SetEntitySystem(entitySystem);
    while (viewer.Run()) {}
    delete entitySystem;
  }

  return 0;
}
