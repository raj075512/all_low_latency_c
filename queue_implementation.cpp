#include <iostream>
#include <stdexcept>

template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
    };

    Node* front;
    Node* rear;

public:
    // Constructor to initialize an empty queue
    Queue() : front(nullptr), rear(nullptr) {}

    // Destructor to clean up the queue
    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    // Enqueues an element to the rear of the queue
    void enqueue(const T& value) {
        Node* newNode = new Node{value, nullptr};
        if (rear != nullptr) {
            rear->next = newNode;
        }
        rear = newNode;
        if (front == nullptr) {
            front = newNode;
        }
    }

    // Dequeues an element from the front of the queue
    T dequeue() {
        if (isEmpty()) {
            throw std::out_of_range("Queue is empty");
        }

        Node* temp = front;
        T value = front->data;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr; // If the queue is empty now, set rear to nullptr
        }
        delete temp;
        return value;
    }

    // Returns the front element without dequeuing it
    T peek() const {
        if (isEmpty()) {
            throw std::out_of_range("Queue is empty");
        }

        return front->data;
    }

    // Checks if the queue is empty
    bool isEmpty() const {
        return front == nullptr;
    }

    // Returns the size of the queue
    int size() const {
        int count = 0;
        Node* current = front;
        while (current != nullptr) {
            ++count;
            current = current->next;
        }
        return count;
    }
};

int main() {
    Queue<int> queue;

    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);

    std::cout << "Front element: " << queue.peek() << std::endl;

    std::cout << "Dequeueing elements:\n";
    while (!queue.isEmpty()) {
        std::cout << queue.dequeue() << std::endl;
    }

    try {
        queue.dequeue();  // This should throw an exception because the queue is empty
    } catch (const std::out_of_range& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
