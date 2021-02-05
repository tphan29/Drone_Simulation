/*! \mainpage CSCI 3081 - Drone Delivery System - Doxygen Documentation - Lukas Hering, Madelyn Ogorek, Tony Phan, and Lucas Schober
 *
 *  \section intro_sec Introduction
 *  This Doxygen document contains all of the relevant documentation for the CSCI 3081 - Drone Delivery Project for Fall 2020.
 *  Please note that the documentation provided is for the second iteration and changes WILL be made as the project progresses.
 *  \subsection quick_links Quick Links
 *  - <a href="https://pages.github.umn.edu/umn-csci-3081-f20/project-portal/Iteration1Requirements.pdf">Iteration 1 Requirements</a>
 *  - <a href="https://github.umn.edu/umn-csci-3081-f20/project-portal/blob/master/Iteration2Requirements.pdf">Iteration 2 Requirements</a>
 *  - <a href="https://github.umn.edu/umn-csci-3081-f20/project-portal/blob/master/Drone%20Delivery%20Project%20Sequence%20Diagram%20(1)-1.png">Project Sequence Diagram</a>
 *  - <a href="https://github.umn.edu/umn-csci-3081-f20/project-portal/wiki"> Project Wiki</a>
 *  - <a href="https://pages.github.umn.edu/umn-csci-3081-f20/project-portal/docs/html/index.html">Support Code Documentation</a>
 *  - <a href="annotated.html">Classes</a>
 *  - <a href="files.html">Files</a>
 *  \subsection related_pages Related Pages
 *  - <a href="DeliverySchedulerPage.html">DeliveryScheduler Details</a>
 *  - <a href="EntityFactoryPage.html">EntityFactory Page</a>
 *  - <a href="DroneSimulationPage.html">DroneSimulation Page</a>
 *  \section getting_started Getting Started
 *  The project centers around the csci3081::DroneSimulation class which is a contrete implementation of the abstract facade entity_project::DroneDeliverySystem.
 *  <br>
 *  Below is a simple example of how the csci3081::DroneSimulation class can be used.
 *  \code{.cpp}
 *  // Create an instance of csci3081::DroneSimulation
 *  entity_project::DroneDeliverySystem* system = new csci3081::DroneSimulation;
 *  picojson::object obj;
 *  obj["type"] = picojson::value("customer");
 *  entity_project::Entity* entity = system->CreateEntity(obj);  // Create the entity
 *  csci3081::Customer* customer = entity->AsType<csci3081::Customer>();  // Cast the new entity to a Customer
 *  entity->AddEntity(customer); // Adds the customer to the subsystem
 *  ...
 *  \endcode
 *  \subsection build_run Building and Running
 *  Start by building the Docker image using the premade scripts found in the /bin/ directory
 *  \code{.unparsed}
 *  ./bin/build-env.sh
 *  \endcode
 *  After building the Docker image, run it
 *  \code{.unparsed}
 *  ./bin/run-env.sh
 *  \endcode
 *  Next, navigate into the project directory and build it
 *  \code{.unparsed}
 *  cd project
 *  make
 *  \endcode
 *  Finally, run the server
 *  \code{.unparsed}
 *  ./bin/run.sh
 *  \endcode
 *  You should now be able to navigate to localhost:8081 in your web browser and watch the simulation.
 *  \section uml_sec UML Diagram
 *  Below is the up to date UML class diagram of the project.
 *  <img src="3081ProjectUML.png" style="width: 55vw; min-width: 330px;" />
 *
 */

/*! \page DeliverySchedulerPage DeliveryScheduler Details
 *  Please see the <a href="classcsci3081_1_1DeliveryScheduler.html">DeliveryScheduler</a>
 *  class for a detailed list of functions.
 *
 *  The DeliveryScheduler class is the class in the drone delivery subsystem responsible for
 *  processing orders and dispatching drones to handle orders. Orders are fulfilled in a
 *  first in first out manner using a queue. Here is an example of how to instantiate a
 *  DeliveryScheduler instance and use it to schedule a delivery.
 *  \code{.cpp}
 *  #include <picojson.h>
 *  #include <vector>
 *
 *  #include <EntityProject/entity.h>
 *
 *  #include "delivery_scheduler.h"
 *  #include "customer.h"
 *  #include "package.h"
 *  #include "drone.h"
 *
 *  std::vector<entity_project::Entity*> entities;  // Create vector of pointers to entities
 *
 *  DeliveryScheduler deliveryScheduler(&entities);  // Pass in pointer to entities in our system
 *
 *  picojson::array position0;
 *  position0.push_back(picojson::value(100.0));
 *  position0.push_back(picojson::value(0.0));
 *  position0.push_back(picojson::value(100.0));
 *  picojson::array direction0;
 *  picojson::object details0;
 *  // Construct a Drone with parameters
 *  csci3081::Drone drone0("mydrone", position0, direction0, 50.0, 2.0, details0);
 *
 *  entities.push_back(&drone0);
 *
 *  picojson::array position1;
 *  position1.push_back(picojson::value(-100.0));
 *  position1.push_back(picojson::value(0.0));
 *  position1.push_back(picojson::value(-100.0));
 *  picojson::array direction1;
 *  picojson::object details1;
 *  // Construct a Customer with parameters
 *  csci3081::Customer customer0("lukas", position1, direction1, 2.0, details1);
 *
 *  entities.push_back(&customer0);
 *
 *  picojson::array position2;
 *  position2.push_back(picojson::value(-100.0));
 *  position2.push_back(picojson::value(0.0));
 *  position2.push_back(picojson::value(100.0));
 *  picojson::array direction2;
 *  picojson::object details2;
 *  // Construct a Package with parameters
 *  csci3081::Package package0("mypackage", position2, direction2, 2.0, details2);
 *
 *  entities.push_back(&package0);
 *
 *  picojson::object details3;
 *  // Now, we will schedule the delivery
 *  deliveryScheduler.ScheduleDelivery(&package0, &customer0, details3);
 *  deliveryScheduler.Update(0);
 *  // drone0 should now we assigned to an order containing package0 and customer0
 *  ...
 *  \endcode
 *  It is important to note that the DeliveryScheduler only assigns its orders to drones
 *  after the Update function has been called. Failure to do so will result in the Scheduler
 *  never assigning orders to drones.
 */

