%option yylineno noyywrap

%{
     #include <stdio.h>
     #include <stdlib.h>
     #include <string.h>
     #include <string>
     #include <ctype.h>
     #include "1805068_SymbolTable.h"
     #include "1805068_parser.tab.h"

     FILE *tokens;
     string *name, *type, s;
     string slcomment;

     int totalErrors = 0;
     int slcommentLineNo;
     int strLineNo;
     extern YYSTYPE yylval;
     extern FILE* logFile;
     extern FILE* errorFile;
     extern int errorCount;
     extern void logError(FILE *logFile, FILE *errorFile, int yylineno, string info);

     SymbolTable symbolTable(7);

     char *comment;

     string initializeSLComment() {
         return "//"; 
     }

     char *toUpperCase(char *str) {
         char *current = (char*) malloc(strlen(str)+1);
         strcpy(current, str);
         int i = 0;
         while (*(current+i)) {
            *(current+i) = toupper(*(current+i));
            i++;
         }
         return current;
     }

     char* returnEscapedChar(char *yytext)
     {
        char *final = (char*) malloc(4);
        final[0] = '\'', final[2] = '\''; final[3] = '\0';
        final[1] = *(yytext+1);
        char str = *(yytext+1);
        if (str == '\\') {
            switch (*(yytext + 2)) {
                case 't':
                    final[1] = '\t';
                    break;
                case '0':
                    final[1] = '\0';
                    break;
                case 'n':
                    final[1] = '\n';
                    break;
                case 'b':
                    final[1] = '\b';
                    break;
                case 'r':
                    final[1] = '\r';
                    break;
                case 'a':
                    final[1] = '\a';
                    break;
                case '\'':
                    final[1] = '\'';
                    break;
                case 'v':
                    final[1] = '\v';
                    break;
                case '\\':
                    final[1] = '\\';
                    break;
                case 'f':
                    final[1] = '\f';
                    break;
                default:
                    break;
            }
        }
        return final;
     }

     char* replaceWord(const char* s, const char* oldWord,
                  const char* newWord) {
        char* result;
        int i, cnt = 0;
        int newWlen = strlen(newWord);
        int oldWlen = strlen(oldWord);
    
        for (i = 0; s[i] != '\0'; i++) {
            if (strstr(&s[i], oldWord) == &s[i]) {
                cnt++;
    
                i += oldWlen - 1;
            }
        }
        result = (char*)malloc(i + cnt * (newWlen - oldWlen) + 1);
    
        i = 0;
        while (*s) {
            if (strstr(s, oldWord) == s) {
                strcpy(&result[i], newWord);
                i += newWlen;
                s += oldWlen;
            }
            else
                result[i++] = *s++;
        }
    
        result[i] = '\0';
        return result;
    }

    char* replaceBackspace(char* yytext) {
        char *p = strstr(yytext, "\\b");
        char *q;
        while (p != NULL && p != yytext) {
            q = p+1;
            p = p-1;
            while(*(p+1)) {
                *p = *(p+1);
                p = p+1;
            }
            *p = '\0';
            p = strstr(q, "\\b");
        }
        yytext = replaceWord(yytext, "\\b", "");
        return yytext;
    }

    char* replaceEscapes(char* yytext) {
        yytext = replaceWord(yytext, "\\t", "\t");
        yytext = replaceWord(yytext, "\\\r\n", "");
        yytext = replaceWord(yytext, "\\\n", "");
        yytext = replaceWord(yytext, "\\n", "\n");
        yytext = replaceBackspace(yytext);
        yytext = replaceWord(yytext, "\\\\", "\\");
        yytext = replaceWord(yytext, "\\\"", "\"");
        return yytext;
    }


    void logResult(const char *type, char *lexeme) {
        cout << "Line no " << yylineno << ": Token <" << type << "> Lexeme " << lexeme << " found ";
        if (type == "CONST_CHAR") {
            cout << "-->" << " <CONST_CHAR, " << returnEscapedChar(lexeme)[1] << ">";
        } else if (type == "STRING") {
            cout << "-->" << " <STRING, " << replaceEscapes(lexeme) << ">";
        }
        cout << "\n\n";
    }

    void logResult(const char *type, string lexeme, int lineNo) {
        cout << "Line no " << lineNo << ": Token <" << type << "> Lexeme " << lexeme << " found ";
        if (type == "STRING") {
            cout << "-->" << " <STRING, " << replaceEscapes((char*) lexeme.c_str()) << ">";
        }
        cout << "\n\n";
    }
    
%}

WHITESPACE  [ \t\f\r\v]+
LETTER [a-zA-Z]
DIGIT [0-9]
NEWLINE \r?\n
KEYWORD "if"|"else"|"while"|"break"|"char"|"double"|"return"|"case"|"continue"|"for"|"do"|"int"|"float"|"void"|"switch"|"default" 

%x COMMENT
%x SLCOMMENT
%x STR

%%

"if"                                                        {return IF;}
"else"                                                      {return ELSE;}
"for"                                                       {return FOR;}
"while"                                                     {return WHILE;}
"int"                                                       {return INT;}
"float"                                                     {return FLOAT;}
"double"                                                    {return DOUBLE;}
"char"                                                      {return CHAR;}
"return"                                                    {return RETURN;}
"void"                                                      {return VOID;}
"println"	                                                {return PRINTLN;}

{DIGIT}+                                                    { SymbolInfo *s = new SymbolInfo(yytext, (char *)"CONST_INT"); yylval.sym = s; return CONST_INT; }
({DIGIT}*\.?{DIGIT}+|{DIGIT}+\.)(E(\+|\-)?{DIGIT}+)?        { SymbolInfo *s = new SymbolInfo(yytext, (char *)"CONST_FLOAT"); yylval.sym = s; return CONST_FLOAT; }

