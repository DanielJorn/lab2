#include <iostream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

/* Returns the path to the directory with the data  */
string requestDirectoryPath();

/* Processes the given entry following the lab task */
void process_entry(const fs::directory_entry &entry);