#include "route_manager.h"  // NOLINT

namespace csci3081 {
    const entity_project::IGraph* RouteManager::graph_ = nullptr;

    std::vector<const entity_project::IGraphNode*> RouteManager::GetRoute(
        const std::tuple<float, float, float>& src,
        const std::tuple<float, float, float>& dest,
        const entity_project::IGraph* graph) {
        if (graph == nullptr) {
            graph = graph_;
        }
        if (graph == nullptr) {
            return {};
        }

        const entity_project::IGraphNode* srcNode = nullptr;
        const entity_project::IGraphNode* destNode = nullptr;

        float minSrcDist = std::numeric_limits<float>::max();
        float minDestDist = std::numeric_limits<float>::max();

        for (auto n : graph->GetNodes()) {
            float distToSrc = Dist(std::get<0>(src), std::get<1>(src), std::get<2>(src),
                n->GetPosition()[0], n->GetPosition()[1], n->GetPosition()[2]);
            float distToDest = Dist(std::get<0>(dest), std::get<1>(dest), std::get<2>(dest),
                n->GetPosition()[0], n->GetPosition()[1], n->GetPosition()[2]);

            if (distToSrc < minSrcDist) {
                minSrcDist = distToSrc;
                srcNode = n;
            }
            if (distToDest < minDestDist) {
                minDestDist = distToDest;
                destNode = n;
            }
        }

        if (srcNode == nullptr) {
            return {};  // Graph is empty return
        }

        // Traveral map. Maps nodes to nodes that came before it
        std::unordered_map<const entity_project::IGraphNode*,
            const entity_project::IGraphNode*> traversalMap;

        std::unordered_set<const entity_project::IGraphNode*> uncoveredSet;
        std::unordered_map<const entity_project::IGraphNode*, float> costMap;
        std::unordered_map<const entity_project::IGraphNode*, float> estimatedCostMap;

        uncoveredSet.insert(srcNode);

        costMap[srcNode] = 0;

        estimatedCostMap[srcNode] = Dist(srcNode->GetPosition()[0], srcNode->GetPosition()[1],
            srcNode->GetPosition()[2], destNode->GetPosition()[0], destNode->GetPosition()[1],
            destNode->GetPosition()[2]);

        while (true) {
            if (uncoveredSet.empty()) {
                return {};  // No solution
            }
            const entity_project::IGraphNode* currentNode = nullptr;
            float lowestEstimatedCost = std::numeric_limits<float>::max();
            for (auto node : uncoveredSet) {
                auto it = estimatedCostMap.find(node);
                if (it != estimatedCostMap.end() && it->second < lowestEstimatedCost) {
                    lowestEstimatedCost = it->second;
                    currentNode = node;
                }
            }
            if (currentNode == nullptr) {
                return {};  // This shouldn't happen
            } else if (currentNode == destNode) {
                break;
            }
            uncoveredSet.erase(currentNode);
            float cost = costMap[currentNode];
            for (auto neighbor : currentNode->GetNeighbors()) {
                float tentativeCost = cost + Dist(currentNode->GetPosition()[0],
                    currentNode->GetPosition()[1], currentNode->GetPosition()[2],
                    neighbor->GetPosition()[0], neighbor->GetPosition()[1],
                    neighbor->GetPosition()[2]);
                auto it = costMap.find(neighbor);
                if (it == costMap.end() || tentativeCost < it->second) {
                    traversalMap[neighbor] = currentNode;
                    costMap[neighbor] = tentativeCost;
                    estimatedCostMap[neighbor] = tentativeCost + Dist(neighbor->GetPosition()[0],
                        neighbor->GetPosition()[1], neighbor->GetPosition()[2],
                        destNode->GetPosition()[0], destNode->GetPosition()[1],
                        destNode->GetPosition()[2]);
                    uncoveredSet.insert(neighbor);
                }
            }
        }

        std::vector<const entity_project::IGraphNode*> solution;
        auto currNode = destNode;
        solution.push_back(currNode);
        while (currNode != srcNode) {
            auto it = traversalMap.find(currNode);
            if (it == traversalMap.end()) {
                return {};  // Shouldn't happen
            }
            currNode = it->second;
            solution.push_back(currNode);
        }
        std::reverse(solution.begin(), solution.end());
        return solution;
    }
}  // namespace csci3081
