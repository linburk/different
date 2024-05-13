#include <vector>
template <typename T, bool (*comparator)(const T &, const T &)>
class sparseTable {
  std::vector<std::vector<T>> ST;
  void build(const std::vector<T> &arr) {
    ST.resize(32 - __builtin_clz(arr.size() + 1), std::vector<T>(arr.size()));
    ST[0] = arr;
    for (int i = 0; i + 1 < 32 - __builtin_clz(arr.size() + 1); i++) {
      for (int j = 0; j < arr.size() - (1 << i); j++) {
        ST[i + 1][j] =
            (comparator(ST[i][j], ST[i][j + (1 << i)]) ? ST[i][j]
                                                       : ST[i][j + (1 << i)]);
      }
    }
  }

public:
  sparseTable() {}

  sparseTable(const std::vector<T> &arr) { build(arr); }

  const T get(int l, int r) {
    int d = 31 - __builtin_clz(r - l);
    return (comparator(ST[d][l], ST[d][r - (1 << d)]) ? ST[d][l]
                                                      : ST[d][r - (1 << d)]);
  }
  const int size() { return ST[0].size(); }

  void operator()(std::vector<T> &arr) { build(arr); }
};

class staticLCA {
  inline static bool comp(const std::pair<int, int> &a,
                          const std::pair<int, int> &b) {
    return (a.first < b.first ? 1 : 0);
  }
  std::vector<std::pair<int, int>> euler_tour;
  std::vector<int> first_enter, last_enter;

  sparseTable<std::pair<int, int>, comp> RMQ;

  void dfs(std::vector<std::vector<int>> &gr, int v, int depth) {
    first_enter[v] = euler_tour.size();
    euler_tour.push_back(std::make_pair(depth, v));
    for (auto to : gr[v]) {
      dfs(gr, to, depth + 1);
      euler_tour.push_back(std::make_pair(depth, v));
    }
    last_enter[v] = euler_tour.size();
  }

  void build(std::vector<std::vector<int>> &graph, int root) {

    first_enter.resize(graph.size());
    last_enter.resize(graph.size());
    dfs(graph, root, 0);
    RMQ(euler_tour);
  }

public:
  staticLCA(std::vector<std::vector<int>> &graph, int root) {
    build(graph, root);
  }

  int get(int u, int v) {
    return RMQ
        .get(std::min(first_enter[u], first_enter[v]),
             std::max(last_enter[u], last_enter[v]))
        .second;
  }
#if 0
    bool is_ancestor(int _anc, int v){
         return tin[_anc] < tin[v] && tin[v] < tout[v] && tout[v] < tout[_anc];
    }
#endif
};
