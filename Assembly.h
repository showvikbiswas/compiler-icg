#include <bits/stdc++.h>
#include <stdio.h>

using namespace std;

void initializeASMFile(FILE *file)
{
    string initialCode = ".MODEL SMALL\n";
    initialCode += ".STACK 100H\n"; 
    initialCode += ".DATA\n";
    initialCode += "MINUS DB 0\n";
    initialCode += ".CODE\n";

    fprintf(file, "%s", initialCode.c_str());
}

void endASMFile(FILE *file)
{
    fprintf(file, "END main");
}

void writePrintFunction(FILE *file)
{
    fprintf(file, "println_int PROC\n");
    // at this point, AX contains the number to be printed
    fprintf(file, "MOV BX, 10\n");
    fprintf(file, "XOR CX, CX\n");
    fprintf(file, "DISPLAY_LOOP:\n");
    fprintf(file, "CMP AX, 0\n");
    fprintf(file, "JGE NOT_NEGATIVE\n");
    fprintf(file, "NEG AX\n");
    fprintf(file, "MOV MINUS, 1\n");
    fprintf(file, "NOT_NEGATIVE:\n");
    fprintf(file, "XOR DX, DX\n");
    fprintf(file, "DIV BX\n");
    fprintf(file, "PUSH DX\n");
    fprintf(file, "INC CX\n");
    fprintf(file, "CMP AX, 0\n");
    fprintf(file, "JE END_DISPLAY_LOOP\n");
    fprintf(file, "JMP DISPLAY_LOOP\n");
    fprintf(file, "END_DISPLAY_LOOP:\n");
    fprintf(file, "CMP MINUS, 1\n");
    fprintf(file, "JNE NEXT_BIT\n");
    fprintf(file, "MOV AH, 2\n");
    fprintf(file, "MOV DL, '-'\n");
    fprintf(file, "INT 21H\n");
    fprintf(file, "NEXT_BIT:\n");
    fprintf(file, "FINISH_DISPLAY_LOOP:\n");
    fprintf(file, "POP DX\n");
    fprintf(file, "ADD DL, '0'\n");
    fprintf(file, "MOV AH, 2\n");
    fprintf(file, "INT 21H\n");
    fprintf(file, "LOOP FINISH_DISPLAY_LOOP\n");
    fprintf(file, "MOV MINUS, 0\n");
    fprintf(file, "MOV DL, 0DH\n");
    fprintf(file, "INT 21H\n");
    fprintf(file, "MOV DL, 0AH\n");
    fprintf(file, "INT 21H\n");
    fprintf(file, "RET\n");
    
    


    fprintf(file, "println_int ENDP\n");
}

void addGlobalVariable(char *name, FILE *file)
{
    freopen("mycode.asm", "r", file);
    FILE *tempFile = fopen("temp.txt", "w");
    char *line;
    size_t len = 0;
    ssize_t read;
    int i = 0;
    while ((read = getline(&line, &len, file)) != -1)
    {
        if (i == 3) {
            fprintf(tempFile, "%s DW ?\n", name);
        }
        fprintf(tempFile, "%s", line);
        i++;
    }
    freopen("mycode.asm", "w", file);
    freopen("temp.txt", "r", tempFile);
    while ((read = getline(&line, &len, tempFile)) != -1)
    {
        fprintf(file, "%s", line);
    }
    fclose(tempFile);
    remove("temp.txt");
    freopen("mycode.asm", "a", file);
}

void printToASM(string text, FILE *file)
{
    fprintf(file, "%s\n", (char*) text.c_str());
}

void writeFunctionExitLabel(string text, FILE *file)
{
    fprintf(file, "%s_exit:\n", (char*) text.c_str());
}

string getFunctionExitLabel(string func)
{
    string str = func + "_exit";
    return str;
}

string collectExprStmt(FILE *file)
{
    freopen("mycode.asm", "r", file);
    char *line;
    size_t len = 0;
    ssize_t read;
    int i = 0;
    while ((read = getline(&line, &len, file)) != -1)
    {
        if (!strcmp(line, "expr_marker\n"))
            break;

        i++;
    }
    string str; 
    while ((read = getline(&line, &len, file)) != -1)
    {
        str += line;
    }
    freopen("mycode.asm", "r", file);
    FILE *tempFile = fopen("temp1.txt", "w");
    for (int j = 0; j < i; j++)
    {
        getline(&line, &len, file);
        fprintf(tempFile, "%s", line);
    }
    freopen("mycode.asm", "w", file);
    freopen("temp1.txt", "r", tempFile);
    while ((read = getline(&line, &len, tempFile)) != -1)
    {
         fprintf(file, "%s", line);
    }
    
    fclose(tempFile);
    remove("temp1.txt");
    cout << str;
    freopen("mycode.asm", "a", file);
    return str;
}
