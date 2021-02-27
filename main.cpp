#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;
using namespace std::filesystem;

int main() {
    string directoryName;
    getline(cin, directoryName);

    string path = "..\\";
    path += directoryName;
    path += "\\league1.csv";

    string currentLine;
    ifstream currentFile;
    currentFile.open(path);

    while (getline(currentFile, currentLine)){
        cout << currentLine << endl;
    }
}
