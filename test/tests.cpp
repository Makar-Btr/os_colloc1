#include <gtest/gtest.h>
#include "tasks.hpp"
#include <string>
#include <memory>

// ========= Тесты для Задачи 1: Факториалы =========

TEST(FactorialsTest, PositiveInput) {
    std::vector<unsigned long long> expected = {1, 2, 6, 24, 120};
    EXPECT_EQ(calculate_factorials(5), expected);
}

TEST(FactorialsTest, SingleInput) {
    std::vector<unsigned long long> expected = {1};
    EXPECT_EQ(calculate_factorials(1), expected);
}

TEST(FactorialsTest, InvalidInputZero) {
    EXPECT_THROW(calculate_factorials(0), std::invalid_argument);
}

TEST(FactorialsTest, InvalidInputNegative) {
    EXPECT_THROW(calculate_factorials(-5), std::invalid_argument);
}

TEST(FactorialsTest, OverflowException) {
    EXPECT_NO_THROW(calculate_factorials(20));
    
    EXPECT_THROW(calculate_factorials(21), std::overflow_error);
}

// ========= Тесты для Задачи 2: Удаление дубликатов =========

TEST(RemoveDuplicatesTest, EmptyVector) {
    std::vector<int> input = {};
    std::vector<int> expected = {};
    EXPECT_EQ(remove_duplicates(input), expected);
}

TEST(RemoveDuplicatesTest, NoDuplicates) {
    std::vector<int> input = {1, 2, 3, 4, 5};
    std::vector<int> expected = {1, 2, 3, 4, 5};
    EXPECT_EQ(remove_duplicates(input), expected);
}

TEST(RemoveDuplicatesTest, AllDuplicates) {
    std::vector<int> input = {5, 5, 5, 5};
    std::vector<int> expected = {5};
    EXPECT_EQ(remove_duplicates(input), expected);
}

TEST(RemoveDuplicatesTest, MixedDuplicates) {
    std::vector<int> input = {1, 2, 1, 4, 3, 2, 4, 1, 5};
    std::vector<int> expected = {1, 2, 4, 3, 5};
    EXPECT_EQ(remove_duplicates(input), expected);
}

TEST(RemoveDuplicatesTest, StringType) {
    std::vector<std::string> input = {"apple", "banana", "apple", "orange", "banana"};
    std::vector<std::string> expected = {"apple", "banana", "orange"};
    EXPECT_EQ(remove_duplicates(input), expected);
}

// ========= Тесты для Задачи 3: Реверс связного списка =========

template <typename T>
std::unique_ptr<Node<T>> create_list(const std::vector<T>& values) {
    if (values.empty()) {
        return nullptr;
    }

    Node<T>* head = new Node<T>(values[0]);
    Node<T>* current = head;
    for (size_t i = 1; i < values.size(); ++i) {
        current->next = new Node<T>(values[i]);
        current = current->next;
    }
    return std::unique_ptr<Node<T>>(head);
}

template <typename T>
std::vector<T> list_to_vector(const Node<T>* head) {
    std::vector<T> result;
    const Node<T>* current = head;
    while (current != nullptr) {
        result.push_back(current->data);
        current = current->next;
    }
    return result;
}

// --------------------------------------------------

TEST(ReverseListTest, NullList) {
    std::unique_ptr<Node<int>> head = nullptr;
    
    Node<int>* new_head_raw = 
        reverse_list_recursive(head.get());

    std::unique_ptr<Node<int>> reversed_list(new_head_raw);

    EXPECT_EQ(reversed_list.get(), nullptr);
}

TEST(ReverseListTest, OneElementList) {
    auto head_ptr = create_list<int>({10});
    
    Node<int>* raw_head = head_ptr.release(); 
    
    Node<int>* new_head_raw = 
        reverse_list_recursive(raw_head);
    
    std::unique_ptr<Node<int>> reversed_list(new_head_raw);
    
    std::vector<int> expected = {10};
    EXPECT_EQ(list_to_vector(reversed_list.get()), expected);
}

TEST(ReverseListTest, MultipleElementsList) {
    auto head_ptr = create_list<int>({1, 2, 3, 4, 5});
    
    Node<int>* raw_head = head_ptr.release(); 
    
    Node<int>* new_head_raw = 
        reverse_list_recursive(raw_head);
    
    std::unique_ptr<Node<int>> reversed_list_manager(new_head_raw);
    
    std::vector<int> expected = {5, 4, 3, 2, 1};
    EXPECT_EQ(list_to_vector(reversed_list_manager.get()), expected);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}