/**
 * Dijikstras.c
 * 
 * @author Perry David Ralston Jr
 * @date Spring Quarter 2019
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

enum v_status {tree, fringe, unseen};

struct vertex {
  //adjacency list with edge weights at corresponding index
  enum v_status status;
  int parent;
  double distance;
};
int notEmpty(struct vertex* pQueue, int size) {
  for (int i = 0; i < size; ++i) {
    if (pQueue[i].status == fringe) return 1;
  }
  return 0;
}

int getMin(struct vertex* pQueue, int size) {
  double min = INFINITY;
  int rc = 0;
  for (int i = 0; i < size; ++i) {
    if (pQueue[i].status == fringe && pQueue[i].distance < min) {
      min = pQueue[i].distance;
      rc = i;
    }
  }
  return rc;
}

void print(struct vertex* pQueue, int size) {
  printf("Index:");
  for (int i = 0; i < size; ++i) {
    printf("%9c", i + 'A');
  }
  printf("\nDistance:");
  for (int i = 0; i < size; ++i) {
    printf("%9.01lf",pQueue[i].distance);
  }
  printf("\nParent:");
  for (int i = 0; i < size; ++i) {
    printf("%9c", pQueue[i].parent + 'A');
  }
  printf("\nStatus:");
  for (int i = 0; i < size; ++i) {
    printf("%9d", pQueue[i].status);
  }
  printf("\n\n");
}

int main() {
  int num_vertex;
  printf("Lets create a graph, how many verticies in your graph? ");
  scanf("%d", &num_vertex);
  double* graph[num_vertex];
  for (int i = 0; i < num_vertex; ++i) {
    graph[i] = calloc(num_vertex, sizeof(int));
  }
  for (int i = 0; i < num_vertex; ++i) {
    for (int j = 0; j < num_vertex; ++j) {
      graph[i][j] = INFINITY;
    }
  }
  struct vertex pQueue[num_vertex];
  printf("Lets add some adajencies." 
    " Please enter source, destination and weight"
    ", a negative value will end input: ");
  int source, destination;
  double weight;
  for(;;) {
    scanf("%d %d %lf", &source, &destination, &weight);
    if (source < 0 || destination < 0) break;
    if (num_vertex < source || num_vertex < destination) {
      printf("vertex not in range, try again.\n"
         "Verticies must be between 1 and %d inclusive.", 
         num_vertex);
      continue;
    }
    if (weight < 0) {
      printf("Weights must be positive, try again");
      continue;
    }
    graph[source-1][destination-1] = weight;
  }
  //initialize
  for (int i = 0; i < num_vertex; ++i) {
    pQueue[i].distance = INFINITY;
    pQueue[i].parent = -1;
    pQueue[i].status = unseen;
  }
  for(;;) {
    printf("Which index would you like to start Dijikstra's? ");
    scanf("%d", &source);
    if(source > 0 && source <= num_vertex) break;
    printf("Source must be between 1 and %d inclusive", num_vertex);
  }
  pQueue[source - 1].distance = 0;
  pQueue[source - 1].status = fringe;
  printf("\n");
  print(pQueue, num_vertex);
  while(notEmpty(pQueue, num_vertex)) {
    int current = getMin(pQueue, num_vertex);
    printf("min is: %d\n", current);
    pQueue[current].status = tree;
    for (int i = 0; i < num_vertex; ++i) {
      if(graph[current][i] < INFINITY 
        && pQueue[i].status != tree) {
        if(graph[current][i] + pQueue[current].distance 
          < pQueue[i].distance) {
          pQueue[i].parent = current;
          pQueue[i].distance = graph[current][i] 
            + pQueue[current].distance;
          pQueue[i].status = fringe;
        }
      }
    }
    print(pQueue, num_vertex);
  }
  print(pQueue, num_vertex);
  return EXIT_SUCCESS;
}
 