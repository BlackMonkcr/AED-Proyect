#include "HashTable_Chaining.h"
#include <chrono>
#include <fstream>
#include "HashTable_OpenAddressing.h"

void TestOpenAddressing(int n = 100) {
    HashTable_OpenAddressing<int, char> table;
    string nameArchive = "../DataOpenAddressing.csv";
    ofstream archive;
    auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < n; i++) {
        table.insert(i, char(i%256));
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
        table.get(i);
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
    return 0;
}