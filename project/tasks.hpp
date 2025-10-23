#pragma once

#include <vector>
#include <stdexcept>
#include <limits>
#include <unordered_set>
#include <memory>
#include <functional>

std::vector<unsigned long long> calculate_factorials(int n) {
    if (n < 0) {
        throw std::invalid_argument("Input 'n' must be a non-negative integer.");
    }

    std::vector<unsigned long long> factorials(n + 1, 0);
    factorials[0] = 1;
    factorials[1] = 1;

    for (int i = 2; i <= n; ++i) {
        if (factorials[i - 1] > std::numeric_limits<unsigned long long>::max() / i) {
            throw std::overflow_error("Factorial calculation overflowed at i = " + std::to_string(i));
        }
        factorials[i] = factorials[i - 1] * i;
    }

    return factorials;
}

template <typename T>
std::vector<T> remove_duplicates(const std::vector<T>& input) {
    std::vector<T> result;
    std::unordered_set<T> seen;

    for (const T& item : input) {
        if (seen.insert(item).second) {
            result.push_back(item);
        }
    }

    return result;
}


template <typename T>
struct Node {
    T data;
    Node* next;

    Node(T val) : data(val), next(nullptr) {}
};

template <typename T>
Node<T>* reverse_list_recursive(Node<T>* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    Node<T>* new_head = reverse_list_recursive(head->next);

    head->next->next = head;

    head->next = nullptr;

    return new_head;
}