'({LETTER}|{DIGIT})'|'\\[nt\\'afrbv0]'                     { SymbolInfo *s = new SymbolInfo(yytext, (char *)"CONST_CHAR"); yylval.sym = s; return CONST_CHAR; }
                                                                    

\+\+                            { SymbolInfo *s = new SymbolInfo(yytext, (char *)"INCOP"); yylval.sym = s; return INCOP; }
\-\-                            { SymbolInfo *s = new SymbolInfo(yytext, (char *)"INCOP"); yylval.sym = s; return DECOP; }
\+|\-                           { SymbolInfo *s = new SymbolInfo(yytext, (char *)"ADDOP"); yylval.sym = s; return ADDOP; }
"<"|"<="|">"|">="|"=="|"!="     { SymbolInfo *s = new SymbolInfo(yytext, (char *)"RELOP"); yylval.sym = s; return RELOP; }
"*"|"/"|"%"                     { SymbolInfo *s = new SymbolInfo(yytext, (char *)"MULOP"); yylval.sym = s; return MULOP; }
"="                             { return ASSIGNOP; }
"&&"|"||"                       { SymbolInfo *s = new SymbolInfo(yytext, (char *)"LOGICOP"); yylval.sym = s; return LOGICOP; }
!                               { return NOT; }
"("                             { return LPAREN; }
")"                             { return RPAREN; }
"{"                             { return LCURL; }
"}"                             { return RCURL; }
"["                             { return LTHIRD; }
"]"                             { return RTHIRD; }
","                             { return COMMA; }
";"                             { return SEMICOLON; } // NEXT UP: ID


({LETTER}|"_")({LETTER}|{DIGIT}|"_")* { SymbolInfo *s = new SymbolInfo(yytext, (char *)"ID"); yylval.sym = s; return ID; }

"/*"                                        BEGIN(COMMENT); slcomment = "/*"; slcommentLineNo = yylineno;
<COMMENT>(.*{NEWLINE})*.*\*\/               slcomment = slcomment + yytext; logResult("COMMENT", slcomment, slcommentLineNo); BEGIN(INITIAL);
<COMMENT>.                                  slcomment = slcomment + yytext;
<COMMENT><<EOF>>                            s = "Unterminated comment "; s += slcomment; s += yytext; logError(logFile, errorFile, slcommentLineNo, s); errorCount++; return 0;        
"//"                                        slcomment = yytext; BEGIN(SLCOMMENT); slcommentLineNo = yylineno; 
<SLCOMMENT>[^\n]*"\\"                       slcomment = slcomment + yytext + "\n";
<SLCOMMENT>[^\n]*                           slcomment = slcomment + yytext; logResult("COMMENT", slcomment, slcommentLineNo); BEGIN(INITIAL);
<SLCOMMENT><<EOF>>                          s = "Unterminated comment "; s += slcomment; s += yytext; logError(logFile, errorFile, yylineno, s); errorCount++; return 0;        
<SLCOMMENT>{NEWLINE}

      

"\""/\n                                     s = "\""; logError(logFile, errorFile, yylineno, s); errorCount++;      
"\""                                        BEGIN(STR);  strLineNo = yylineno;
<STR>"\""                                   BEGIN(INITIAL);      
<STR>((([^\"\n]*[^\\\"\n])*(\\\\)*(\\\")*)*\\{NEWLINE})*(([^\"\n]*[^\\\"\n])*(\\\\)*(\\\")*)*/\"                { SymbolInfo *s = new SymbolInfo(replaceEscapes(yytext), (char *)"STRING"); yylval.sym = s; return STRING; } // fprintf(tokens, "<STRING, \"%s\"> ", replaceEscapes(yytext));   s = "\""; s = (s + yytext) + "\""; logResult("STRING", s, strLineNo);
<STR>((([^\"\n]*[^\\\"\n])*(\\\\)*(\\\")*)*\\{NEWLINE})*(([^\"\n]*[^\\\"\n])*(\\\\)*(\\\")*)*{WHITESPACE}?$     s = "Unterminated string "; s += yytext; s += yytext; logError(logFile, errorFile, strLineNo, s); errorCount++; BEGIN(INITIAL);


({DIGIT}*\.({DIGIT}*\.{DIGIT}*)+)                                      s = "Too many decimal points "; s += yytext; logError(logFile, errorFile, yylineno, s); errorCount++;      
({DIGIT}*\.?{DIGIT}+|{DIGIT}+\.)(E(\+|\-)?({DIGIT}*\.{DIGIT}*)+)?      s = "Ill formed number "; s += yytext; logError(logFile, errorFile, yylineno, s); errorCount++;
{DIGIT}+{LETTER}+({LETTER}|{DIGIT}|"_")*                               s = "Invalid prefix on ID or invalid suffix on number "; s += yytext; logError(logFile, errorFile, yylineno, s); errorCount++;      
'\\*({LETTER}|{DIGIT}|{WHITESPACE}){2,}'                               s = "Multi character constant error "; s += yytext; logError(logFile, errorFile, yylineno, s); errorCount++;      
'\\'|'[^\\^\n^']*                                                      s = "Unterminated character " + s += yytext; logError(logFile, errorFile, yylineno, s); errorCount++;      
''                                                                     s = "Empty character constant error "; s += yytext; logError(logFile, errorFile, yylineno, s); errorCount++;


{NEWLINE}       
{WHITESPACE}    
.                                                                      s = "Unrecognized character "; s+= yytext; logError(logFile, errorFile, yylineno, s); errorCount++;

%%