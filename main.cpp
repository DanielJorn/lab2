#include <iostream>
#include <filesystem>
#include <vector>
#include "lib.h"

using namespace std;
namespace fs = std::filesystem;

int main() {
    string directoryPath = requestDirectoryPath();
    vector<string> leagueTable;
    for (const auto &entry: fs::directory_iterator(directoryPath)) {
        process_entry(entry, leagueTable);
    }
    outputTable(leagueTable);
    sortTable(leagueTable);
    outputTable(leagueTable);
}
