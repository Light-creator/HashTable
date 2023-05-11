#include <iostream>
#include <string>

using namespace std;

class HashTable {
private:
    static const int TABLE_SIZE = 20;
    
    struct Data {
        string key;
        int value;
        bool deleted;
    };
    
    Data table[TABLE_SIZE];
    
    int hashFunction(string key) {
        int sum = 0;
        for (int i = 0; i < key.length(); i++) {
            sum += key[i];
        }
        return sum % TABLE_SIZE;
    }
    
public:
    HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i].deleted = true;
        }
    }
    
    bool insert(string key, int value) {
        int index = hashFunction(key);
        int i = 0;
        while (i != TABLE_SIZE && !table[index].deleted && table[index].key != key) {
            index = (index + 1) % TABLE_SIZE;
            i++;
        }
        if (table[index].deleted || i == TABLE_SIZE) {
            cout << "index of key " << key << " = " << index << endl;
            table[index].key = key;
            table[index].value = value;
            table[index].deleted = false;
            return true; // insert succeeded
        }
        return false; // insert failed
    }
    
    bool remove(string key) {
        int index = hashFunction(key);
        int i = 0;
        while (i != TABLE_SIZE && (!table[index].deleted && table[index].key != key)) {
            index = (index + 1) % TABLE_SIZE;
            i++;
        }
        if (!table[index].deleted && table[index].key == key) {
            table[index].deleted = true;
            return true; // remove succeeded
        }
        return false; // remove failed
    }
    
    int find(string key) {
        int index = hashFunction(key);
        int i = 0;
        while (i != TABLE_SIZE && (!table[index].deleted && table[index].key != key)) {
            index = (index + 1) % TABLE_SIZE;
            i++;
        }
        if (!table[index].deleted && table[index].key == key) {
            return table[index].value; // found key
        }
        return -1; // key not found
    }
};

int main() {
    HashTable hashTable;
    hashTable.insert("one", 1);
    hashTable.insert("two", 2);
    hashTable.insert("three", 3);
    hashTable.insert("four", 4);
    hashTable.insert("five", 5);
    hashTable.insert("six", 6);
    hashTable.insert("seven", 7);
    hashTable.insert("eight", 8);
    hashTable.insert("nine", 9);
    hashTable.insert("ten", 10);
    hashTable.insert("eleven", 11);

    cout << "The value of key 'eight' is: " << hashTable.find("eight") << endl;
    cout << "The value of key 'ten' is: " << hashTable.find("ten") << endl;

    return 0;
}