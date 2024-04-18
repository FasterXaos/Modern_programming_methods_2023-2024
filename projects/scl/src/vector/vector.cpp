#include <iostream>
#include <stdexcept>

#include "vector.hpp"

template<typename T>
EAbrakhin::Vector<T>::Vector() noexcept {
    arr = new T[capacity];
}

template<typename T>
EAbrakhin::Vector<T>::~Vector() noexcept {
    delete[] arr;
}

template<typename T>
void EAbrakhin::Vector<T>::push_back(const T& value) noexcept {
    if (size == capacity) {
        capacity *= 2;
        T* new_arr = new T[capacity];
        for (size_t i = 0; i < size; ++i) {
            new_arr[i] = arr[i];
        }
        delete[] arr;
        arr = new_arr;
    }
    arr[size++] = value;
}

template<typename T>
bool EAbrakhin::Vector<T>::has_item(const T& value) const noexcept {
    for (size_t i = 0; i < size; ++i) {
        if (arr[i] == value) {
            return true;
        }
    }
    return false;
}

template<typename T>
bool EAbrakhin::Vector<T>::insert(const int position, const T& value) noexcept(false) {
    if (position < 0 || position > size) {
        throw std::out_of_range("Invalid position for insertion");
    }
    if (size == capacity) {
        capacity *= 2;
        T* new_arr = new T[capacity];
        for (size_t i = 0; i < position; ++i) {
            new_arr[i] = arr[i];
        }
        new_arr[position] = value;
        for (size_t i = position; i < size; ++i) {
            new_arr[i + 1] = arr[i];
        }
        delete[] arr;
        arr = new_arr;
    } else {
        for (size_t i = size; i > position; --i) {
            arr[i] = arr[i - 1];
        }
        arr[position] = value;
    }
    ++size;
    return true;
}

template<typename T>
void EAbrakhin::Vector<T>::print() const noexcept {
    for (size_t i = 0; i < size; ++i) {
        std::cout  << ' ' << arr[i];
    }
    std::cout << std::endl;
}

template<typename T>
bool EAbrakhin::Vector<T>::remove_first(const T& value) noexcept {
    for (size_t i = 0; i < size; ++i) {
        if (arr[i] == value) {
            for (size_t j = i; j < size - 1; ++j) {
                arr[j] = arr[j + 1];
            }
            --size;
            return true;
        }
    }
    return false;
}

template<typename T>
int EAbrakhin::Vector<T>::get_size() const noexcept {
    return size;
}
