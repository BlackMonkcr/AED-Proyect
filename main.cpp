#include "HashTable_Chaining.h"
#include <chrono>
#include <fstream>
#include <array>
#include <random>
#include <unordered_map>
#include "HashTable_OpenAddressing.h"

/* ---------------------------------------------------------------------------*/
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> dist(1, 10000);
/* ---------------------------------------------------------------------------*/

void TestOpenAddressing(int n = 100) {
    HashTable_OpenAddressing<int, char> table;
    string nameArchive = "../DataOpenAddressing.csv";
    ofstream archive;

    auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < n; i++) {
        table.insert(i, char((i%221)+33));
    }
    auto end = std::chrono::steady_clock::now();

    cout << "Insert " << n << " elements in HashTable (OpenAddressing): "
         << chrono::duration_cast<chrono::microseconds>(end - start).count()
         << " ms" << endl;

    archive.open(nameArchive.c_str(), fstream::app);
    archive << (end-start).count() << ",";
    archive.close();

    start = std::chrono::steady_clock::now();
    for (int i = 0; i < n; i++) {
        table.search(i);
    }
    end = std::chrono::steady_clock::now();

    cout << "Get " << n << " elements in HashTable (OpenAddressing): "
         << chrono::duration_cast<chrono::microseconds>(end - start).count()
         << " ms" << endl;

    archive.open(nameArchive.c_str(), fstream::app);
    archive << (end-start).count() << "," << table.getNumberReHashes() << "," << n << "\n";
    archive.close();

    cout << "Number of rehashes: " << table.getNumberReHashes() << endl << endl;

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
    archive << (end-start).count() << ",";
    archive.close();

    start = std::chrono::steady_clock::now();
    for (int i = 0; i < n; i++) {
        table->search(i);
    }
    end = std::chrono::steady_clock::now();

    cout << "Get " << n << " elements in HashTable (Chaining): "
         << chrono::duration_cast<chrono::microseconds>(end - start).count()
         << " ms" << endl;

    archive.open(nameArchive.c_str(), fstream::app);
    archive << (end-start).count() << "," << table->getNumberReHashes() << "," << n << "\n";
    archive.close();

    cout << "Number of rehashes: " << table->getNumberReHashes() << endl << endl;

    delete table;
}


int main() {
    for (int i = 0; i < 10; i++) {
        TestOpenAddressing();
        TestOpenAddressing(1000);
        TestOpenAddressing(10000);
        TestOpenAddressing(100000);
        TestOpenAddressing(1000000);
        TestOpenAddressing(10000000);
        TestOpenAddressing(100000000);
    }

    for (int i = 0; i < 10; i++) {
        TestChaining();
        TestChaining(1000);
        TestChaining(10000);
        TestChaining(100000);
        TestChaining(1000000);
        TestChaining(10000000);
        TestChaining(100000000);
    }
    return 0;
}