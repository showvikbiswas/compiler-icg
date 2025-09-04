#include <ios>
#include <iostream>
#include <string>
#include <vector>
#include "Parameter.h"

using namespace std;

class SymbolInfo
{

public:

    string name;
    string type;
    SymbolInfo *next;
    int size;
    vector<Parameter> paramlist;
    bool func;
    bool inTable;
    bool definedFunc;
    bool global;
    int offset;
    int addOrSub;
    

    SymbolInfo(char *name, char* type)
    {
        this->name = name;
        this->type = type;
    }

    SymbolInfo(string name, string type)
    {
        this->name = name;
        this->type = type;
    }

    vector<Parameter> getParamList()
    {
        return paramlist;
    }

    bool isDefined()
    {
        return definedFunc;
    }

    void setGlobal(bool global) {
        this->global = global;
    }

    bool isGlobal() {
        return global;
    }

    int getSize()
    {
        return size;
    }

    bool isArray()
    {
        return size > 0;
    }
    
    void setName(string name)
    {
        this->name = name;
    }

    void setParams(vector<Parameter> parameters)
    {
        paramlist = parameters;
    }

    void setDefined(bool defined)
    {
        definedFunc = defined;
    }

    void setAsArray(string name, string type, int size)
    {
        this->name = name;
        this->type = type;
        this->size = size;
        this->next = NULL;
        this->definedFunc = false;
    }

    SymbolInfo()
    {
        next = NULL;
        size = -1;
        offset = 0;
        func = false;
        inTable = false;
        definedFunc = false;
        global = false;
        addOrSub = 0;
    }

    int getAddOrSub()
    {
        return addOrSub;
    }

    void setAddOrSub(int x)
    {
        addOrSub = x;
    }
    
    bool isInTable()
    {
        return inTable;
    }

    void setInTable(bool inTable)
    {
        this->inTable = inTable;
    }

    void setFunc(bool func)
    {
        this->func = func;
    }

    bool isFunc()
    {
        return func;
    }

    string getName()
    {
        return name;
    }

    void setType(string type)
    {
        this->type = type;
    }

    string getType()
    {
        return type;
    }

    SymbolInfo *getNext()
    {
        return next;
    }

    void setNext(SymbolInfo *next)
    {
        // cout << "HEHe: " << next << endl;
        // this->next = new SymbolInfo;
        // cout << "heHe: " << this->next << endl;
        this->next = next;
        // cout << "heHe: " << this->next << endl;
        
    }

    void setOffset(int offset)
    {
        this->offset = offset;
    }

    int getOffset()
    {
        return offset;
    }

    ~SymbolInfo()
    {
        delete next;
    }
};
