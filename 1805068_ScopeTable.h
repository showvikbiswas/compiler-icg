#include <string>
#include <cstddef>
#include <iostream>
#include <string>
#include <string.h>
#include "1805068_SymbolInfo.h"
#include <stdio.h>

using namespace std;

static unsigned long sdbm(unsigned char *str);

class ScopeTable
{
private:
    SymbolInfo** buckets;
    ScopeTable* parentScope;
    int totalBuckets;
    string id;

    int sdbm(string str)
    {
        uint32_t hash = 0;
        int c;

        for(int i = 0; i < str.length(); i++)
        {
            c = str[i];
            hash = c + (hash << 6) + (hash << 16) - hash;
        }

        hash = hash % totalBuckets;

        return hash;
    }

public:
    ScopeTable(int totalBuckets)
    {
        parentScope = NULL;
        this->totalBuckets = totalBuckets;
        buckets = new SymbolInfo*[totalBuckets];
        for(int i = 0; i < totalBuckets; i++)
        {
            buckets[i] = NULL;
        }
        id = "";
    }

    ScopeTable *getParentScope()
    {
        return parentScope;
    }


    bool insert(SymbolInfo symbolInfo)
    {
        int length = symbolInfo.getName().length();
        int bucket = sdbm(symbolInfo.getName());
        int counter = 0;

        if(buckets[bucket] == NULL)
        {
            buckets[bucket] = new SymbolInfo;
            *buckets[bucket] = symbolInfo;
            return true;
        }
        else
        {   
            SymbolInfo *current = buckets[bucket];
            if(current->getName() == symbolInfo.getName())
            {
                // cout << symbolInfo.getName() + " already exists in current ScopeTable\n\n";
                return false;
            }
            while(current->getNext() != NULL)
            {
                current = current->getNext();
                counter++;
                if(current->getName() == symbolInfo.getName()) {
                    return false;
                }
            }
            SymbolInfo *next = new SymbolInfo;
            *next = symbolInfo;
            current->setNext(next);
            return true;
        }
        // cout << symbolInfo.getName() + " already exists in current ScopeTable\n\n";
        return false;
    }

    void setParentScope(ScopeTable *parentScopeTable)
    {
        this->parentScope = parentScopeTable;
    }

    bool remove(string entry)
    {
        // in each bucket
        for(int i = 0; i < totalBuckets; i++)
        {
            int counter = 0;
            SymbolInfo *current = buckets[i];
            // if the current pointer points to null, then there are no entries in this bucket. move on to the next one
            if (current == NULL)
                continue;

            SymbolInfo *symbolInfo = lookUp(entry);
            // if the first entry of the bucket matches the query, make the next entry the new "head"
            if (current == symbolInfo)
            {
                SymbolInfo *temp = buckets[i];
                buckets[i] = current->getNext();           // removed
                temp->setNext(NULL);
                delete temp;
                // cout << "Deleted entry " << i << ", " << counter << " from current scopetable" << endl;
                return true;
            }
            // else, keep going

            if (symbolInfo == NULL)
            {
                // cout << "Not found" << endl;
                return false;
            }
            
            while (current->getNext() != symbolInfo)
            {
                if (current->getNext() == NULL)
                    return false;
                current = current->getNext();
                counter++;
            }

            current->setNext(symbolInfo->getNext());
            symbolInfo->setNext(NULL);
            delete symbolInfo;
            // cout << "Deleted entry " << i << ", " << counter+1 << " from current scopetable" << endl;
            return true;

            // SymbolInfo *current1 = current;
            
            // while (current != NULL)
            // {
            //     if (current->getName() == entry)
            //     {
            //         SymbolInfo *temp = current;
            //         current1->setNext(current->getNext());
            //         delete temp;
            //         cout << "Deleted entry " << i << ", " << counter << " from current scopetable" << endl;
            //         return true;
            //     }
            //     else {
            //         current1 = current;
            //     }
            //     current = current->getNext();
            //     counter++;
            // }
        }
        // cout << "Not found" << endl;
        return false;
    }

    void print(FILE* logFile)
    {
        fprintf(logFile, "ScopeTable # %s\n", (this->id).c_str());
        for(int i = 0; i < totalBuckets; i++)
        {
            SymbolInfo *current = buckets[i];
            if (current == NULL) 
                continue;
            fprintf(logFile, "%d --> ", i);
            while (current != NULL)
            {
                fprintf(logFile, "< %s , ID > ", current->getName().c_str());
                current = current->getNext();
            }

            fprintf(logFile, "\n");
        }
        fprintf(logFile, "\n");
    }

    SymbolInfo *lookUp(string name)
    {
        SymbolInfo *current = NULL;
        for(int i = 0; i < totalBuckets; i++)
        {
            int counter = 0;
            current = buckets[i];
            if (current == NULL)
                continue;

            while (current != NULL)
            {
                if (current->getName() == name)
                {
                    // cout << "Found in scopetable " << id << " at position " << i << ", " << counter << endl;
                    return current;
                }
                current = current->getNext();
                counter++;
            }
            
        }
        return current;
    }

    void setID(string id)
    {
        this->id = id;
    }

    string getID()
    {
        return this->id;
    }

    ~ScopeTable()
    {
        for (int i = 0; i < totalBuckets; i++)
        {
            delete buckets[i];
            // SymbolInfo *current1 = current->getNext();
            // while (current != NULL)
            // {
            //     delete current;
            //     if (current1 != NULL)
            //         current1 = current1->getNext();
            //     current = current1;
            // }
        }
        delete[] buckets;
    }
};