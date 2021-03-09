#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

const string csv_delimiter = ",";
const string scoreDelimiter = ":";
const int matchesInLeague = 10;

void process_entry(const filesystem::directory_entry& entry, vector<string>& leagueTable);
void sortTable(vector<string>& leagueTable);
bool is_csv(const fs::directory_entry& entry);
int getTeamCount(const string& path);

/** Takes a string with team info as a parameter.
    Returns the team's final score.
*/
int process_teamResult(const string& teamLine, vector<string>& leagueTable);
string getTeamName(const string& teamLine);
void outputFile(vector<string>& leagueTable);
int extractPoints(string& currentLine);

/** Takes a string with result of a match as a parameter.
    Returns the points the team got for the match.
*/
int process_matchResult(const string& matchString);
int teamMatchScore(const string& matchString);
int opponentMatchScore(const string& matchString);
int getMatchResult(int teamScore, int opponentScore);


string requestDirectoryPath() {
    string dirName;
    getline(cin, dirName);

    string pathToDir = "..\\";
    pathToDir += dirName;
    return pathToDir;
}

void process_entry(const fs::directory_entry& entry, vector<string>& leagueTable) {
    if (!is_csv(entry)) return;

    string currentLine;
    ifstream currentFile;
    string filePath = entry.path().string();


    currentFile.open(filePath);
    int teamsCount = getTeamCount(filePath);

    // skip the first line
    getline(currentFile, currentLine);

    for (int teamInd = 0; teamInd < teamsCount; ++teamInd) {
        string teamLine;
        getline(currentFile, teamLine);

        process_teamResult(teamLine, leagueTable);
    }

}

void outputFile(vector<string>& leagueTable) {
    ofstream outFile("results.csv");
    if (!outFile) {
        cout << "Cannot open file" << endl;
    }
    for (int i = 0; i < leagueTable.size(); i++) {
        outFile << leagueTable[i] << endl;
    }
    outFile.close();
}

void sortTable(vector<string>& leagueTable)
{
    for (int i = 0; i < leagueTable.size() - 1; i++) {
        for (int j = 0; j < leagueTable.size() - i - 1; j++) {
            int teamPoints = extractPoints(leagueTable[j]);
            int nextTeamPoints = extractPoints(leagueTable[j + 1]);
            if (teamPoints < nextTeamPoints) {
                string temp = leagueTable[j];
                leagueTable[j] = leagueTable[j + 1];
                leagueTable[j + 1] = temp;
            }
        }
    }
}

int extractPoints(string& currentLine) {
    int positionOfDelimiter = currentLine.find_last_of(csv_delimiter);
    string stringTeamPoints = currentLine.substr(positionOfDelimiter + 1, currentLine.length() - positionOfDelimiter - 1);
    int teamPoints = stoi(stringTeamPoints);
    return teamPoints;
}

bool is_csv(const fs::directory_entry& entry) {
    const fs::path& path = entry.path();
    string fileExtension = path.extension().string();
    return fileExtension == ".csv";
}

int getTeamCount(const string& path) {
    ifstream file;
    //the first line is the team count, we get it now
    file.open(path);

    string stringCount;
    getline(file, stringCount);
    int intCount = stoi(stringCount);

    file.close();
    return intCount;
}

int process_teamResult(const string& teamLine, vector<string>& leagueTable) {
    string teamName = getTeamName(teamLine);
    string currentLine = teamName;
    int matchResultStartInd = teamName.size();
    if (teamName.substr(0, 1) == "\"")
    {
        matchResultStartInd += 3;
    }
    else {
        matchResultStartInd += 1;
    }

    int finalTeamScore = 0;
    for (int matchInd = 0; matchInd < matchesInLeague; ++matchInd) {
        int matchResultEndInd = teamLine.find_first_of(csv_delimiter, matchResultStartInd);
        string matchResultString = string(teamLine, matchResultStartInd, matchResultEndInd - matchResultStartInd);

        finalTeamScore += process_matchResult(matchResultString);

        matchResultStartInd = matchResultEndInd + 1;
    }
    currentLine += csv_delimiter + to_string(finalTeamScore);
    leagueTable.push_back(currentLine);

    return finalTeamScore;
}

string getTeamName(const string& teamLine) {
    string teamName;
    int teamNameEndInd = 0;
    if (teamLine.substr(0, 1) == "\"") {
        teamNameEndInd = teamLine.find_last_of("\"");
        teamName = string(teamLine, 0, teamNameEndInd + 1);
        //cout << teamName << endl;
    }
    else {
        teamNameEndInd = teamLine.find_first_of(csv_delimiter);
        teamName = string(teamLine, 0, teamNameEndInd);
    }
    return teamName;
}

int process_matchResult(const string& matchString) {
    int teamScore = teamMatchScore(matchString);
    int opponentScore = opponentMatchScore(matchString);

    int result = getMatchResult(teamScore, opponentScore);

    return result;
}

int teamMatchScore(const string& matchString) {
    int delimiterInd = matchString.find_first_of(scoreDelimiter);
    string teamScoreString = string(matchString, 0, delimiterInd);

    int scoreInt = stoi(teamScoreString);
    return scoreInt;
}

int opponentMatchScore(const string& matchString) {
    int delimiterInd = matchString.find_first_of(scoreDelimiter);

    int scoreStartInd = delimiterInd + 1;
    int scoreEndInd = matchString.size();
    string opponentScoreString = string(matchString, scoreStartInd, scoreEndInd - scoreStartInd);

    int scoreInt = stoi(opponentScoreString);
    return scoreInt;
}

int getMatchResult(int teamScore, int opponentScore) {
    int result = 0;
    if (teamScore > opponentScore) {
        result = 3;
    }
    else if (teamScore < opponentScore) {
        result = 0;
    }
    else {
        result = 1;
    }

    return result;
}


