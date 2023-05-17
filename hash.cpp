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
    double treshold;
    double loadFactor;
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
    int countColl;
    HashTable(int _size) {
        size = _size;
        table = new Pair[size];
        loadFactor = 0;
        treshold = 0.75;
        countElements = 0;
        countColl = 0;
        for(int i=0; i<size; i++) table[i].check = 0;
    }

    HashTable(int _size, double _treshold) {
        size = _size;
        table = new Pair[size];
        loadFactor = 0;
        treshold = _treshold;
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

void checkTreshold(double treshold, int n) {
    ifstream in("text.txt");
    string insertStr;
    int insertNum;
    int i = 0;

    HashTable *hashTable = new HashTable(32, treshold);
    int start = clock();
    while(in >> insertStr >> insertNum && i<n) {

        hashTable->insert(insertStr, insertNum);
        i++;
    }
    int end = clock();
    double t = (end - start) / (double)CLOCKS_PER_SEC;
    hashTable->printHash();
    cout << treshold << " " << t << endl;
    cout << "Treshold: " << treshold << endl;
    cout << "Time insert: " << t << endl;

    // find time
    start = clock();


    end = clock();
    t = (end - start) / 10.0 / (double)CLOCKS_PER_SEC;
    //cout << "Time find: " << t << endl;
    in.close();
    //hashTable->printLog();

    delete hashTable;
}

int splitBySeps(string str, string *strArr, string seps)
{
    for (int i = 0; i < 3; i++)
        strArr[i].clear();
    int strLen, idxRes, count;

    int sepsLen = seps.length();

    strLen = str.length();
    idxRes = count = 0;
    for (int i = 0; i < strLen; i++)
    {
        bool f = false;
        for (int j = 0; j < sepsLen; j++)
        {
            if (str[i] == seps[j])
            {
                idxRes = 0;
                count++;
                f = true;
                break;
            }
        }
        if (!f)
        {
            strArr[count] += (char)str[i];
        }
    }
    return count + 1;
}

int main() {
    /*
    double treshold = 0.1;
    for(int i=0; i<9; i++) {
        checkTreshold(treshold, 1000000);
        treshold += 0.1;
    }
    */

    string strCmd;
    string *strArr = new string[3];
    HashTable *hashTable = new HashTable(32, 0.75);
    while(1) {
        cout << "put key,val" << endl;
        cout << "get key" << endl;
        cout << "del key" << endl;
        cout << "print" << endl;
        cout << "exit" << endl;
        cout << "-------------" << endl << endl;

        cout << "Enter the command: ";
        getline(cin, strCmd);
        int l = splitBySeps(strCmd, strArr, " ,");
        cout << l << endl;
        if(strArr[0] == "put") {
            hashTable->insert(strArr[1], stoi(strArr[2]));
        } else if(strArr[0] == "get") {
            int val = hashTable->find(strArr[1]);
            cout << "Value: " << val << endl;
        } else if(strArr[0] == "del") {
            hashTable->del(strArr[1]);
        } else if(strArr[0] == "print") {
            hashTable->printHash();
        } else if(strArr[0] == "exit") {
            break;
        } else {
            cout << "Incorrect command..." << endl;
        }
    }

    return 0;
}