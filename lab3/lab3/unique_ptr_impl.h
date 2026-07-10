#ifndef UNIQUE_PTR_IMPL_H
#define UNIQUE_PTR_IMPL_H

template <typename T>
UniquePtr<T>::UniquePtr(UniquePtr &&other) noexcept : pointer(other.pointer) {
    other.pointer = nullptr;
}

template <typename T>
UniquePtr<T>::~UniquePtr() {
    if (pointer) {
        delete pointer;
        pointer = nullptr;
    }
}

template <typename T>
UniquePtr<T> &UniquePtr<T>::operator=(UniquePtr &&other) noexcept {
    if (this != &other) {
        if (pointer) {
            delete pointer;
        }
        pointer = other.pointer;
        other.pointer = nullptr;
    }
    return *this;
}

template <typename T>
UniquePtr<T> &UniquePtr<T>::operator=(std::nullptr_t) noexcept {
    if (pointer) {
        delete pointer;
    }
    pointer = nullptr;
    return *this;
}

template <typename T>
void UniquePtr<T>::reset(T *ptr) noexcept {
    if (pointer != ptr) {
        if (pointer) {
            delete pointer;
        }
        pointer = ptr;
    }
}

template <typename T>
T *UniquePtr<T>::release() noexcept {
    T *temp = pointer;
    pointer = nullptr;
    return temp;
}

#endif  // UNIQUE_PTR_IMPL_H