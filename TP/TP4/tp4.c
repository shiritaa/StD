// Developer : Shir-Li Kedem

#include <stdio.h>
#include <stdlib.h>
#define size 100

// Function declarations for the queue
typedef struct TQueue {
  int elements[size];
  int head;
  int tail;
} TQueue;


TQueue *create_queue(); // Create a queue
void add_to_queue(TQueue *queue, int); // Add element to queue
int remove_from_queue(TQueue *queue); // Remove element from queue
int is_empty(TQueue *queue); // Check if queue is empty
void print_queue(TQueue *queue); // Print queue


// Function declarations for the node
typedef struct TNode {
  int vertex;
  struct TNode *next;
} TNode;

TNode *create_node(int num); // Create a node


// Function declarations for the graph
typedef struct TGraph {
  int numVertices;
  int *explored;
  TNode **listAdj;
} TGraph;

void print_list(TGraph *graph); // Print adjacency list of graph
void add_edge(TGraph *graph, int vertex1, int vertex2); // Add connection between 2 vertices to graph
void populateGraphFromMatrix(TGraph *graph, int matrixLength, int matrix[][matrixLength]); // Populate graph from matrix


// The BFS function for the adjacency list
// The function receives a graph and a start vertex, and performs a BFS on the
// graph, starting from the start vertex
void BFS(TGraph *graph, int startVertex) {
  TQueue *queue = create_queue();
  graph->explored[startVertex] = 1;
  add_to_queue(queue, startVertex);
  while (!is_empty(queue)) {
    print_queue(queue);
    int vertex = remove_from_queue(queue);
    printf("\nExplored : %d\n", vertex);
    TNode *node = graph->listAdj[vertex];
    while (node) {
      int vertexAdj = node->vertex;
      if (graph->explored[vertexAdj] == 0) {
        graph->explored[vertexAdj] = 1;
        add_to_queue(queue, vertexAdj);
      }
      node = node->next;
    }
  }
}

// The BFS function for the adjacency matrix
// The function is the same as the adjacency list BFS function, except for the
// populateGraphFromMatrix function
void BFS_matrix(TGraph *graph, int matrixLength, int matrix[][matrixLength],
                int startVertex) {
  populateGraphFromMatrix(graph, matrixLength, matrix);
  BFS(graph, startVertex);
}

// The DFS function for the adjacency list
// The function receives a graph and a start vertex, and performs a DFS on the
// graph, starting from the start vertex
void DFS(TGraph *graph, int vertex) {
  TNode *listAdj = graph->listAdj[vertex];
  TNode *n = listAdj;
  graph->explored[vertex] = 1;
  printf("Explored : %d\n", vertex);
  while (n != NULL) {
    int v = n->vertex;
    if (graph->explored[v] == 0) {
      DFS(graph, v);
    }
    n = n->next;
  }
}

// The DFS function for the adjacency matrix
// The function is the same as the adjacency list DFS function, except for the
// populateGraphFromMatrix function
void DFS_matrix(TGraph *graph, int matrixLength, int matrix[][matrixLength],
                int startVertex) {
  populateGraphFromMatrix(graph, matrixLength, matrix);
  DFS(graph, startVertex);
}

// This function creates edges in a graph based on a given adjacency matrix.
 //If there is a 1 in the matrix, it adds an edge between the corresponding 
 //vertices to the graph.
void populateGraphFromMatrix(TGraph *graph, int matrixLength, int matrix[][matrixLength]) {
  for (int i = 0; i < matrixLength; i++) {
    for (int j = 0; j < matrixLength; j++) {
      if (matrix[i][j] == 1) {
        add_edge(graph, i, j);
      }
    }
  }
}

// Create a node
TNode *create_node(int v) {
  TNode *node = malloc(sizeof(TNode));
  node->vertex = v;
  node->next = NULL;
  return node;
}

// Create a graph
TGraph *create_graph(int numVertices) {
  TGraph *graph = malloc(sizeof(TGraph));
  graph->numVertices = numVertices;
  graph->listAdj = malloc(numVertices * sizeof(struct node *));
  graph->explored = malloc(numVertices * sizeof(int));
  int i;
  for (i = 0; i < numVertices; i++) {
    graph->listAdj[i] = NULL;
    graph->explored[i] = 0;
  }
  return graph;
}

