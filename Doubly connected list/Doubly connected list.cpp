﻿/*
 1) push_back 2) pop_back 3) push_front 4) pop_front 5) erase 6) insert 7) at
 8) operator[] 9) operator<< 10) size 11) shift_right 12) shift_left 13*) sort - допустимо N^2 14**) quick_sort - NlogN
 */

#include <iostream>
#include <optional>
#include <cassert>


    struct Node {
    int val;
    Node* next;
    Node* prev;


    Node()
        : val(0), next(nullptr), prev(nullptr) {};

    Node(int val) = delete;
};

struct Forward_List {
public:
    Node* head;
    Node* tail;
    unsigned int size;
public:
    Forward_List() :
        head(nullptr), tail(nullptr), size{ 0 } {}

    /*std::optional<int> at_value(int idx) const {
        if (head == nullptr || idx < 0 || idx >= size) return std::optional<int>{};
        int i = 0;
        Node* tmp = head;
        while (i++ < idx) {
            tmp = tmp->next;
        }
        return tmp->val;
    }*/

    void push_back(int value) {
        Node* tmp = new Node{};
        tmp->val = value;
        tmp->next = nullptr;
        tmp->prev = nullptr;

        if (head == nullptr) {
            head = tmp;
            tail = tmp;
        }
        else {
            Node* it = tail;
            tmp->prev = it;
            it->next = tmp;
            tail = tmp;
        }
        size++;
    }

    void push_front(int value) {
        Node* tmp = new Node{};
        tmp->val = value;
        tmp->next = nullptr;
        tmp->prev = nullptr;

        if (head == nullptr) {
            head = tmp;
            tail = tmp;
        }

        else {
            head->prev = tmp;
            tmp->next = head;
            head = tmp;
        }
        size++;
    }

    void pop_back() {
        if (tail == nullptr) return;
        Node* tmp = tail->prev;                         
        if (tmp != nullptr) tmp->next = nullptr;        
        else head = nullptr;                            
        delete tail;
        tail = tmp;
        size--;
    }

    void pop_front() {
        if (head == nullptr) return;
        Node* tmp = head->next;                         
        if (tmp != nullptr) tmp->prev = nullptr;        
        else head = nullptr;  
        delete head;
        head = tmp;
        size--;
    }

    void erase(int posithion) {
        if (posithion >= size || posithion < 0) std::cerr << "There is no such position" << std::endl;

        Node* it{};
        Node* tmp{};
        int count;

        if (posithion <= size / 2) {
            it = head;
            count = 0;
            if (posithion == 0) {
                it = it->next;
                it->prev = nullptr;
                delete head;
                head = it;
            }
            else {
                while (count != posithion) {
                    if (count == posithion - 1) tmp = it;
                    it = it->next;
                    count++;
                }
                tmp->next = it->next;
                tmp = tmp->next;
                tmp->prev = it->prev;
                it = nullptr;
                delete it;
            }
        }

        if (posithion > size / 2) {
            it = tail;
            count = size - 1;
            if (posithion == size - 1) {
                it = it->prev;
                tail = nullptr;
                delete tail;
                tail = it;
            }
            else {
                while (count != posithion) {
                    if (count == posithion + 1) tmp = it;
                    it = it->prev;
                    count--;
                }
                tmp->prev = tmp->prev->prev;
                tmp = tmp->prev;
                tmp->next = tmp->next->next;
                it = nullptr;
                delete it;
            }
        }
    }

    void insert(int value, int posithion) {
        if (posithion >= size || posithion < 0) {
            return;
        }

        Node* tmp = new Node{};
        tmp->val = value;
        tmp->next = nullptr;
        tmp->prev = nullptr;


        Node* it{};
        int count;

        if (posithion <= size / 2) {
            it = head;
            count = 0;
            if (posithion == 0) {
                it = it->next;
                head = tmp;
                tmp = it;
            }
            else {
                while (count != posithion) {
                    it = it->next;
                    count++;
                }
                tmp->next = it;
                tmp->prev = it->prev;
                it->prev = tmp;
                tmp->prev->next = tmp;
            }
        }

        if (posithion > size / 2) {
            it = tail;
            count = size - 1;
            if (posithion == size - 1) {
                it = it->prev;
                tmp->prev = it;
                tail = tmp;
            }
            else {
                while (count != posithion) {
                    if (count == posithion + 1) tmp = it;
                    it = it->prev;
                    count--;
                }
                tmp->next = it;
                tmp->prev = it->prev;
                it->prev = tmp;
                tmp->prev->next = tmp;
            }
        }
    }

    Node* at(int index) const {
        if (head == nullptr || index < 0 || index >= size) return nullptr;
        int i = 0;
        Node* tmp = head;
        while (i++ < index) {
            tmp = tmp->next;
        }
        return tmp;
    }

    // operator[]
    Node* operator[] (int index) {
        return at(index);
    }

    void shift_right(int num_pos) {
        if (head == nullptr) return;
        tail->next = head;
        head->prev = tail;
        int i{ 0 };
        while (i++ < num_pos) {
            head = head->next;
            tail = tail->next;
        }
    }
    void shift_left(int num_pos) {
        if (head == nullptr) return;
        tail->next = head;
        head->prev = tail;
        int i{ 0 };
        while (i++ < num_pos) {
            head = head->prev;
            tail = tail->prev;
        }
    }
};

std::ostream& operator<< (std::ostream& out, const Forward_List& fl) {
    Node* it = fl.head;
    while (it->next != nullptr) {
        std::cout << it->val << " ";
        it = it->next;
    }
    std::cout << std::endl;
}


int main()
{

    Forward_List fl{};
    assert(fl.head == nullptr);
    fl.push_back(1);
    assert(fl[0]->val == 1);
    assert(fl.at(0)->val == 1);
    fl.push_back(2);
    fl.push_back(3);
    //    fl.push_back(4);
    //    fl.push_back(5);
    //    assert(fl.size == 5);
    //    fl.push_front(0);
    //    assert(fl[0]->val == 0);
    fl.pop_back();
    //    assert(fl[4]->val == 4);
    //    fl.pop_front();
    //    assert(fl[0]->val == 1);
    //    fl.erase(1);
    //    fl.insert(100, 1);
    //    assert(fl[1]->val == 100);

    //    std::cout << fl;

    //    std::cout << fl.at(0)->val << std::endl;
    //    fl.shift_right(2);
    //    std::cout << fl.at(0)->val << std::endl;
    //    fl.shift_left(2);
    //    std::cout << fl.at(0)->val << std::endl;
    return 0;
}