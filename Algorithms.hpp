#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Graph.hpp"

namespace ariel
{

    class Algorithms
    {
    private:
    public:
        static bool isConnected(const Graph &g);
        static std::string shortestPath(const Graph &g, int start, int end);
        static bool isContainsCycle(const Graph &g);
        static std::string isBipartite(const Graph &g);
    };

} // namespace ariel

#endif // ALGORITHMS_HPP