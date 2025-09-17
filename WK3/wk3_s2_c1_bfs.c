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

typedef struct Queue {
    int* items;
    int front;
    int rear;
    int capacity;
}Queue;

// Graph-related functions
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjLists = (Node**)malloc(vertices * sizeof(Node*));
    graph->visited = (bool*)malloc(vertices * sizeof(bool));
    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = false;
    }
    return graph;
}

Node* createNode(int vertex) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
    // For undirected graph, add edge from dest to src
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

void printGraph(Graph* graph) {
    for (int v = 0; v < graph->numVertices; v++) {
        Node* temp = graph->adjLists[v];
        printf("Adjacency list of vertex %d:", v);
        while (temp) {
            printf(" -> %d", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

// Queue operations
Queue* createQueue(int capacity) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->items = (int*)malloc(capacity * sizeof(int));
    q->front = 0;
    q->rear = -1;
    q->capacity = capacity;
    return q;
}

void enqueue(Queue* q, int value) {
    if (q->rear < q->capacity - 1) {
        q->rear++;
        q->items[q->rear] = value;
    }
}

int dequeue(Queue* q) {
    if (q->front > q->rear) {
        return -1; // Queue empty
    }
    int value = q->items[q->front];
    q->front++;
    return value;
}

bool isQueueEmpty(Queue* q) {
    return q->front > q->rear;
}

// BFS traversal
void BFS(Graph* graph, int startVertex) {
    Queue* queue = createQueue(graph->numVertices);
    for (int i = 0; i < graph->numVertices; i++)
        graph->visited[i] = false;
    graph->visited[startVertex] = true;
    enqueue(queue, startVertex);
    while (!isQueueEmpty(queue)) {
        int currentVertex = dequeue(queue);
        printf("%d ", currentVertex);
        Node* temp = graph->adjLists[currentVertex];
        while (temp) {
            int adjVertex = temp->vertex;
            if (!graph->visited[adjVertex]) {
                graph->visited[adjVertex] = true;
                enqueue(queue, adjVertex);
            }
            temp = temp->next;
        }
    }
    printf("\n");
    free(queue->items);
    free(queue);
}

int main() {
    int vertices = 6;
    Graph* graph = createGraph(vertices);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 5);
    printf("Breadth-First Search starting from vertex 0:\n");
    BFS(graph, 0);
    return 0;
}