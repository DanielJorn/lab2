#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

const string csv_delimiter = ",";
const string scoreDelimiter = ":";
const int matchesInLeague = 10;

void process_entry(const filesystem::directory_entry& entry);
bool is_csv(const fs::directory_entry& entry);
int getTeamCount(const string& path);

/** Takes a string with team info as a parameter.
    Returns the team's final score.
*/
int process_teamResult(const string& teamLine, vector<string>& leagueTable);
string getTeamName(const string& teamLine);
void outputTable(vector<string>& leagueTable, int teamsCount);

/** Takes a string with result of a match as a parameter.
    Returns the points the team got for the match.
*/
int process_matchResult(const string& matchString);
int teamMatchScore(const string& matchString);
int opponentMatchScore(const string& matchString);
string getMatchResult(int teamScore, int opponentScore);
int getPoints(string result);

string requestDirectoryPath() {
    string dirName;
    getline(cin, dirName);

    string pathToDir = "..\\";
    pathToDir += dirName;
    return pathToDir;
}

void process_entry(const fs::directory_entry& entry) {
    if (!is_csv(entry)) return;

    string currentLine;
    ifstream currentFile;
    string filePath = entry.path().string();
    

    currentFile.open(filePath);
    int teamsCount = getTeamCount(filePath);
    vector<string> leagueTable;

    // skip the first line
    getline(currentFile, currentLine);

    for (int teamInd = 0; teamInd < teamsCount; ++teamInd) {
        string teamLine;
        getline(currentFile, teamLine);

        process_teamResult(teamLine, leagueTable);
    }
    
    outputTable(leagueTable, teamsCount);
}

void outputTable(vector<string>& leagueTable, int teamsCount)
{
    cout << endl;
    for (int i = 0; i < teamsCount; i++)
        cout << leagueTable[i] << endl;
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

int process_teamResult(const string& teamLine, vector<string> &leagueTable) {
    string teamName = getTeamName(teamLine);
    string currentLine = teamName;

    int matchResultStartInd = teamName.size() + 1;

    int finalTeamScore = 0;
    for (int matchInd = 0; matchInd < matchesInLeague; ++matchInd) {
        int matchResultEndInd = teamLine.find_first_of(csv_delimiter, matchResultStartInd);
        string matchResultString = string(teamLine, matchResultStartInd, matchResultEndInd - matchResultStartInd);

        finalTeamScore += process_matchResult(matchResultString);

        matchResultStartInd = matchResultEndInd + 1;
    }
    currentLine += " " + to_string(finalTeamScore);
    leagueTable.push_back(currentLine);

    return finalTeamScore;
}

string getTeamName(const string& teamLine) {
    int teamNameEndInd = teamLine.find_first_of(csv_delimiter);
    string teamName = string(teamLine, 0, teamNameEndInd);
    return teamName;
}

int process_matchResult(const string& matchString) {
    int teamScore = teamMatchScore(matchString);
    int opponentScore = opponentMatchScore(matchString);

    string result = getMatchResult(teamScore, opponentScore);
    int pointsGot = getPoints(result);
    //cout << teamScore << ":" << opponentScore << " " << result << endl;

    return pointsGot;
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

string getMatchResult(int teamScore, int opponentScore) {
    string result = "LOSE";
    if (teamScore > opponentScore) {
        result = "WIN";
    }
    else if (teamScore < opponentScore) {
        result = "LOSE";
    }
    else {
        result = "DRAW";
    }

    return result;
}

int getPoints(string result) {
    int points = 0;
    if (result == "WIN") {
        points = 3;
    }
    else if (result == "DRAW") {
        points = 1;
    }

    return points;
}

