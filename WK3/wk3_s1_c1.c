#include <stdio.h>
#include <stdlib.h>

// Maximum number of nodes our graph can have
#define MAX_NODES 10

// Our simple graph structure
typedef struct {
    int numNodes;                      // How many nodes are in the graph
    int matrix[MAX_NODES][MAX_NODES];  // Adjacency matrix
    char labels[MAX_NODES];            // Node labels (A, B, C, etc.)
} Graph;

// Function to create a new empty graph
Graph* createGraph() {
    // Allocate memory for the graph
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    
    // Initialize the graph
    graph->numNodes = 0;
    
    // Set all matrix values to 0 (no connections)
    for (int i = 0; i < MAX_NODES; i++) {
        for (int j = 0; j < MAX_NODES; j++) {
            graph->matrix[i][j] = 0;
        }
    }
    
    return graph;
}

// Function to add a new node to the graph
void addNode(Graph* graph, char label) {
    // Check if we have space for more nodes
    if (graph->numNodes >= MAX_NODES) {
        printf("Cannot add more nodes, the graph is full!\n");
        return;
    }
    
    // Add the node
    graph->labels[graph->numNodes] = label;
    graph->numNodes++;
    
    printf("Added node %c\n", label);
}

// Function to add an edge between two nodes
void addEdge(Graph* graph, int from, int to, int weight) {
    // Check if the nodes exist
    if (from < 0 || from >= graph->numNodes || to < 0 || to >= graph->numNodes) {
        printf("Cannot add edge - invalid node number!\n");
        return;
    }
    
    // Add the edge (update the matrix)
    graph->matrix[from][to] = weight;
    graph->matrix[to][from] = weight;  // For undirected graph
    
    printf("Added edge from %c to %c with weight %d\n", 
           graph->labels[from], graph->labels[to], weight);
}

// Function to display the adjacency matrix
void displayMatrix(Graph* graph) {
    printf("\nAdjacency Matrix:\n");
    
    // Print the column headers (node labels)
    printf("  ");
    for (int i = 0; i < graph->numNodes; i++) {
        printf("%c ", graph->labels[i]);
    }
    printf("\n");
    
    // Print each row
    for (int i = 0; i < graph->numNodes; i++) {
        printf("%c ", graph->labels[i]);
        for (int j = 0; j < graph->numNodes; j++) {
            printf("%d ", graph->matrix[i][j]);
        }
        printf("\n");
    }
}

// Main function to test our graph
int main() {
    // Create a new graph
    printf("Creating a new graph...\n");
    Graph* myGraph = createGraph();
    
    // Add some nodes
    addNode(myGraph, 'A'); // Index 0
    addNode(myGraph, 'B'); // Index 1
    addNode(myGraph, 'C'); // Index 2
    addNode(myGraph, 'D'); // Index 3
    
    // Add edges between nodes
    addEdge(myGraph, 0, 1, 5); // A to B with weight 5
    addEdge(myGraph, 0, 2, 3); // A to C with weight 3
    addEdge(myGraph, 1, 2, 1); // B to C with weight 1
    addEdge(myGraph, 2, 3, 8); // C to D with weight 8
    
    // Display the adjacency matrix
    //displayMatrix(myGraph);
    
    // Free the allocated memory
    free(myGraph);
    
    return 0;
}