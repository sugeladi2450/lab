#ifndef STACK_IMPL_H
#define STACK_IMPL_H
#include <cassert>
#include <utility>

template <typename T>
void Stack<T>::push(T t) {
    auto new_node = MakeUnique<Node<T>>(t);
    new_node->next = std::move(head);
    head = std::move(new_node);
    sz++;
}

template <typename T>
void Stack<T>::pop() {
    assert(!empty() && "pop() called on empty stack");
    UniquePtr<Node<T>> temp = std::move(head);
    head = std::move(temp->next);
    sz--;
}

template <typename T>
T &Stack<T>::top() {
    assert(!empty() && "top() called on empty stack");
    return head->val;
}

template <typename T>
bool Stack<T>::empty() const {
    return sz == 0;
}

template <typename T>
size_t Stack<T>::size() const {
    return sz;
}

#endif  // STACK_IMPL_H