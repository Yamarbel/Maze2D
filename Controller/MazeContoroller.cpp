#include "MazeContoroller.h"

using namespace std;

MazeContoroller::MazeContoroller()
{
    Commands["dir"] =				new DirRequest();
    Commands["generate_maze"] =		new GenerateRequest();
    Commands["display"] =			new DisplayRequest();
    Commands["save_maze"] =			new SaveRequest();
    Commands["load_maze"] =			new LoadRequest();
    Commands["maze_size"] =			new SizeRequest();
    Commands["file_size"] =			new FileSizeRequest();
    Commands["solve"] =				new SolveRequest();
    Commands["display_solution"] =	new SolutionRequest();
    Commands["exit"] =				new ExitRequest();
}

MazeContoroller::~MazeContoroller(){}

void MazeContoroller::InitializeCommand(const string& str)
{
    vector<string> commands;
    string word = "";
    for (auto Str : str)
    {
        if (Str != ' ')
        {
            word = word + Str;
        }
        else
        {
            commands.push_back(word);
            word = "";
        }
    }
    commands.push_back(word);
    Args = commands;

    if (Commands[commands[0]]) {
        Commands[commands[0]]->run(commands);
    }
}
