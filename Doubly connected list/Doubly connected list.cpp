#include <iostream>﻿


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
        tail = nullptr;
        delete tail;
        tail = tmp;
        size--;
    }

    void pop_front() {
        if (head == nullptr) return;
        Node* tmp = head->next;                         
        if (tmp != nullptr) tmp->prev = nullptr;        
        else head = nullptr; 
        head = nullptr;
        delete head;
        head = tmp;
        size--;
    }

    void erase(int posithion) {
        if (posithion >= size || posithion < 0) {
            std::cerr << "There is no such position" << std::endl;
            return;
        }

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
                if(it->next != nullptr) it->next->prev = tmp;;
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
                tmp->prev = it->prev;
                it->prev->next = tmp;
                it = nullptr;
                delete it;
            }
        }
    }

    void insert(int value, int posithion) {
        if (posithion >= size || posithion < 0) return;

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
                tmp->next = it;
                it->prev = tmp;
                head = tmp;
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
                tmp->prev = it;
                it->next = tmp;
                tail = tmp;
            }
            else {
                while (count != posithion) {
                    if (count == posithion + 1) {
                        it = it->prev;
                        count--;
                    }
                }
                tmp->next = it;
                tmp->prev = it->prev;
                it->prev = tmp;
                tmp->prev->next = tmp;
            }
        }
        size++;
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

    void sort() {
        for (int i = 0; i < size; i++) {
            Node* it = at(i);
            for (int j = i; j < size; j++) {
                Node* jt = at(j);
                if (it->val < jt->val) { break; }

                if (it->val > jt->val) {
                    if (j == size - 1) {
                        it->next = jt->next;
                        jt->prev = it->prev;
                        it->prev->next = jt;
                        jt->next = it;
                        it->prev = jt;
                    }
                    else {
                        it->next = jt->next;
                        jt->next->prev = it;
                        jt->prev = it->prev;
                        it->prev->next = jt;
                        jt->next = it;
                        it->prev = jt;
                    }
                }
          }
        }
    }
};

std::ostream& operator<< (std::ostream& out, const Forward_List& fl) {
    Node* it = fl.head;
    for (int i = 0; i < fl.size; i++) {
        std::cout << it->val << " ";
        it = it->next;
    }
    std::cout << std::endl;
    return std::cout;
}




int main()
{

    Forward_List fl{};
    fl.push_back(0);
    fl.push_back(8);
    fl.push_back(1);
    fl.push_back(3);
    fl.push_back(9);
    fl.push_back(5);
    std::cout << fl;
    fl.sort();
    std::cout << fl;
    
    return 0;
}
