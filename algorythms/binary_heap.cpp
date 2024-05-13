#include <vector>

template <typename T, bool (*comparator)(const T, const T)> class binary_heap {
  std::vector<T> tree;
  void sift_up(size_t node) {
    while (node > 1 and comparator(tree[node], tree[node / 2])) {
      swap(tree[node], tree[node / 2]);
      node /= 2;
    }
  }
  void sift_down(size_t node) {
    size_t maxindex = node;
    for (size_t son = 2 * node; son <= 2 * node + 1; son++) {
      if (son < tree.size() && tree[son] > tree[maxindex])
        maxindex = son;
    }
    if (maxindex == node)
      return;
    swap(tree[maxindex], tree[node]);
    sift_down(maxindex);
  }
  size_t heap_size = 0;

public:
  binary_heap() {
    tree.reserve(1E6 + 1);
    tree.resize(1);
  }
  void push(T x) {
    tree.push_back(x);
    sift_up(tree.size() - 1);
    heap_size++;
  }
  void pop() {
    swap(tree[1], tree[tree.size() - 1]);
    tree.erase(tree.end() - 1);
    if (tree.size())
      sift_down(1);
    heap_size--;
  }
  void clear() {
    while (heap_size)
      pop();
  }
  T top() { return tree[1]; }
  int size() { return heap_size; }
  const bool empty() { return heap_size == 0; }
};
