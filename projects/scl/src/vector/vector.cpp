#include <iostream>
#include <stdexcept>

#include "vector.hpp"

namespace EAbrakhin {
    template<typename T>
    Vector<T>::Vector() noexcept {
        arr = new T[capacity];
    }

    template<typename T>
    Vector<T>::~Vector() noexcept {
        delete[] arr;
    }

    template<typename T>
    void Vector<T>::push_back(const T& value) noexcept {
        if (vec_size == capacity) {
            capacity *= 2;
            T* new_arr = new T[capacity];
            for (size_t i = 0; i < vec_size; ++i) {
                new_arr[i] = arr[i];
            }
            delete[] arr;
            arr = new_arr;
        }
        arr[vec_size++] = value;
    }

    template<typename T>
    bool Vector<T>::has_item(const T& value) const noexcept {
        for (size_t i = 0; i < vec_size; ++i) {
            if (arr[i] == value) {
                return true;
            }
        }
        return false;
    }

    template<typename T>
    bool Vector<T>::insert(const int position, const T& value) {
        if (position < 0 || position > vec_size) {
            throw std::out_of_range("Invalid position for insertion");
        }
        if (vec_size == capacity) {
            capacity *= 2;
            T* new_arr = new T[capacity];
            for (size_t i = 0; i < position; ++i) {
                new_arr[i] = arr[i];
            }
            new_arr[position] = value;
            for (size_t i = position; i < vec_size; ++i) {
                new_arr[i + 1] = arr[i];
            }
            delete[] arr;
            arr = new_arr;
        } else {
            for (size_t i = vec_size; i > position; --i) {
                arr[i] = arr[i - 1];
            }
            arr[position] = value;
        }
        ++vec_size;
        return true;
    }

    template<typename T>
    void Vector<T>::print() const noexcept {
        for (size_t i = 0; i < vec_size; ++i) {
            std::cout << ' ' << arr[i];
        }
        std::cout << std::endl;
    }

    template<typename T>
    bool Vector<T>::remove_first(const T& value) noexcept {
        for (size_t i = 0; i < vec_size; ++i) {
            if (arr[i] == value) {
                for (size_t j = i; j < vec_size - 1; ++j) {
                    arr[j] = arr[j + 1];
                }
                --vec_size;
                return true;
            }
        }
        return false;
    }

    template<typename T>
    int Vector<T>::size() const noexcept {
        return vec_size;
    }
}
