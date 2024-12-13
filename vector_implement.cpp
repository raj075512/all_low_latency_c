#include <iostream>
#include <stdexcept>  // For exceptions like out_of_range
using namespace std;

template <typename T>
class MyVector {
private:
    T* arr;               // Pointer to the dynamic array
    size_t capacity;      // Current capacity of the vector
    size_t size;          // Current size of the vector

    // Resizes the vector when the capacity is exceeded
    void resize() {
        capacity *= 2;  // Double the capacity
        T* newArr = new T[capacity];
        
        // Copy the old array elements to the new array
        for (size_t i = 0; i < size; ++i) {
            newArr[i] = arr[i];
        }

        // Delete old array and update pointer
        delete[] arr;
        arr = newArr;
    }

public:
    // Constructor
    MyVector() : arr(nullptr), capacity(0), size(0) {}

    // Destructor
    ~MyVector() {
        delete[] arr;
    }

    // Adds an element to the end of the vector
    void push_back(const T& value) {
        if (size == capacity) {
            resize();  // Resize if the capacity is reached
        }
        if (arr == nullptr) {
            arr = new T[1];
            capacity = 1;
        }
        arr[size++] = value;
    }

    // Access an element by index (with bounds checking)
    T& at(size_t index) {
        if (index >= size) {
            throw out_of_range("Index out of range");
        }
        return arr[index];
    }

    // Const version of the at method (for read-only access)
    const T& at(size_t index) const {
        if (index >= size) {
            throw out_of_range("Index out of range");
        }
        return arr[index];
    }

    // Returns the current size of the vector
    size_t get_size() const {
        return size;
    }

    // Returns the current capacity of the vector
    size_t get_capacity() const {
        return capacity;
    }

    // Removes the last element
    void pop_back() {
        if (size > 0) {
            --size;
        }
    }

    // Checks if the vector is empty
    bool empty() const {
        return size == 0;
    }

    // Overload the subscript operator for element access
    T& operator[](size_t index) {
        return arr[index];
    }

    const T& operator[](size_t index) const {
        return arr[index];
    }

    // A method to clear the vector
    void clear() {
        size = 0;
    }

    // A method to display the vector's elements
    void print() const {
        for (size_t i = 0; i < size; ++i) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    MyVector<char> vec;
    
    vec.push_back('a');
    vec.push_back('b');
    vec.push_back('c');

    cout << "Vector elements: ";
    vec.print();

    cout << "Element at index 1: " << vec.at(1) << endl;

    vec.pop_back();
    cout << "After pop_back, vector elements: ";
    vec.print();

    cout << "Vector size: " << vec.get_size() << ", capacity: " << vec.get_capacity() << endl;

    return 0;
}
