#include "Controller.h"
#include "../Model/Maze/Maze2D.h"

using namespace std;

Controller::Controller() {}

Controller::~Controller() {}

void Controller::InitializeCommand(const string& str) {
    vector<string> commands;
    string word = "";
    for (const auto T : str) {
        if (T != ' ') {
            word = word + T;
		}
        else {
            commands.push_back(word);
            word = "";
        }
    }
    commands.push_back(word);
    Args = commands;
}
