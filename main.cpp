#include <iostream>
#include <fstream>
#include <filesystem>
#include "lib.h"

using namespace std;
namespace fs = std::filesystem;

enum MATCH_RESULT {
    WIN,
    LOSE,
    DRAW
};

int main() {
    const string csv_delimiter = ",";
    const string scoreDelimiter = ":";
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

            int teamNameEndInd = currentLine.find_first_of(csv_delimiter);
            string teamName = string(currentLine, 0, teamNameEndInd);

            int finalTeamScore = 0;
            int matchResultStartInd = teamNameEndInd + 1;

            cout << teamName << endl;

            for (int matchInd = 0; matchInd < matchesInLeague; ++matchInd) {
                int matchResultEndInd = currentLine.find_first_of(csv_delimiter, matchResultStartInd);

                string matchResultString = string(currentLine, matchResultStartInd, matchResultEndInd - matchResultStartInd);

                int teamScoreEndInd = matchResultString.find_first_of(scoreDelimiter);
                string teamScoreString = string(matchResultString, 0, teamScoreEndInd);

                int opponentScoreStartInd  = teamScoreEndInd + 1;
                int opponentScoreEndInd    = matchResultString.size();
                string opponentScoreString = string(matchResultString, opponentScoreStartInd, opponentScoreEndInd - opponentScoreStartInd);

                int teamScoreInt = stoi(teamScoreString);
                int opponentScoreInt = stoi(opponentScoreString);

                MATCH_RESULT result;
                if (teamScoreInt > opponentScoreInt){
                    result = WIN;
                } else if (teamScoreInt < opponentScoreInt) {
                    result = LOSE;
                } else {
                    result = DRAW;
                }

                if (result == WIN) {
                    finalTeamScore += 3;
                } else if (result == DRAW){
                    finalTeamScore += 1;
                }

                cout << teamScoreInt << ":" << opponentScoreInt << " " << result << endl;
                matchResultStartInd = matchResultEndInd + 1;
            }
            cout << finalTeamScore << endl;
            cout << endl;
        }
        cout << endl;
    }
}
