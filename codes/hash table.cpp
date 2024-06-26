#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;

class HashTable {
private:
    int capacity;
    vector<list<pair<string, string>>> table;

    int hashFunction(const string& key) {
        int hash = 0;
        for (char ch : key) {
            hash = (hash * 31 + ch) % capacity;
        }
        return hash;
    }

public:
    HashTable(int size) : capacity(size) {
        table.resize(capacity);
    }

    void insert(const string& key, const string& value) {
        int hashValue = hashFunction(key);
        auto& cell = table[hashValue];
        for (auto& kv : cell) {
            if (kv.first == key) {
                kv.second = value;
                return;
            }
        }
        cell.emplace_back(key, value);
    }

    string search(const string& key) {
        int hashValue = hashFunction(key);
        auto& cell = table[hashValue];
        for (const auto& kv : cell) {
            if (kv.first == key) {
                return kv.second;
            }
        }
        return "Not found";
    }

    void remove(const string& key) {
        int hashValue = hashFunction(key);
        auto& cell = table[hashValue];
        for (auto it = cell.begin(); it != cell.end(); ++it) {
            if (it->first == key) {
                cell.erase(it);
                return;
            }
        }
    }
};

int main() {
    HashTable ht(10);
    ht.insert("apple", "10");
    ht.insert("banana", "20");
    ht.insert("orange", "30");

    cout << "Search apple: " << ht.search("apple") << endl;
    cout << "Search banana: " << ht.search("banana") << endl;
    cout << "Search grape: " << ht.search("grape") << endl;

    ht.remove("banana");
    cout << "Search banana after removal: " << ht.search("banana") << endl;

    return 0;
}
