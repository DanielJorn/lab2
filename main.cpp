#include <iostream>
#include <filesystem>
#include "lib.h"

using namespace std;
namespace fs = std::filesystem;

int main() {
    string directoryPath = requestDirectoryPath();

    for (const auto &entry: fs::directory_iterator(directoryPath)) {
        process_entry(entry);
    }
}
