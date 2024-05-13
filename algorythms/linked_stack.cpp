class linked_stack {
  struct node {
    int value;
    node *prev;
    node() { prev = nullptr; }
    node(int x, node *prev_) {
      value = x;
      prev = prev_;
    }
  };
  int len;
  node *head;

public:
  linked_stack() { len = 0; }
  void push(int value) {
    len++;
    head = new node(value, head);
  }
  void pop() {
    len--;
    node *t = head;
    head = head->prev;
    delete t;
  }
  void clear() {
    while (len > 0) {
      pop();
    }
  }
  ~linked_stack() { clear(); }
  int top() { return head->value; }
  int size() { return len; }
};
