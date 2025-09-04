#include "1805068_ScopeTable.h"
#include <stdio.h>
#include <cstddef>
#include <vector>
#include <string>

using namespace std;

class SymbolTable
{
private:
    ScopeTable* currentScopeTable;
    int buckets;
    vector<int> ids;
    int currentLevel;

public:
    SymbolTable(int buckets)
    {
        this->buckets = buckets;
        currentLevel = 0;
        ids.push_back(1);
        currentScopeTable = new ScopeTable(buckets);
        currentScopeTable->setID(to_string(ids[currentLevel]));
//        currentScopeTable->setUID(currentScopeTable->getUID() + 1);
    }

    void enterScope()
    {
        ScopeTable *newScopeTable = new ScopeTable(this->buckets);
        ScopeTable *current = currentScopeTable;
        currentLevel++;
        if(currentLevel == ids.size())
        {
            ids.push_back(1);
        }
        else
        {
            if (currentLevel != 0)
                ids[currentLevel]++;
        }
        newScopeTable->setParentScope(current);
        string newID;
        if (currentScopeTable == NULL)
        {
            newID = to_string(ids[0]);
        }
        else 
        {
            newID = currentScopeTable->getID() + "." + to_string(ids[currentLevel]);
        }
        newScopeTable->setID(newID);
        currentScopeTable = newScopeTable;
    }

    void exitScope()
    {
        if (currentScopeTable == NULL)
        {
            cout << "NO CURRENT SCOPE" << endl;
            return;
        }

        ScopeTable *newScopeTable = currentScopeTable->getParentScope();
        if (ids.size() > currentLevel)
            ids[currentLevel+1] = 0;
        currentLevel--;
        delete currentScopeTable;
        currentScopeTable = newScopeTable;
    }

    bool insert(string name, string type)
    {
        if (currentScopeTable == NULL)
        {
            enterScope();
        }
            

        SymbolInfo symbolInfo;
        symbolInfo.setName(name);
        symbolInfo.setType(type);
        bool result = currentScopeTable->insert(symbolInfo);
        return result;
    }

    bool insert(SymbolInfo symbolInfo)
    {
        return currentScopeTable->insert(symbolInfo);
    }

    bool remove(string name)
    {
        if (currentScopeTable == NULL)
        {
            cout << "NO CURRENT SCOPE" << endl;
            return false;
        }

        bool result = currentScopeTable->remove(name);
        return  result;
    }

    SymbolInfo *lookUp(string name)
    {
        if (currentScopeTable == NULL)
        {
            // cout << "NO CURRENT SCOPE" << endl;
            return NULL;
        }

        SymbolInfo *result = NULL;
        ScopeTable *current = currentScopeTable;
        while (current != NULL)
        {
            result = current->lookUp(name);
            if (result != NULL)
            {
                return result;
            }
            current = current->getParentScope();
        }
        // cout << "Not found" << endl;
        return result;
    }

    void printCurrentScopeTable(FILE* logFile)
    {
        currentScopeTable->print(logFile);
    }

    void printAllScopeTables(FILE* logFile)
    {
        ScopeTable *current = currentScopeTable;
        while (current != NULL)
        {
            current->print(logFile);
            current = current->getParentScope();
            if (current != NULL)
                fprintf(logFile, "\n");
        }
        fprintf(logFile, "\n");
    }

    string getScopeID()
    {
        return currentScopeTable->getID();
    }

    ~SymbolTable()
    {
        if (currentScopeTable != NULL)
        {
            ScopeTable *current = currentScopeTable;
            ScopeTable *current1 = current->getParentScope();
            while (current != NULL)
            {
                delete current;
                current = current1;
                if (current1 != NULL)
                    current1 = current1->getParentScope();
            }
        }   
    }
};
