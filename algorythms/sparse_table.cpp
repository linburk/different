#include "vector"
class sparseTable {
  std::vector<std::vector<long long>> ST;
  void build(const std::vector<long long> &arr) {
    ST.resize(32 - __builtin_clz(arr.size() + 1),
              std::vector<long long>(arr.size()));
    ST[0] = arr;
    for (int i = 0; i + 1 < 32 - __builtin_clz(arr.size() + 1); i++) {
      for (int j = 0; j < arr.size() - (1 << i); j++) {
        ST[i + 1][j] = std::min(ST[i][j], ST[i][j + (1 << i)]);
      }
    }
  }

public:
  sparseTable(const std::vector<long long> &arr) { build(arr); }

  const int get(int l, int r) {
    int d = 31 - __builtin_clz(r - l);
    return std::min(ST[d][l], ST[d][r - (1 << d)]);
  }
  const int size() { return ST[0].size(); }
};
