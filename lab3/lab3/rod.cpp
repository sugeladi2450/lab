#include "rod.h"
#include <string>


Rod::Rod(const int capacity, const int id) : capacity(capacity), id(id), stack() {
}

bool Rod::push(const Disk d) {
    if (stack.empty() || d.val < stack.top().val) {
        stack.push(d);
        return true;
    }
    return false;
}

const Disk &Rod::top() {
    return stack.top();
}

void Rod::pop() {
    stack.pop();
}

size_t Rod::size() const {
    return stack.size();
}

bool Rod::empty() const {
    return stack.empty();
}

bool Rod::full() const {
    return stack.size() == static_cast<size_t>(capacity);
}

void Rod::draw(Canvas &canvas) {
    int rod_center_x = 5 + id * 15;
    for (int i = 0; i < Canvas::HEIGHT; ++i) {
        if (rod_center_x >= 0 && rod_center_x < Canvas::WIDTH) {
            canvas.buffer[i][rod_center_x] = '|';
        }
    }

    Stack<const Disk> temp_stack;
    while (!stack.empty()) {
        temp_stack.push(stack.top());
        stack.pop();
    }

    int level = 0;
    while (!temp_stack.empty()) {
        Disk current_disk = temp_stack.top();
        current_disk.draw(canvas, level, id);
        stack.push(current_disk);
        temp_stack.pop();
        level++;
    }
}

std::string Rod::toString() {
    std::string s;
    Stack<const Disk> temp_stack;
    while (!stack.empty()) {
        temp_stack.push(stack.top());
        stack.pop();
    }

    while (!temp_stack.empty()) {
        s += std::to_string(temp_stack.top().val) + "_";
        stack.push(temp_stack.top());
        temp_stack.pop();
    }
    s += "|";
    return s;
}