// Add edge to graph
void add_edge(TGraph *graph, int vertex1, int vertex2) {
  TNode *node = create_node(vertex2);
  node->next = graph->listAdj[vertex1];
  graph->listAdj[vertex1] = node;
}

// Create a queue
TQueue *create_queue() {
  TQueue *queue = malloc(sizeof(TQueue));
  queue->head = -1;
  queue->tail = -1;
  return queue;
}

// Check if queue is empty
int is_empty(TQueue *queue) {
  if (queue->tail == -1)
    return 1;
  else
    return 0;
}

// Add element to queue
void add_to_queue(TQueue *queue, int num) {
  if (queue->tail == size - 1)
    printf("\nQueue is full.");
  else {
    if (queue->head == -1)
      queue->head = 0;
    queue->tail++;
    queue->elements[queue->tail] = num;
  }
}

// Remove element from queue
int remove_from_queue(TQueue *queue) {
  int element;
  if (is_empty(queue)) {
    printf("TQueue is empty");
    element = -1;
  } else {
    element = queue->elements[queue->head];
    queue->head++;
    if (queue->head > queue->tail) {
      queue->head = queue->tail = -1;
    }
  }
  return element;
}

// Print the queue
void print_queue(TQueue *queue) {
  int i = queue->head;

  if (is_empty(queue)) {
    printf("TQueue is empty");
  } else {
    printf("\nIn queue : ");
    for (i = queue->head; i < queue->tail + 1; i++) {
      printf("%d ", queue->elements[i]);
    }
  }
}

// Print the adjacency list of the graph
void print_list(TGraph *graph) {
  printf("Adjacency list :\n");
  for (int i = 0; i < graph->numVertices; i++) {
    TNode *n = graph->listAdj[i];
    printf("%d : ", i);
    while (n) {
      printf("%d ", n->vertex);
      n = n->next;
    }
    printf("\n");
  }
}

// Print the adjacency matrix of the graph
void print_matrix(int matrixLength, int matrix[][matrixLength]) {
  printf("Adjacency matrix :\n");
  for (int i = 0; i < matrixLength; i++) {
    for (int j = 0; j < matrixLength; j++) {
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }
}

int main() {

  //All these examples with adjacency list/matrix are based on the first exercise of TP4.
  //The graph is the same for all examples and is represented by the adjacency list and the adjacency matrix.

  TGraph *graph = create_graph(7);
  add_edge(graph, 0, 1);
  add_edge(graph, 0, 2);
  add_edge(graph, 1, 4);
  add_edge(graph, 1, 3);
  add_edge(graph, 2, 3);
  add_edge(graph, 2, 5);
  add_edge(graph, 3, 6);
  add_edge(graph, 4, 6);
  add_edge(graph, 5, 6);

  print_list(graph);
  printf("-------------\n");
  printf("BFS algorithm\n");
  printf("-------------\n");
  BFS(graph, 0);
  printf("\n\n\n");

  TGraph *graph2 = create_graph(7);
  add_edge(graph2, 0, 1);
  add_edge(graph2, 0, 2);
  add_edge(graph2, 1, 4);
  add_edge(graph2, 1, 3);
  add_edge(graph2, 2, 3);
  add_edge(graph2, 2, 5);
  add_edge(graph2, 3, 6);
  add_edge(graph2, 4, 6);
  add_edge(graph2, 5, 6);

  print_list(graph2);
  printf("-------------\n");
  printf("DFS algorithm\n");
  printf("-------------\n");
  DFS(graph2, 0);
  printf("\n\n\n");

  TGraph *graph3 = create_graph(7);
  TGraph *graph4 = create_graph(7);
  int matrix[7][7] = {
    {0, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0},
    {0, 0, 0, 1, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 1}, 
    {0, 0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 0}
  };

  print_matrix(7, matrix);
  printf("-------------------------\n");
  printf("BFS algorithm with matrix\n");
  printf("-------------------------\n");
  BFS_matrix(graph3, 7, matrix, 0);
  printf("\n\n\n");

  print_matrix(7, matrix);
  printf("-------------------------\n");
  printf("DFS algorithm with matrix\n");
  printf("-------------------------\n");
  DFS_matrix(graph4, 7, matrix, 0);
  return 0;
}