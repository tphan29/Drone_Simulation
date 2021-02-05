### Feedback for Iteration 1

Run on November 04, 19:33:46 PM.

+ :heavy_check_mark:  Run git ls-remote to check for existence of specific branch- Branch release found

+ :heavy_check_mark:  Checkout release branch.




### Necessary Files and Structure

+ :heavy_check_mark:  Check that directory "project" exists.

+ :heavy_check_mark:  Check that directory "project/bin" exists.

+ :heavy_check_mark:  Check that directory "project/docs" exists.

+ :heavy_check_mark:  Check that directory "project/src" exists.

+ :heavy_check_mark:  Check that directory "project/tests" exists.

+ :heavy_check_mark:  Check that directory "project/web" exists.

+ :heavy_check_mark:  Check that file "project/Makefile" exists.

+ :heavy_check_mark:  Check that file "project/docs/Doxyfile" exists.

+ :heavy_check_mark:  Check that file/directory "project/docs/html" does not exist.

+ :heavy_check_mark:  Check that file/directory "project/docs/latex" does not exist.

+ :heavy_check_mark:  Change into directory "project".

+ :heavy_check_mark:  overwriting makefile



+ :heavy_check_mark:  overwriting makefile



+ :heavy_check_mark:  Copy file "Copying official project makefile".



+ :heavy_check_mark:  Change into directory "..".


### Google Style Compliance

+ :heavy_check_mark:  overwriting config



+ :heavy_check_mark:  overwriting cpplint



+ :heavy_check_mark:  overwriting cpplint



+ :heavy_check_mark:  Making sure we can access cpplint



+ :heavy_check_mark:  Making sure we can access cpplint



+ :heavy_check_mark:  Making sure we can access cpplint config



+ :heavy_check_mark:  Cpplint checking for for Google C++ compliance


### Doxygen

+ :heavy_check_mark:  Change into directory "project/docs".

+ :heavy_check_mark:  Generating documentation by running doxygen

+ :heavy_check_mark:  Check that directory "html" exists.

+ :heavy_check_mark:  Check that directory "latex" exists.

+ :heavy_check_mark:  Change into directory "../../".


### Compile Local Tests

+ :heavy_check_mark:  Change into directory "project".

+ :heavy_check_mark:  Check that make clean compiles.



+ :heavy_check_mark:  Check that make compiles.



+ :heavy_check_mark:  Dynamic Check that file exists.

+ :heavy_check_mark:  Check that make test compiles.



+ :heavy_check_mark:  Dynamic Check that file exists.

+ :heavy_check_mark:  Change into directory "..".

+ :heavy_check_mark:  Get all google tests.
    25 tests found.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: CustomerTest.ConstructCustomer.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: CustomerTest.UpdateCustomer.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: CustomerTest.DynamicCustomer.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: DroneTest.DroneConstruct.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: DroneTest.DroneOrder.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: DroneTest.DroneRoute.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: DroneTest.DroneUpdate.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: EntityObservableTest.AddObserver.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: EntityObservableTest.RemoveObserver.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: FactoryTest.DroneCreated.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: FactoryTest.CustomerCreated.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: FactoryTest.PackageCreated.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: PackageTest.ConstructPackage.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: PackageTest.UpdatePackage.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: PackageTest.DynamicPackage.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: SchedulerTest.ScheduleDelivery.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: SchedulerTest.ScheduleCloseDelivery.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: SimulationTest.CreateEntityDrone.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: SimulationTest.CreateEntityPackage.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: SimulationTest.CreateEntityCustomer.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: SimulationTest.AddEntity.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: SimulationTest.ScheduleDelivery.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: SimulationTest.AddObserver.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: SimulationTest.RemoveObserver.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: SimulationTest.Update.



+ :heavy_check_mark:  At least 12 tests passed.


### Compile Official Tests

+ :heavy_check_mark:  Change into directory "project".

+ :heavy_check_mark:  overwriting tests directory



+ :heavy_check_mark:  Copy directory "Copying official tests".



+ :heavy_check_mark:  Check that make clean compiles.



+ :heavy_check_mark:  Check that make compiles.



+ :heavy_check_mark:  Dynamic Check that file exists.

+ :heavy_check_mark:  Check that make test compiles.



+ :heavy_check_mark:  Dynamic Check that file exists.

+ :heavy_check_mark:  Change into directory "..".

+ :heavy_check_mark:  Get all google tests.
    31 tests found.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: CustomerTests.DefaultConstructorTest.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: DroneSimulationTests.DefaultConstructorTest.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: DroneSimulationTests.AddEntity.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: DroneSimulationTests.ScheduleDelivery.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: DroneSimulationTests.DroneMovesWhenScheduled.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: DroneSimulationTests.DroneMovesTowardsPackage.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: DroneSimulationTests.DroneMovesPackage.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: DroneSimulationTests.AssigningPackageWithoutDrone.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: DroneSimulationTests.AssigningPackageNotInSimulation.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: DroneTests.DefaultConstructorTest.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: BoundaryFactoryTest.EntitiesWithNoType.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: BoundaryFactoryTest.EntitiesWithNothingSet.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: PackageTests.DefaultConstructorTest.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: SharedFactoryTests/FactoryTest.EntityCreated/0.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: SharedFactoryTests/FactoryTest.EntityCreated/1.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: SharedFactoryTests/FactoryTest.EntityCreated/2.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: SharedFactoryTests/FactoryTest.EntityCreatedWithPosition/0.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: SharedFactoryTests/FactoryTest.EntityCreatedWithPosition/1.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: SharedFactoryTests/FactoryTest.EntityCreatedWithPosition/2.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: SharedFactoryTests/FactoryTest.EntitiesHaveDifferentIDs/0.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: SharedFactoryTests/FactoryTest.EntitiesHaveDifferentIDs/1.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: SharedFactoryTests/FactoryTest.EntitiesHaveDifferentIDs/2.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: SharedFactoryTests/FactoryTest.EntityCreatedWithPositionBoundary/0.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: SharedFactoryTests/FactoryTest.EntityCreatedWithPositionBoundary/1.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: SharedFactoryTests/FactoryTest.EntityCreatedWithPositionBoundary/2.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: SharedFactoryTests/FactoryTest.EntityCreatedWithPositionBoundary2/0.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: SharedFactoryTests/FactoryTest.EntityCreatedWithPositionBoundary2/1.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: SharedFactoryTests/FactoryTest.EntityCreatedWithPositionBoundary2/2.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: SharedFactoryTests/FactoryTest.EntityCreatedWithPositionBoundary3/0.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: SharedFactoryTests/FactoryTest.EntityCreatedWithPositionBoundary3/1.



+ :heavy_check_mark:  Check that a GoogleTest test passes.
    passes the test: SharedFactoryTests/FactoryTest.EntityCreatedWithPositionBoundary3/2.



+ :heavy_check_mark:  100.0% of the tests passed. Expected at least 100%.

+ :heavy_check_mark:  Change into directory "project".


### Test Memory Leaks

+ :heavy_check_mark:  Valgrind executed successfully



+ :heavy_check_mark:  no memory leaks

+ :heavy_check_mark:  Check that make clean compiles.



+ :heavy_check_mark:  Change into directory "..".

+ :heavy_check_mark:  Check that file "project/src/drone.cc" exists.

+ :heavy_check_mark:  Check that file "project/src/package.cc" exists.

+ :heavy_check_mark:  Check that file "project/src/drone_simulation.cc" exists.

+ :heavy_check_mark:  Check that file "project/src/customer.cc" exists.

