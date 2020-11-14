#include "JSON.h"

JSON::List::List(const List& other) : front(nullptr), back(nullptr), nodes(0) {
  *this = other;
}

JSON::List& JSON::List::operator=(const List& other) {
  for (const auto& o : other) {
    pushBack(o);
  }
  return *this;
}

void JSON::List::pushBack(const std::variant<std::string, float, int>& data) {
  if (front == nullptr) {
    front = new Node(data);
    back = front;
  }
  else {
    back->next = new Node(data);
    back->next->prev = back;
    back = back->next;
  }
  ++nodes;
}

bool JSON::List::popBack() {
  if (front != nullptr) {
    if (back == front) {
      delete front;
      front = nullptr;
    }
    else {
      back = back->prev;
      delete back->next;
      back->next = nullptr;
    }
    --nodes;
    return true;
  }
  return false;
}

void JSON::List::clear() {
  while(popBack()) {}
}

bool JSON::List::Iterator::operator!=(const Iterator& other) const {
  return act != other.act;
}

const JSON::List::Iterator& JSON::List::Iterator::operator++() {
  act = act->next;
  return *this;
}

const std::variant<std::string, float, int>& JSON::List::Iterator::operator*() const {
  return act->data;
}

JSON::List::Iterator JSON::List::begin() const {
  if (size() > 0) { return Iterator(front); }
  else { throw ParseException("List is empty!"); }
}

JSON::List::Iterator JSON::List::end() const {
  if (size() > 0) { return Iterator(back->next); }
  else { throw ParseException("List is empty!"); }
}
