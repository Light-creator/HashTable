#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

struct Pair {
    string key;
    int val;
    int check;
};

class HashTable {

private:
    int size;
    int countElements;
    int countColl;
    double loadFactor;
    double treshold;
    Pair *table;

    int hashFunc(string key) {
        int A = 1, B = 0;
        for (size_t i = 0; i < key.length(); i++)
        {
            int ascii = key.at(i);
            A += ascii;
            B += A % 65521;
        }
        int res = (B << 16) | A;
        cout << res << endl;
        return res % size;
    }

    void rehash() {
        Pair *newTable = new Pair[size*2];
        Pair *tmp = table;
        int i = 0;
        for(int j=0; j<size*2; j++) newTable[j].check = 0;
        table = newTable;
        countElements = 0;
        countColl = 0;
        size *= 2;
        while(i < size/2) {
            if(tmp[i].check) insert(tmp[i].key, tmp[i].val);
            i++;
        }

        newTable = nullptr;
        tmp = nullptr;
        delete[] tmp;
    }

public:
    HashTable(int _size) {
        size = _size;
        table = new Pair[size];
        loadFactor = 0;
        treshold = 0.75;
        countElements = 0;
        countColl = 0;
        for(int i=0; i<size; i++) table[i].check = 0;
    }

    ~HashTable() {
        delete[] table;
    }

    bool insert(string key, int val) {
        int idx = hashFunc(key);
        int i=0;

        if(table[idx].check) countColl++;
        while(i < size && table[idx].check && table[idx].key != key) {
            idx = (idx + i*i)%size;
            i++;
        }

        if(table[idx].key == key) {
            cout << "key: " << key << " already exists..." << endl;
            return false;
        } else {
            table[idx].key = key;
            table[idx].val = val;
            table[idx].check = 1;
            countElements++;
            loadFactor = (double)countElements/size;
            if(loadFactor >= treshold) {
                printLog();
                rehash();
            }
            return true;
        }
    }

    int del(string key) {
        int idx = hashFunc(key);
        int i=0;    
        while(i < size && table[idx].check && table[idx].key != key) {
            idx = (idx + i*i)%size;
            i++;
        }
        if(table[idx].key == key) {
            table[idx].check = 0;
            countElements--;
            return table[idx].val;
        }

        cout << "Pair with key = " << key << " does not exist..." << endl;
        return -1;     
    }

    int find(string key) {
        int idx = hashFunc(key);
        int i=0;    
        while(i < size && table[idx].check && table[idx].key != key) {
            idx = (idx + i*i)%size;
            i++;
        }
        if(table[idx].key == key) {
            return table[idx].val;
        }

        return -1;  
    }

    void printLog() {
        cout << "load factor = " << loadFactor << endl;
        cout << "collinsion count = " << countColl << endl;
        cout << "Elements count = " << countElements << endl;
        cout << "----------------------------------- "<< endl;
    }

    void printHash() {
        int i = 0;
        cout << "{" << endl;
        while(i < size) {
            if(table[i].check) cout << i << ") " << table[i].key << " => " << table[i].val << endl;
            else cout << i << ") None" << endl;
            i++;
        }
        cout << "}" << endl;
        cout << "load factor = " << loadFactor << endl;
        cout << "collinsion count = " << countColl << endl;
        cout << "Elements count = " << countElements << endl;
    }
};

int main() {
    ifstream in("text.txt");
    string insertStr;
    int insertNum;
    int i = 0;

    HashTable *hashTable = new HashTable(32);
    int start = clock();
    while(in >> insertStr >> insertNum && i<10000) {

        hashTable->insert(insertStr, insertNum);
        //if(i%10000 == 0) hashTable->printLog();
        i++;
    }
    int end = clock();
    double t = (end - start) / (double)CLOCKS_PER_SEC;
    cout << "Time insert: " << t << endl;

    // find time
    start = clock();

    hashTable->find("56");
    hashTable->find("23");
    hashTable->find("44");
    hashTable->find("11");
    hashTable->find("90");
    hashTable->find("900");
    hashTable->find("349");
    hashTable->find("55");
    hashTable->find("34");
    hashTable->find("34");

    end = clock();
    t = (end - start) / 10.0 / (double)CLOCKS_PER_SEC;
    cout << "Time find: " << t << endl;
    in.close();
    hashTable->printLog();

    delete hashTable;
    return 0;
}