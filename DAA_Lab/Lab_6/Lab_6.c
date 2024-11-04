//6) Compare the performance of Dijkstra and Bellman ford algorithm for the single source shortest path problem.

#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define INF INT_MAX

// Structure to represent an edge in the graph
struct Edge {
    int src, dest, weight;
};

// Function to find the vertex with the minimum distance value
int minDistance(int dist[], bool sptSet[], int V) {
    int min = INF, min_index;
    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}

// Dijkstra's Algorithm using adjacency matrix
void dijkstra(int graph[10][10], int src, int V) {
    int dist[V];  // Output array. dist[i] will hold the shortest distance from src to i
    bool sptSet[V]; // sptSet[i] will be true if vertex i is included in shortest path tree

    // Initialize all distances as INFINITE and sptSet[] as false
    for (int i = 0; i < V; i++)
        dist[i] = INF, sptSet[i] = false;

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet, V); // Pick the minimum distance vertex

        sptSet[u] = true; // Mark the picked vertex as processed

        // Update dist value of the adjacent vertices of the picked vertex
        for (int v = 0; v < V; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INF && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    // Print the calculated shortest distances
    printf("Dijkstra Algorithm:\n");
    for (int i = 0; i < V; i++)
        printf("Vertex %d -> Distance from source: %d\n", i, dist[i]);
}

// Bellman-Ford Algorithm
void bellmanFord(struct Edge edges[], int V, int E, int src) {
    int dist[V];

    // Step 1: Initialize distances from src to all other vertices as INFINITE
    for (int i = 0; i < V; i++)
        dist[i] = INF;
    dist[src] = 0;

    // Step 2: Relax all edges |V| - 1 times
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int weight = edges[j].weight;
            if (dist[u] != INF && dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight;
        }
    }

    // Step 3: Check for negative-weight cycles
    for (int i = 0; i < E; i++) {
        int u = edges[i].src;
        int v = edges[i].dest;
        int weight = edges[i].weight;
        if (dist[u] != INF && dist[u] + weight < dist[v]) {
            printf("Graph contains negative weight cycle\n");
            return;
        }
    }

    // Print the calculated shortest distances
    printf("Bellman-Ford Algorithm:\n");
    for (int i = 0; i < V; i++)
        printf("Vertex %d -> Distance from source: %d\n", i, dist[i]);
}

int main() {
    int V = 5; // Number of vertices

    // Graph representation using adjacency matrix for Dijkstra's algorithm
    int graph[10][10] = {
        {0, 6, 0, 1, 0},
        {6, 0, 5, 2, 2},
        {0, 5, 0, 0, 5},
        {1, 2, 0, 0, 1},
        {0, 2, 5, 1, 0}
    };

    // Graph representation using Edge list for Bellman-Ford algorithm
    int E = 8; // Number of edges
    struct Edge edges[] = {
        {0, 1, 6}, {0, 3, 1}, {1, 2, 5}, {1, 3, 2},
        {1, 4, 2}, {2, 4, 5}, {3, 4, 1}, {4, 2, 5}
    };

    int source = 0; // Source vertex

    // Run Dijkstra's algorithm
    dijkstra(graph, source, V);

    // Run Bellman-Ford algorithm
    bellmanFord(edges, V, E, source);

    return 0;
}