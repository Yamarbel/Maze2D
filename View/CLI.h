#include <iostream>
#include <string>
#include "../Controller/MazeContoroller.h"
#include "view.h"

using namespace std;

class CLI : public view
{
public:
	void menu();
	CLI(ostream& out, istream& in) :view(out, in), exit(1) {
		controller = new MazeContoroller();
	};
	void start() {
		while (exit != 0) {
			system("cls");
			menu();
			string client_input;
			if (exit != 0) {
				getline(cin, client_input);
				controller->InitializeCommand(client_input);
				cout << "Press any key to continue...";
				_getch();
			}
		}
	}
private:
	int exit;
};
