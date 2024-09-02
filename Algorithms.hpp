// elnatan100@gmail.com
#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Graph.hpp"

namespace ariel
{
    class Algorithms
    {

    public:
        // Checks if the graph is connected (i.e., there is a path between any two vertices)
        static bool isConnected(const Graph &g);

        // Finds the shortest path between two vertices in the graph
        // Returns a string representation of the path
        static std::string shortestPath(const Graph &g, int start, int end);

        // Checks if the graph contains any cycles
        static bool isContainsCycle(const Graph &g);

        // Determines if the graph is bipartite
        // Returns a string representation of the result
        static std::string isBipartite(const Graph &g);

        // Detects if there is a negative weight cycle in the graph
        // Returns a string representation of the result
        static std::string negativeCycle(const Graph &g);
    };

} // namespace ariel

#endif // ALGORITHMS_HPP