/*! \page EntityFactoryPage EntityFactory Details
 *  Please see the <a href="classcsci3081_1_1EntityFactory.html">EntityFactory</a>
 *  class for a detailed list of functions.
 *
 *  The EntityFactory class is the class in the drone delivery subsystem responsible for
 *  constructing entities based on JSON data in the form of a picojson::object. If a field
 *  is not provided then it will be assigned to a default value. The default drone speed
 *  is 30. The default radius for all objects is 1. Furthermore, arrays with fewer than
 *  three entries will be packed with zeros to initialize each entity. Below is an example
 *  of how to construct and use the EntityFactory class.
 *  \code{.cpp}
 *  #include <picojson.h>
 *  #include <vector>
 *
 *  #include <EntityProject/entity.h>
 *
 *  #include "entity_factory.h"
 *  #include "customer.h"
 *  #include "package.h"
 *  #include "drone.h"
 *
 *
 *  picojson::object obj;
 *  obj["type"] = picojson::value("customer");
 *
 *  picojson::array pos;
 *  pos.push_back(picojson::value(1.0));
 *  pos.push_back(picojson::value(2.0));
 *  pos.push_back(picojson::value(3.0));
 *  picojson::array direction;
 *  direction.push_back(picojson::value(0.0));
 *  direction.push_back(picojson::value(1.0));
 *
 *  obj["position"] = picojson::value(pos);
 *  obj["direction"] = picojson::value(direction);
 *  obj["name"] = picojson::value("lukas");
 *  obj["radius"] = picojson::value(2.0);
 *
 *  entity = system->CreateEntity(obj);
 *  customer = entity->AsType<Customer>();
 *  // customer will now have position (1, 2, 3)
 *  // direction (0, 1, 0), name "lukas" and
 *  // radius 2
 *  ...
 *  \endcode
 */

/*! \page DroneSimulationPage DroneSimulation Details
 *  Please see the <a href="classcsci3081_1_1DroneSimulation.html">DroneSimulation</a>
 *  class for a detailed list of functions.
 *
 *  The DroneSimulation class is the concrete implementation of the abstract facade DroneDeliverySystem.
 *  The easy to use interface makes all of the functions almost self explanatory. Below is an example of how
 *  to create a DroneSimulation instance and call some methods.
 *  \code{.cpp}
#include <picojson.h>
#include <vector>

#include <EntityProject/entity.h>

#include "drone_simulation.h"
#include "customer.h"
#include "package.h"
#include "drone.h"
picojson::array position0;
position0.push_back(picojson::value(100.0));
position0.push_back(picojson::value(0.0));
position0.push_back(picojson::value(100.0));
picojson::array direction0;
picojson::object details0;
// Construct a Drone with parameters
csci3081::Drone drone0("mydrone", position0, direction0, 50.0, 2.0, details0);

// Add the entity to the system
system->AddEntity(&drone0);

picojson::array position1;
position1.push_back(picojson::value(100.0));
position1.push_back(picojson::value(0.0));
position1.push_back(picojson::value(-100.0));
picojson::array direction1;
picojson::object details1;
// Construct a Customer with parameters
csci3081::Customer customer0("lukas", position1, direction1, 2.0, details1);

// Add the entity to the system
system->AddEntity(&customer0);

picojson::array position2;
position2.push_back(picojson::value(-100.0));
position2.push_back(picojson::value(0.0));
position2.push_back(picojson::value(100.0));
picojson::array direction2;
picojson::object details2;
// Construct a Package with parameters
csci3081::Package package0("mypackage", position2, direction2, 2.0, details2);

// Add the entity to the system
system->AddEntity(&package0);

system->ScheduleDelivery()

// Schedule a delivery
picojson::object deliveryDetails;
system->ScheduleDelivery(&package0, &customer0, deliveryDetails);

// Update the system by time 1.0 each Update
system->Update(1.0);
system->Update(1.0);
// The drone should move closer to the package
// every update call. All other entities should not move
 *  \endcode
 */
