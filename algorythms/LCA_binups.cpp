#include <vector>
class staticLCA {
  std::vector<std::vector<int>> binaryUpp;
  std::vector<int> depths;

  void dfs(std::vector<std::vector<int>> &graph, int vertex, int past_vertex) {
    depths[vertex] = depths[past_vertex] + 1;
    binaryUpp[vertex][0] = past_vertex;
    for (int i = 1; i < 30; i++) {
      binaryUpp[vertex][i] = binaryUpp[binaryUpp[vertex][i - 1]][i - 1];
    }
    for (auto to : graph[vertex]) {
      dfs(graph, to, vertex);
    }
  }

  void build(std::vector<std::vector<int>> &graph, int root) {
    depths.resize(graph.size());
    binaryUpp.resize(graph.size(), std::vector<int>(30));
    depths[root] = -1;
    dfs(graph, root, root);
  }

public:
  staticLCA() {}

  staticLCA(std::vector<std::vector<int>> &graph, int root) {
    build(graph, root);
  }

  int get_lca(int a, int b) {
    if (depths[a] < depths[b])
      std::swap(a, b);
    for (int i = 29; i >= 0; i--) {
      if (depths[binaryUpp[a][i]] >= depths[b]) {
        a = binaryUpp[a][i];
      }
    }

    if (a == b)
      return b;

    for (int i = 29; i >= 0; i--) {
      if (binaryUpp[b][i] != binaryUpp[a][i]) {
        b = binaryUpp[b][i];
        a = binaryUpp[a][i];
      }
    }
    return binaryUpp[a][0];
  }

  long long upp(int a, int level) {
    for (int i = 29; i >= 0; i--) {
      if (level >= (1 << i)) {
        a = binaryUpp[a][i];
        level -= (1 << i);
      }
    }
    return a;
  }
};
