#include "AnimalManager.h"
#include "FileProcessor.h"
#include <string>
#include <windows.h>

int main(int argc, char* argv[]) {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    AnimalManager manager;
    FileProcessor fp(manager);
    fp.processFile(argc > 1 ? argv[1] : "commands.txt");
    return 0;
}