#include <iostream>
#include <fstream>
#include <filesystem>
#include "lib.h"

using namespace std;
namespace fs = std::filesystem;

int main() {
    const string delimiter = ",";
    string directoryPath = requestDirectoryPath();
    int matchesInLeague = 10;

    for (const auto &entry: fs::directory_iterator(directoryPath)) {
        const fs::path &currentPath = entry.path();
        string fileExtension = currentPath.extension().string();
        if (fileExtension != ".csv") continue;

        string stringFilePath = currentPath.string();

        string currentLine;
        ifstream currentFile;
        currentFile.open(stringFilePath);

        int teamsCount = getTeamCount(stringFilePath);

        // skip the first line
        getline(currentFile, currentLine);
        for (int teamInd = 0; teamInd < teamsCount; ++teamInd) {
            getline(currentFile, currentLine);

            int teamNameEndInd = currentLine.find_first_of(delimiter);
            string teamName = string(currentLine, 0, teamNameEndInd);

            int teamScore = 0;
            int matchResultStartInd = teamNameEndInd + 1;

            for (int matchInd = 0; matchInd < matchesInLeague; ++matchInd) {
                int matchResultEndInd = currentLine.find_first_of(delimiter, matchResultStartInd);

                string matchResultString = string(currentLine, matchResultStartInd, matchResultEndInd - matchResultStartInd);
                matchResultStartInd = matchResultEndInd + 1;

                cout << matchResultString << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}
