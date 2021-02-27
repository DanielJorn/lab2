#include <iostream>
#include <fstream>

using namespace std;


string requestDirectoryPath(){
    string dirName;
    getline(cin, dirName);

    string pathToDir = "..\\";
    pathToDir += dirName;
    return pathToDir;
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