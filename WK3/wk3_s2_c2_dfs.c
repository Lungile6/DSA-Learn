#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Node and Graph Structures
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    int numVertices;
    Node** adjLists;
    bool* visited;
} Graph;

//Stack Structure for Iterative DFS
typedef struct Stack {
    int* items;
    int top;
    int capacity;
} Stack;

// Graph-related functions
Graph* createGraph(int vertices);
Node* createNode(int vertex);
void addEdge(Graph* graph, int src, int dest);
void printGraph(Graph* graph);

// DFS Iterative
Stack* createStack(int capacity);
void push(Stack* stack, int value);
int pop(Stack* stack);
bool isStackEmpty(Stack* stack);
void DFS_Iterative(Graph* graph, int startVertex);

//Main Function
int main() {
    int vertices = 6;
    Graph* graph = createGraph(vertices);
    
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 5);

    printf("\nIterative Depth-First Search starting from vertex 0:\n");
    graph->visited = calloc(vertices, sizeof(bool));  // Reset visited
    DFS_Iterative(graph, 0);
    
    return 0;
}