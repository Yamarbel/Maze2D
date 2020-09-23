#pragma once
#include <iostream>
#include <string>
#include <conio.h>
#include "../Controller/Controller.h"

using namespace std;

class view {
public:
    virtual void start() = 0;
    view(ostream& out, istream& in) :_out(out), _in(in) , controller(nullptr) {};
protected:
    ostream& _out;
    istream& _in;
    Controller* controller;
};
