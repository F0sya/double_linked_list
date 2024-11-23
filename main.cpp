#include <iostream>
using namespace std;


template <typename T>
class Element {
public:
    T value;
    Element* next;
    Element* prev;

    Element(T value) : value(value), next(nullptr), prev(nullptr) {}
};

template <typename T>
class DoublyLinkedList {
private:
    Element<T>* head;
    Element<T>* tail;
    int size;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~DoublyLinkedList() {
        while (head != nullptr) {
            Element<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void push_back(T val) {
        Element<T>* newNode = new Element<T>(val);
        if (tail) {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        else {
            head = tail = newNode;
        }
        size++;
    }

    void pop_back() {
        if (!tail) return;
        Element<T>* temp = tail;
        tail = tail->prev;
        if (tail) {
            tail->next = nullptr;
        }
        else {
            head = nullptr;
        }
        delete temp;
        size--;
    }

    int getSize() const {
        return size;
    }

    Element<T>* getHead() const {
        return head;
    }

    Element<T>* getTail() const {
        return tail;
    }

    bool isEmpty() const {
        return size == 0;
    }


    T getAt(int index) const {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of range");
        }
        Element<T>* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->value;
    }

    void setAt(int index, T value) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of range");
        }
        Element<T>* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        current->value = value;
    }
};


template <typename T>
class Array {
private:
    DoublyLinkedList<T> list;
    int size;
    int capacity;
    int grow;

public:
    Array(int initialSize = 0, int growSize = 1)
        : size(0), capacity(initialSize), grow(growSize) {
        setSize(initialSize);
    }


    void setSize(int newSize, int growSize = 1) {
        if (newSize > capacity) {
            capacity = newSize + growSize;
        }
        if (newSize < size) {
            for (int i = size - 1; i >= newSize; --i) {
                list.pop_back();
            }
        }
        size = newSize;
    }

    int getSize() const {
        return size;
    }

    bool isEmpty() const {
        return list.isEmpty();
    }

    void freeExtra() {
        setSize(size);
    }

    void removeAll() {
        list.clear();
        size = 0;
    }

    T getAt(int index) const {
        return list.getAt(index);
    }

    void setAt(int index, T value) {
        list.setAt(index, value);
    }

    T& operator[](int index) {
        return list.getAt(index);
    }

    void add(T value) {
        if (size == capacity) {
            setSize(capacity + grow);
        }
        list.push_back(value);
    }

    Array<T> operator+(const Array<T>& other) {
        Array<T> result(size + other.size);
        for (int i = 0; i < size; ++i) {
            result.add(getAt(i));
        }
        for (int i = 0; i < other.size; ++i) {
            result.add(other.getAt(i));
        }
        return result;
    }

    Array<T>& operator=(const Array<T>& other) {
        if (this != &other) {
            removeAll();
            for (int i = 0; i < other.size; ++i) {
                add(other.getAt(i));
            }
        }
        return *this;
    }

    T* getData() {
        T* data = new T[size];
        for (int i = 0; i < size; ++i) {
            data[i] = getAt(i);
        }
        return data;
    }

    void insertAt(int index, T value) {
        if (index < 0 || index > size) {
            throw out_of_range("Index out of range");
        }
        if (size == capacity) {
            setSize(capacity + grow);
        }
        for (int i = size; i > index; --i) {
            setAt(i, getAt(i - 1));
        }
        setAt(index, value);
        size++;
    }

    void removeAt(int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of range");
        }
        for (int i = index; i < size - 1; ++i) {
            setAt(i, getAt(i + 1));
        }
        list.pop_back();
        size--;
    }

    int getUpperBound() const {
        return size - 1;
    }

};

int main() {
    return 0;
}