#include <bits/stdc++.h>
#include <sstream>
#include <vector>
#include "Parameter.h"

using namespace std;

vector<string> split(string line, char delim)
{
    stringstream stream(line);
    vector<string> tokens;
    string word;
    
    while(getline(stream, word, delim)) {
        tokens.push_back(word);
    }
    return tokens;
}

bool isArray(string line) {
    int foundL = line.find("[");
    int foundR = line.find("]");
    if ((foundL != string::npos) || (foundR != string::npos)) {
        return true;
    }
    return false;
}

string getArrayName(string line) {
    int foundL = line.find("[");
    if (foundL == string::npos)
        return line;
        
    string arrayName = line.substr(0, line.find("["));
    return arrayName;
}

int getArraySize(string line) {
    string arraySize = line.substr(line.find("[") + 1);
    arraySize.pop_back();
    return stoi(arraySize);
}

vector<Parameter> getParamList(string line) {
    vector<string> params = split(line, ',');
    vector<Parameter> paramList;
    for (string param: params)
    {
        string name, type;
        // check whether type and name or only type
        if (param.find(" ") == string::npos)
        {
            // only a type, so the name of the parameter is empty
            name = " ";
            type = param;
        }
        else {
        type = split(param, ' ')[0];
        name = split(param, ' ')[1];
        }
        Parameter parameter(name, type);
        paramList.push_back(parameter);
    }
    return paramList;
}

void logData(FILE *logFile, int yylineno, string info, string token)
{
    fprintf(logFile, "Line %d: %s\n\n%s\n\n", yylineno, info.c_str(), token.c_str());
}

void logError(FILE *logFile, FILE *errorFile, int yylineno, string info)
{
    fprintf(logFile, "Error at line %d: %s\n\n", yylineno, info.c_str());
    fprintf(errorFile, "Error at line %d: %s\n\n", yylineno, info.c_str());
}

