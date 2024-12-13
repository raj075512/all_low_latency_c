#include <iostream>
#include <stdexcept>

template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
    };

    Node* top;

public:
    // Constructor to initialize an empty stack
    Stack() : top(nullptr) {}

    // Destructor to clean up the stack
    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    // Pushes an element onto the stack
    void push(const T& value) {
        Node* newNode = new Node{value, top};
        top = newNode;
    }

    // Pops an element from the stack
    T pop() {
        if (isEmpty()) {
            throw std::out_of_range("Stack is empty");
        }

        Node* temp = top;
        T value = top->data;
        top = top->next;
        delete temp;
        return value;
    }

    // Returns the top element without removing it
    T peek() const {
        if (isEmpty()) {
            throw std::out_of_range("Stack is empty");
        }

        return top->data;
    }

    // Checks if the stack is empty
    bool isEmpty() const {
        return top == nullptr;
    }

    // Returns the size of the stack
    int size() const {
        int count = 0;
        Node* current = top;
        while (current != nullptr) {
            ++count;
            current = current->next;
        }
        return count;
    }
};

int main() {
    Stack<int> stack;

    stack.push(10);
    stack.push(20);
    stack.push(30);

    std::cout << "Top element: " << stack.peek() << std::endl;

    std::cout << "Popping elements:\n";
    while (!stack.isEmpty()) {
        std::cout << stack.pop() << std::endl;
    }

    try {
        stack.pop();  // This should throw an exception because the stack is empty
    } catch (const std::out_of_range& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
