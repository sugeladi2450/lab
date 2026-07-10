#ifndef QUEUE_IMPL_H
#define QUEUE_IMPL_H

#include <cassert>
#include <utility>

template <typename T>
void Queue<T>::push(T t) {
    auto new_node = MakeUnique<Node<T>>(t);
    if (empty()) {
        head = std::move(new_node);
        tail = head.get();
    } else {
        tail->next = std::move(new_node);
        tail = tail->next.get();
    }
    sz++;
}

template <typename T>
void Queue<T>::pop() {
    assert(!empty() && "pop() called on empty queue");
    UniquePtr<Node<T>> temp = std::move(head);
    head = std::move(temp->next);
    sz--;
    if (empty()) {
        tail = nullptr;
    }
}

template <typename T>
T &Queue<T>::front() {
    assert(!empty() && "front() called on empty queue");
    return head->val;
}

template <typename T>
bool Queue<T>::empty() const {
    return sz == 0;
}

template <typename T>
size_t Queue<T>::size() const {
    return sz;
}
#endif  // QUEUE_IMPL_H