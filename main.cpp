#include "HashTable_Chaining.h"
#include "HashTable_OpenAddressing.h"
#include "HashTable_Cuckoo.h"
#include <unordered_map>
#include <chrono>
#include <fstream>
#include <random>
#include <cmath>

/* ---------------------------------------------------------------------------*/
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> dist(1, 10000);
/* ---------------------------------------------------------------------------*/

void TestOpenAddressing(int n = 100) {
    auto* table = new HashTable_OpenAddressing<int, char>;
    string nameArchive = "../DataOpenAddressing.csv";
    ofstream archive;

    auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < n; i++) {
        table->insert(i, char((i%221)+33));
    }
    auto end = std::chrono::steady_clock::now();

    cout << "Insert " << n << " elements in HashTable (OpenAddressing): "
         << chrono::duration_cast<chrono::microseconds>(end - start).count()
         << " ms" << endl;

    archive.open(nameArchive.c_str(), fstream::app);
    archive << chrono::duration_cast<chrono::microseconds>(end-start).count() << ",";
    archive.close();

    start = std::chrono::steady_clock::now();
    for (int i = 0; i < n; i++) {
        table->search(i);
    }
    end = std::chrono::steady_clock::now();

    cout << "Search " << n << " elements in HashTable (OpenAddressing): "
         << chrono::duration_cast<chrono::microseconds>(end - start).count()
         << " ms" << endl;

    archive.open(nameArchive.c_str(), fstream::app);
    archive << chrono::duration_cast<chrono::microseconds>(end-start).count() << "," << table->getNumberReHashes() << "," << n << "\n";
    archive.close();

    cout << "Number of rehashes: " << table->getNumberReHashes() << endl << endl;

    delete table;
}


void TestChaining(size_t n = 100) {
    auto* table = new HashTable_Chaining<int, char>;
    string nameArchive = "../DataChaining.csv";
    ofstream archive;

    auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < n; i++) {
        table->insert(i, char((i%221)+33));
    }
    auto end = std::chrono::steady_clock::now();

    cout << "Insert " << n << " elements in HashTable (Chaining): "
         << chrono::duration_cast<chrono::microseconds>(end - start).count()
         << " ms" << endl;

    archive.open(nameArchive.c_str(), fstream::app);
    archive << chrono::duration_cast<chrono::microseconds>(end-start).count() << ",";
    archive.close();

    start = std::chrono::steady_clock::now();
    for (int i = 0; i < n; i++) {
        table->search(i);
    }
    end = std::chrono::steady_clock::now();

    cout << "Search " << n << " elements in HashTable (Chaining): "
         << chrono::duration_cast<chrono::microseconds>(end - start).count()
         << " ms" << endl;

    archive.open(nameArchive.c_str(), fstream::app);
    archive << chrono::duration_cast<chrono::microseconds>(end-start).count() << "," << table->getNumberReHashes() << "," << n << "\n";
    archive.close();

    cout << "Number of rehashes: " << table->getNumberReHashes() << endl << endl;

    delete table;
}

void TestCuckoo(size_t n = 100) {
    auto* table = new HashTable_Cuckoo<int, char>;


    string nameArchive = "../DataCuckoo.csv";
    ofstream archive;

    auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < n; i++) {
        table->insert(i, char((i%221)+33));
    }
    auto end = std::chrono::steady_clock::now();

    cout << "Insert " << n << " elements in HashTable (Cuckoo): "
         << chrono::duration_cast<chrono::microseconds>(end - start).count()
         << " ms" << endl;

    archive.open(nameArchive.c_str(), fstream::app);
    archive << chrono::duration_cast<chrono::microseconds>(end-start).count() << ",";
    archive.close();

    start = std::chrono::steady_clock::now();
    for (int i = 0; i < n; i++) {
        table->search(i);
    }
    end = std::chrono::steady_clock::now();

    cout << "Search " << n << " elements in HashTable (Cuckoo): "
         << chrono::duration_cast<chrono::microseconds>(end - start).count()
         << " ms" << endl;

    archive.open(nameArchive.c_str(), fstream::app);
    archive << chrono::duration_cast<chrono::microseconds>(end-start).count() << "," << table->getNumberReHashes() << "," << n << "\n";
    archive.close();

    cout << "Number of rehashes: " << table->getNumberReHashes() << endl << endl;

    delete table;
}

void TestSTL(size_t n = 100) {
    auto* table = new unordered_map<int, char>;


    string nameArchive = "../DataSTL.csv";
    ofstream archive;

    auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < n; i++) {
        table->insert({i, char((i%221)+33)});
    }
    auto end = std::chrono::steady_clock::now();

    cout << "Insert " << n << " elements in HashTable (STL): "
         << chrono::duration_cast<chrono::microseconds>(end - start).count()
         << " ms" << endl;

    archive.open(nameArchive.c_str(), fstream::app);
    archive << chrono::duration_cast<chrono::microseconds>(end-start).count() << ",";
    archive.close();

    start = std::chrono::steady_clock::now();
    for (int i = 0; i < n; i++) {
        table->find(i);
    }
    end = std::chrono::steady_clock::now();

    cout << "Get " << n << " elements in HashTable (STL): "
         << chrono::duration_cast<chrono::microseconds>(end - start).count()
         << " ms" << endl;

    archive.open(nameArchive.c_str(), fstream::app);
    archive << chrono::duration_cast<chrono::microseconds>(end-start).count() << "," << "undefined" << "," << n << "\n";
    archive.close();

    delete table;
}


int main() {
    const int reps = 400; // number of repetitions
    const int powers = 7; // max -> 100^powers

    for (int i = 0; i < reps; i++) {
        for (int j = 1; j < powers; ++j) {
            TestCuckoo(pow(10, (j+1)));
            TestChaining(pow(10, (j+1)));
            TestOpenAddressing(pow(10,(j+1)));
            TestSTL(pow(10,(j+1)));
        }
    }

    return 0;
}