#include <iostream>
#include <list>
#include <vector>
#include <stdexcept>

template <typename K, typename V>
class HashMap {
private:
    // Define a bucket type as a linked list of pairs (key, value)
    using Bucket = std::list<std::pair<K, V>>;

    // The hash table is an array of buckets
    std::vector<Bucket> table;
    size_t capacity;
    size_t size;

    // Hash function to compute the hash value of a key
    size_t hash(const K& key) const {
        return std::hash<K>{}(key) % capacity;
    }

public:
    // Constructor to initialize the hash map with a given capacity
    HashMap(size_t capacity = 10) : capacity(capacity), size(0) {
        table.resize(capacity);
    }

    // Insert a key-value pair into the hash map
    void insert(const K& key, const V& value) {
        size_t index = hash(key);
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                pair.second = value; // If key already exists, update the value
                return;
            }
        }
        table[index].emplace_back(key, value);
        ++size;

        // If load factor exceeds 0.7, rehash
        if (static_cast<float>(size) / capacity > 0.7) {
            rehash();
        }
    }

    // Retrieve the value for a given key
    V get(const K& key) const {
        size_t index = hash(key);
        for (const auto& pair : table[index]) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        throw std::out_of_range("Key not found");
    }

    // Remove a key-value pair from the hash map
    void remove(const K& key) {
        size_t index = hash(key);
        auto& bucket = table[index];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                bucket.erase(it);
                --size;
                return;
            }
        }
        throw std::out_of_range("Key not found");
    }

    // Check if the hash map contains a key
    bool contains(const K& key) const {
        size_t index = hash(key);
        for (const auto& pair : table[index]) {
            if (pair.first == key) {
                return true;
            }
        }
        return false;
    }

    // Get the size of the hash map
    size_t getSize() const {
        return size;
    }

private:
    // Rehash the hash map when the load factor exceeds 0.7
    void rehash() {
        capacity *= 2;
        std::vector<Bucket> newTable(capacity);
        
        for (const auto& bucket : table) {
            for (const auto& pair : bucket) {
                size_t index = std::hash<K>{}(pair.first) % capacity;
                newTable[index].emplace_back(pair);
            }
        }

        table = std::move(newTable);
    }
};

int main() {
    HashMap<std::string, int> map;

    map.insert("Alice", 30);
    map.insert("Bob", 25);
    map.insert("Charlie", 35);

    std::cout << "Size: " << map.getSize() << std::endl;

    std::cout << "Alice's age: " << map.get("Alice") << std::endl;
    std::cout << "Bob's age: " << map.get("Bob") << std::endl;

    map.remove("Alice");

    std::cout << "Size after removing Alice: " << map.getSize() << std::endl;

    try {
        std::cout << "Alice's age: " << map.get("Alice") << std::endl;  // This will throw
    } catch (const std::out_of_range& e) {
        std::cout << e.what() << std::endl;  // Output: Key not found
    }

    return 0;
}
