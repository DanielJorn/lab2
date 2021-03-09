#include <iostream>
#include <filesystem>
#include <vector>
#include <fstream>
#include "lib.h"

using namespace std;
namespace fs = std::filesystem;

int main() {
    cout << "Please enter a folder name: ";
    string directoryPath = requestDirectoryPath();
    vector<string> leagueTable;
    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        process_entry(entry, leagueTable);
    }
    sortTable(leagueTable);

    outputFile(leagueTable);
}
