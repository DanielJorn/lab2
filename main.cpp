#include <iostream>
#include <fstream>
#include <filesystem>
#include "lib.h"

using namespace std;
namespace fs = std::filesystem;


int main() {
    string directoryPath = requestDirectoryPath();

    for (const auto &entry: fs::directory_iterator(directoryPath)) {
        const fs::path &currentPath = entry.path();
        string fileExtension = currentPath.extension().string();
        if (fileExtension != ".csv") continue;

        string stringFilePath = currentPath.string();

        string currentLine;
        ifstream currentFile;
        currentFile.open(stringFilePath);

        int teamsCount = getTeamCount(stringFilePath);

        for (int i = 0; i < teamsCount; ++i) {
            getline(currentFile, currentLine);
            cout << currentLine << endl;
        }
    }
}
