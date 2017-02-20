/* Catalina Vajiac
 * CSE 20311 Final Project
 * list.h
 * headers for linked list
 */

#ifndef LIST_H
#define LIST_H

typedef std::pair<int, int> pair_int_t;

class Node {
  public:
    Node(pair_int_t);
    ~Node();
    void add_next(Node *);
    pair_int_t value;
    Node *next;
    Node *previous;
};

class LinkedList {
  public:
    LinkedList();
    ~LinkedList();
    pair_int_t first();
    pair_int_t last();
    void push_back(pair_int_t);
    void push_front(pair_int_t);
    void pop_back();
    void pop_front();
    void print();
    bool contains(Node);
    int size();
    int count_occurances(Node);
    Node* begin();
    Node* end();
    
  private:
    Node *head;
    Node *tail;
    int list_size;
};

#endif
