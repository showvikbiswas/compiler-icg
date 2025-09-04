#include <iostream>
#include <vector>

#ifndef PARAMETER 
#define PARAMETER

using namespace std;

class Parameter {
    public:
        string name, type;

    Parameter(string name, string type) {
        this->name = name;
        this->type = type;
    }

};

#endif