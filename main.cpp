#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

int main() {
    string directoryName;
    getline(cin, directoryName);
    string pathToDir = "..\\";
    pathToDir += directoryName;

    for (const auto &entry: fs::directory_iterator(pathToDir)){
        const fs::path &currentPath = entry.path();
        string fileExtension = currentPath.extension().string();
        if (fileExtension != ".csv") continue;

        string currentLine;
        ifstream currentFile;
        string stringFilePath = currentPath.string();

        currentFile.open(stringFilePath);
        getline(currentFile, currentLine);
        cout << currentLine << endl;
    }
}
