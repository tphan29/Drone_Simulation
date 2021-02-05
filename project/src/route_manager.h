#ifndef ROUTE_MANAGER_H_
#define ROUTE_MANAGER_H_

#include <EntityProject/graph.h>

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <limits>
#include <algorithm>
#include <tuple>

#include "math.h"  // NOLINT

namespace csci3081 {
/**
 * The RouteManager class is the class responsible for calculating the shortest path 
 * between two entity_project::IGraphNode nodes using the given entity_project::IGraph 
 * graph using the graph traversal algorithm A*, a specialized variant of dijkstra's 
 * algorithm. All of the functions and members of this class are static, so this class
 * should not be instantiated.
 */
class RouteManager {
 public:
    /**
     * Sets the underlying graph object of the RouteManager to a certain entity_project::IGraph
     * @param graph const pointer to an entity_project::IGraph object
     */
    static void SetGraph(const entity_project::IGraph* graph) { graph_ = graph; }
    /**
     * Returns the shortest path from a source point to a destination point.
     * @param src const reference to a tuple of floats (x, y, z) refering to starting point
     * of the route
     * @param dest const reference to a tuple of floats (x, y, z) refering to the destination
     * point of the route
     * @returns the shortest path as a vector of const pointers to
     * entity_project::IGraphNode objects
     */
    static std::vector<const entity_project::IGraphNode*> GetRoute(
        const std::tuple<float, float, float>& src,
        const std::tuple<float, float, float>& dest,
        const entity_project::IGraph* graph = nullptr);
 private:
    static const entity_project::IGraph* graph_;
};

}  // namespace csci3081
#endif
