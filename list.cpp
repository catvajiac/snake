/* Catalina Vajiac
 * CSE 20311 Final Project
 * list.cpp
 * implementation of linked list
 */

#include <iostream>
#include <utility>
#include "./list.h"

typedef std::pair<int, int> pair_int_t;

Node::Node(pair_int_t value) {
  this -> value = value;
  this -> next = 0;
  this -> previous = 0;
}

Node::~Node() {
}

void Node::add_next(Node *n) {
  this -> next = n;
  n -> previous = this;
}

LinkedList::LinkedList() {
  this -> head = 0;
  this -> tail = 0;
}

LinkedList::~LinkedList() {

}

pair_int_t LinkedList::first() {
  return this -> head -> value;
}

pair_int_t LinkedList::last() {
  return this -> tail -> value;
}

int LinkedList::size() {
  return list_size;
}

void LinkedList::push_back(pair_int_t value) {
/* add node to back of linked list
 * take care of head & tail pointers
 */
  Node *new_node = new Node(value);
  if (this -> tail) {
    (this -> tail) -> add_next(new_node);
    this -> tail = new_node;
  } else {
    this -> head = new_node;
    this -> tail = new_node;
  }
  list_size++;
}

void LinkedList::push_front(pair_int_t value) {
/* add node to front of linked list
 * take care of head & tail pointers
 */
  Node *new_node = new Node(value);
  if (this -> head) {
    new_node -> add_next(this -> head);
    this -> head = new_node;
  } else {
    this -> head = new_node;
    this -> tail = new_node;
  }
  list_size++;
}

void LinkedList::pop_back() {
/* delete last node from list
 * take care of head & tail pointers
 */
  if (this -> tail) {
    this -> tail = (this -> tail) -> previous;
    if (this -> tail) {
      this -> tail -> next = 0;
    } else {
      this -> head = 0;
    }
  }
  if (list_size > 0) {
    list_size--;
  }
}

void LinkedList::pop_front() {
/* delete first node from list
 * take care of head & tail pointers
 */
  if (this -> head) {
    this -> head = (this -> head) -> next;
    if (this -> head) {
      (this -> head) -> previous = 0;
    } else {
      this -> tail = 0;
    }
  }
  if (list_size > 0) {
    list_size--;
  }
}

void LinkedList::print() {
/* print values of nodes in list with the format
 * (value.first, value.second)
 */
  Node *current_node = this -> head;
  while (current_node != 0) {
    std::cout << current_node << ": ";
    std::cout << "(" << (current_node -> value).first << ", ";
    std::cout << (current_node -> value).second << ")" << std::endl;
    current_node = current_node -> next;
  }
}

bool LinkedList::contains(Node n) {
/* check if list contains node n
 * return true if it contains true, false otherwise
 */
  Node *current_node = this -> head;
  while (current_node != 0) {
    if (n.value == current_node -> value) {
      return true;
    }
    current_node = current_node -> next;
  }
  return false;
}

int LinkedList::count_occurances(Node n) {
/* count number of times node n appears in list
 */
  Node *current_node = this -> head;
  int count = 0;
  while (current_node != 0) {
    if (n.value == current_node -> value) {
      count++;
    }
    current_node = current_node -> next;
  }
  return count;
}

Node* LinkedList::begin() {
  return this -> head;
}

Node* LinkedList::end() {
  return 0;
}
