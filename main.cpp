#include <iostream>
#include <filesystem>
#include <vector>
#include <fstream>
#include "lib.h"

using namespace std;
namespace fs = std::filesystem;
ofstream outFile;

int main() {
    string directoryPath = requestDirectoryPath();
    vector<string> leagueTable;
    for (const auto &entry: fs::directory_iterator(directoryPath)) {
        process_entry(entry, leagueTable);
    }
    sortTable(leagueTable);
    ofstream outFile("results.csv");
    if (!outFile) {
        cout << "Cannot open file" << endl;
        return 0;
    }
    for (int i = 0; i < leagueTable.size(); i++) {
        outFile << leagueTable[i] << endl;
    }
    outFile.close();
}
