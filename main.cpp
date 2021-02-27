#include <iostream>
#include <fstream>

using namespace std;

int main() {
    string line;
    ifstream file;
    string path = "..\\data\\league1.csv";
    file.open(path);
    while (getline(file, line)){
        cout << line << endl;
    }
}
