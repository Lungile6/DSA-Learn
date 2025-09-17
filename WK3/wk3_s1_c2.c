#include <stdio.h>
#include <stdlib.h>

// Structure for an adjacency list node
struct Node {
    int dest;           // Destination vertex number
    int weight;         // Weight of the edge (for weighted graphs)
    struct Node* next;  // Pointer to the next node in the list
};

// Structure to represent an adjacency list
struct AdjList {
    struct Node* head;
};

// Structure to represent a graph
struct Graph {
    int numVertices;
    struct AdjList* array;
};

struct Node* createNode(int dest, int weight) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int numVertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = numVertices;
    graph->array = (struct AdjList*)malloc(numVertices * sizeof(struct AdjList));
    for (int i = 0; i < numVertices; i++) {
        graph->array[i].head = NULL;
    }
    return graph;
}

void addEdge(struct Graph* graph, int src, int dest, int weight) {
    // Add edge from src to dest
    struct Node* newNode = createNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
    // For undirected graph, add edge from dest to src
    newNode = createNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

void printGraph(struct Graph* graph) {
    printf("Adjacency List Representation of the Graph:\n");
    for (int v = 0; v < graph->numVertices; v++) {
        struct Node* pCrawl = graph->array[v].head;
        printf("Vertex %d:", v);
        while (pCrawl) {
            printf(" -> %d(w=%d)", pCrawl->dest, pCrawl->weight);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}


void freeGraph(struct Graph* graph) {
    for (int v = 0; v < graph->numVertices; v++) {
        struct Node* curr = graph->array[v].head;
        while (curr) {
            struct Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(graph->array);
    free(graph);
}

int main() {
    // Sample graph with 5 vertices
    int numVertices = 5;
    // Create a graph
    struct Graph* graph = createGraph(numVertices);
    // Sample edges to be added
    // Edge 0-1 with weight 10
    addEdge(graph, 0, 1, 10);
    // Edge 0-4 with weight 20
    addEdge(graph, 0, 4, 20);
    // Edge 1-2 with weight 30
    addEdge(graph, 1, 2, 30);
    // Edge 1-3 with weight 40
    addEdge(graph, 1, 3, 40);
    // Edge 1-4 with weight 50
    addEdge(graph, 1, 4, 50);
    // Edge 2-3 with weight 60
    addEdge(graph, 2, 3, 60);
    // Edge 3-4 with weight 70
    addEdge(graph, 3, 4, 70);
    // Print the graph
    printGraph(graph);
    // Free the allocated memory
    freeGraph(graph);
    /*
    Test:
    Vertices: 5 (0,1,2,3,4)
    Edges:
    0-1 (10), 0-4 (20), 1-2 (30), 1-3 (40), 1-4 (50), 2-3 (60), 3-4 (70)
    */
    return 0;
}