class linked_queue {
  struct node {
    int value;
    node *next;
    node *last;
    node() {
      next = nullptr;
      last = nullptr;
    }
    node(int x, node *next_) {
      last = nullptr;
      next = next_;
      value = x;
    }
  };
  int len;
  node *head;
  node *last;

public:
  linked_queue() {
    head = new node();
    last = head;
    len = 0;
  }

  void push(int value) {
    len++;
    last->last = new node(value, last);
    last = last->last;
    if (len == 1) {
      head = last;
    }
  }
  void pop() {
    len--;
    head = head->last;
    if (len == 0)
      delete head;
    else
      delete head->next;
  }
  void clear() {
    while (len > 0) {
      pop();
    }
  }
  int front() { return head->value; }
  int size() { return len; }
  ~linked_queue() { clear(); }
};
