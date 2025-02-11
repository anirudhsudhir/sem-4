#include <stdbool.h>
#include <stdio.h>

#define MAX_SIZE 10

typedef struct {
  int cost;
  int path[MAX_SIZE + 1];
  int path_length;
  bool exists;
} Result;

bool is_visited(bool visited[], int n, int vertex) { return visited[vertex]; }

int calculate_cost(int graph[][MAX_SIZE], int path[], int length) {
  int cost = 0;
  for (int i = 0; i < length - 1; i++) {
    if (graph[path[i]][path[i + 1]] == -1)
      return -1;
    cost += graph[path[i]][path[i + 1]];
  }
  return cost;
}

void copy_path(int dest[], int src[], int length) {
  for (int i = 0; i < length; i++) {
    dest[i] = src[i];
  }
}

void find_path(int graph[][MAX_SIZE], int n, int current_vertex, bool visited[],
               int current_path[], int path_length, Result *best_result) {

  current_path[path_length] = current_vertex;
  visited[current_vertex] = true;
  path_length++;

  if (path_length == n) {
    if (graph[current_vertex][0] != -1) {
      current_path[path_length] = 0;
      int total_cost = calculate_cost(graph, current_path, path_length + 1);

      if (!best_result->exists ||
          (total_cost != -1 &&
           (best_result->cost > total_cost ||
            (best_result->cost == total_cost &&
             path_length + 1 <= best_result->path_length)))) {
        best_result->exists = true;
        best_result->cost = total_cost;
        best_result->path_length = path_length + 1;
        copy_path(best_result->path, current_path, path_length + 1);
      }
    }
  } else {
    for (int i = 0; i < n; i++) {
      if (!is_visited(visited, n, i) && graph[current_vertex][i] != -1) {
        find_path(graph, n, i, visited, current_path, path_length, best_result);
      }
    }
  }

  visited[current_vertex] = false;
}

Result solve_tsp(int n, int graph[][MAX_SIZE]) {
  Result result = {0, {0}, 0, false};
  bool visited[MAX_SIZE] = {false};
  int current_path[MAX_SIZE + 1] = {0};

  find_path(graph, n, 0, visited, current_path, 0, &result);

  return result;
}

int main() {
  int n;
  scanf("%d", &n);

  int graph[MAX_SIZE][MAX_SIZE];

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      scanf("%d", &graph[i][j]);
    }
  }

  Result result = solve_tsp(n, graph);

  if (!result.exists || result.cost == -1) {
    printf("path does not exist\n");
  } else {
    printf("minimum cost: %d\n", result.cost);
    printf("optimal path: ");
    for (int i = 0; i < result.path_length; i++) {
      printf("%d", result.path[i]);
      if (i < result.path_length - 1)
        printf(" ");
    }
    printf("\n");
  }

  return 0;
}
