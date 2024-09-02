// elnatan100@gmail.com
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>

namespace ariel
{
    extern const std::string RED;
    extern const std::string RESET;

    class Graph
    {
    private:
        // Adjacency matrix representing the graph
        std::vector<std::vector<int>> adjacency_matrix;

        // Number of vertices in the graph
        int num_vertices;

        // Number of edges in the graph
        int num_edges;

        // Boolean flag indicating if the graph is directed
        bool isDirect;

        // Helper function to check if 'other' is a submatrix of the current graph
        bool isSubmatrix(const Graph &other) const;

        // Helper function to check if the adjacency matrices of the current and 'other' graphs are equal
        bool checkIfMatrixEquel(const Graph &other) const;

    public:
        // Default constructor
        Graph();

        // Loads the graph from an adjacency matrix
        void loadGraph(const std::vector<std::vector<int>> &matrix);

        // Prints the adjacency matrix of the graph
        void printGraph() const;

        // Checks if the graph is directed
        void checkIfDirect();

        // Returns whether the graph is directed
        bool getDirect() const;

        // Returns the number of edges in the graph
        int getNumEdges() const;

        // Returns the number of vertices in the graph
        int getNumVertices() const;

        // Returns the adjacency matrix of the graph
        std::vector<std::vector<int>> getAdjacencyMatrix() const;

        // Scales the graph by multiplying each element of the adjacency matrix by a scalar
        Graph operator*(int scalar) const;

        // Scales the graph in place by multiplying each element of the adjacency matrix by a scalar
        Graph &operator*=(int scalar);

        // Creates a new graph where each element of the adjacency matrix is divided by a scalar
        Graph operator/(int scalar) const;

        // Scales down the graph in place by dividing each element of the adjacency matrix by a scalar
        Graph &operator/=(int scalar);

        // Multiplies the adjacency matrix of the current graph with that of another graph
        Graph operator*(const Graph &other) const;

        // Adds the adjacency matrix of the current graph to that of another graph
        Graph operator+(const Graph &other) const;

        // Adds the adjacency matrix of another graph to the current graph in place
        Graph &operator+=(const Graph &other);

        // Subtracts the adjacency matrix of another graph from the current graph
        Graph operator-(const Graph &other) const;

        // Subtracts the adjacency matrix of the current graph by another graph's adjacency matrix in place
        Graph &operator-=(const Graph &other);

        // Unary plus operator (identity operation)
        Graph operator+() const;

        // Unary minus operator (negates all elements in the adjacency matrix)
        Graph operator-() const;

        // Overloaded increment operators
        Graph &operator++();   // Pre-increment
        Graph operator++(int); // Post-increment

        // Overloaded decrement operators
        Graph &operator--();   // Pre-decrement
        Graph operator--(int); // Post-decrement

        // Overloaded stream insertion operator for printing the graph
        friend std::ostream &operator<<(std::ostream &os, const Graph &graph);

        // Comparison operators
        bool operator>(const Graph &other) const;
        bool operator>=(const Graph &other) const;
        bool operator<(const Graph &other) const;
        bool operator<=(const Graph &other) const;
        bool operator==(const Graph &other) const;
        bool operator!=(const Graph &other) const;
    };
}

#endif // GRAPH_HPP
