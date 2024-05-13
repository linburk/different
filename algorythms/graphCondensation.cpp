#include <set>
#include <vector>

struct _condensate {
  _condensate() {
    used = new std::vector<bool>;
    order = new std::vector<int>;
    member = new std::vector<int>;
    component = new std::vector<int>;
    condensatedGraph = new std::vector<std::set<int>>;
  }
  ~_condensate() {
    delete order;
    delete member;
    delete component;
    delete condensatedGraph;
  }
  std::vector<std::set<int>>
  operator()(std::vector<std::vector<int>> &graph,
             std::vector<std::vector<int>> &turnedGraph) {
    topSortGraph(graph);
    getMember(turnedGraph);
    getCondensatedGraph(graph);
    return *condensatedGraph;
  }

private:
  std::vector<bool> *used;
  std::vector<int> *order, *member, *component;
  std::vector<std::set<int>> *condensatedGraph;
  int componentCount;

  void topSortGraph(std::vector<std::vector<int>> &graph) {
    used->resize(graph.size(), 0);
    for (int v = 0; v < graph.size(); v++) {
      if (!used->at(v))
        topSort(v, graph);
    }
  }
  void topSort(int v, std::vector<std::vector<int>> &graph) {
    if (used->at(v))
      return;
    used->at(v) = 1;
    for (auto to : graph[v]) {
      topSort(to, graph);
    }
    order->push_back(v);
  }
  void getCondensatedGraph(std::vector<std::vector<int>> &graph) {
    condensatedGraph->resize(componentCount);
    for (int v = 0; v < member->size(); v++) {
      for (auto to : graph[v]) {
        if (member->at(v) != member->at(to))
          condensatedGraph->at(member->at(v)).insert(member->at(to));
      }
    }
  }

  void getMember(std::vector<std::vector<int>> &turnedGraph) {
    componentCount = 0;
    used->assign(order->size(), 0);
    member->resize(order->size());
    for (int v = order->size() - 1; v >= 0; v--) {
      if (!used->at(order->at(v))) {
        getComponent(order->at(v), turnedGraph);
        for (auto i : *component)
          member->at(i) = componentCount;
        componentCount++;
        component->clear();
      }
    }
  }
  void getComponent(int v, std::vector<std::vector<int>> &turnedGraph) {
    if (used->at(v))
      return;
    used->at(v) = 1;
    component->push_back(v);
    for (auto to : turnedGraph[v]) {
      getComponent(to, turnedGraph);
    }
  }
};
