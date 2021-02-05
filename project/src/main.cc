#include <EntityProject/project_settings.h>
#include <EntityProject/web_scene_viewer.h>
#include <EntityProject/osm_graph_parser.h>
#include <drone_simulation.h>   // NOLINT

#include <cmath>
#include <iostream>
#include <sys/stat.h>
#include <cstring>
#include <fstream>
#include <csv_printer.h>

// using namespace csci3081;

int main(int argc, char**argv) {
  std::cout << "Usage: ./build/web-app 8081 web" << std::endl;

  if (argc > 2) {
    int port = std::atoi(argv[1]);
    std::string webDir(argv[2]);

    entity_project::DroneDeliverySystem* entitySystem = GetDroneDeliverySystem("default");

    // Creating an output directory
    if (mkdir("output", 0777) == -1) {
      std::cerr << "Error creating output directory" << std::strerror(errno) << std::endl;
    } else {
      std::cout << "Output directory created" << std::endl;
    }
  csci3081::CSVPrinter printer = csci3081::CSVPrinter("output/Statistics.csv");
  printer.UpdateHeader("Delivery Time", "Total Packages", "Distance Traveled");
  printer.WriteToCSV();
#ifdef ANVIL2
    // Create and set the graph
    entity_project::OSMGraphParser parser;
    const entity_project::IGraph* graph = parser.CreateGraph("data/umn.osm", "data/umn-height.csv");
    entitySystem->SetGraph(graph);
#endif

    entity_project::WebSceneViewer viewer(port, webDir);
    viewer.SetEntitySystem(entitySystem);

    while (viewer.Run()) {}
    delete entitySystem;
  }

  return 0;
}
