%{
#	include <iostream>
#	include <cstdlib>
#	include <cstring>
#	include <cmath>
#	include "1805068_SymbolTable.h"
#	include "Assembly.h"
#	include "util.h"
#	include <string>
#	include <regex>
#include 	<stack>
using namespace std;

int yyparse(void);
int yylex(void);

extern int yylineno;
extern FILE *yyin;
int errorCount = 0;

SymbolTable *table;

FILE *logFile;
FILE *errorFile;
FILE *inputFile;
FILE *codeFile;
FILE *optimizedFile;

string str;
string vartype;
string program = "";
string statementsStr = "";
string returnType;

int returnLineNo;

// ASM  Variables
int funcVariableCount = 0;
int funcParameterCount = 0;
int addOrSub = 0;
SymbolInfo *currentFunction;
bool inFactorArgList = false;
bool inForLoopThird = false;
int labelCount = 0;
stack<string> ifElseLabelStack;
stack<string> forThirdStack;
stack<string> forLabelStack;
stack<string> forLabelStack2;
string logicOpLabel1, logicOpLabel2, logicOpLabel3;
string ifLabel1, ifLabel2, ifLabel3;
string forLabel1, forLabel2, forLabel3, forExprStmt;
string whileLabel1, whileLabel2;
stack<string> whileLabelStack, whileLabelStack2;
stack<string> functionArgumentASMStack;
string simpleExpStr  = "";
string forThirdStr = "";


void yyerror(char *s)
{
	fprintf(logFile, "Error at line %d: %s\n\n", yylineno, s);
	fprintf(errorFile, "Error at line %d: %s\n\n", yylineno, s);
	errorCount++;
}

string newLabel()
{
	return "label_" + to_string(labelCount++);
}
%}

%token IF ELSE FOR WHILE ID LPAREN RPAREN SEMICOLON COMMA LCURL RCURL INT FLOAT VOID LTHIRD CONST_INT RTHIRD PRINTLN RETURN ASSIGNOP LOGICOP
%token RELOP MULOP ADDOP CONST_FLOAT NOT INCOP DECOP DOUBLE CHAR MAIN CONST_CHAR STRING UNRECOG

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%union {
	SymbolInfo *sym;
	char *name;
}

%type <sym> ID ADDOP CONST_INT CONST_FLOAT MULOP RELOP LOGICOP 
%type <sym> unary_expression factor term simple_expression rel_expression logic_expression expression variable arguments argument_list
%type <name> type_specifier declaration_list unit program var_declaration func_declaration parameter_list statement compound_statement expression_statement start
%type <name> statements func_definition dummy  
%%

start : { initializeASMFile(codeFile);} program
	{
		//write your code in this block in all the similar blocks below
		$$ = $2;
		logData(logFile, yylineno, "start : program", "");
		writePrintFunction(codeFile);
		endASMFile(codeFile);
	}
	;

program : program unit 				{
										program += "\n";
										program += $2;
										$$ = new char [program.size() + 1];
										std::strcpy($$, program.c_str());
										logData(logFile, yylineno, "program : program unit", $$);
									}
	| unit							{
										program += $1;
										$$ = new char [program.size() + 1];
										std::strcpy($$, program.c_str());
										logData(logFile, yylineno, "program : unit", $$);
									}
	;
	
unit : var_declaration				{
										$$ = $1;
										logData(logFile, yylineno, "unit : var_declaration", $$);

									}	
     | func_declaration				{ 
		 								$$ = $1;
										logData(logFile, yylineno, "unit : func_declaration", $$);
									}
     | func_definition				{ 
		 								$$ = $1;
										logData(logFile, yylineno, "unit : func_definition", $$);
									}
     ;
     
func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON
														{
															string type = $1, name = $2->name;
															SymbolInfo *current = table->lookUp(name);

															if (current == NULL)
															{
																// not declared
																vector<Parameter> declaredParamList = getParamList($4);
																SymbolInfo symbolInfo;
																symbolInfo.setName(name);
																symbolInfo.setType(type);
																symbolInfo.setDefined(false);
																symbolInfo.setFunc(true);
																// now add parameters to the function by opening a new scope
																table->enterScope();
																// if possible to enter symbol in ST, then add the parameter, otherwise show error
																// but if parameter name = " ", then can be added no worries
																for (int i = 0; i < declaredParamList.size(); i++)
																{
																	if (declaredParamList[i].name != " ")
																	{
																		if (!table->insert(declaredParamList[i].name, declaredParamList[i].type))
																		{
																		errorCount++;
																		logError(logFile, errorFile, yylineno, "Redeclaration of parameter");
																		}
																	}
																}
																table->exitScope();
																symbolInfo.setParams(declaredParamList);
																table->insert(symbolInfo);
															}
															else
															{
																// function already declared, redeclaration
																errorCount++;
																logError(logFile, errorFile, yylineno, "Redeclaration of function");
															}

															str = $1; str += " "; str += ($2->name); str += "("; str += $4; str += ");";
															$$ = new char [str.size() + 1];
															std::strcpy($$, str.c_str());
															logData(logFile, yylineno, "func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON", $$);
														}
		| 	type_specifier ID LPAREN parameter_list RPAREN error SEMICOLON
														{
															string type = $1, name = $2->name;
															SymbolInfo *current = table->lookUp(name);

															if (current == NULL)
															{
																// not declared
																vector<Parameter> declaredParamList = getParamList($4);
																SymbolInfo symbolInfo;
																symbolInfo.setName(name);
																symbolInfo.setType(type);
																symbolInfo.setDefined(false);
																symbolInfo.setFunc(true);
																// now add parameters to the function by opening a new scope
																table->enterScope();
																// if possible to enter symbol in ST, then add the parameter, otherwise show error
																// but if parameter name = " ", then can be added no worries
																for (int i = 0; i < declaredParamList.size(); i++)
																{
																	if (declaredParamList[i].name != " ")
																	{
																		if (!table->insert(declaredParamList[i].name, declaredParamList[i].type))
																		{
																		errorCount++;
																		logError(logFile, errorFile, yylineno, "Redeclaration of parameter");
																		}
																	}
																}
																table->exitScope();
																symbolInfo.setParams(declaredParamList);
																table->insert(symbolInfo);
															}
															else
															{
																// function already declared, redeclaration
																errorCount++;
																logError(logFile, errorFile, yylineno, "Redeclaration of function");
															}

															str = $1; str += " "; str += ($2->name); str += "("; str += $4; str += ");";
															$$ = new char [str.size() + 1];
															std::strcpy($$, str.c_str());
															logData(logFile, yylineno, "func_declaration : type_specifier ID LPAREN parameter_list RPAREN", $$);
														}

		| type_specifier ID LPAREN RPAREN SEMICOLON		{
															string type = $1, name = $2->name;
															SymbolInfo *current = table->lookUp(name);
															
															if (current == NULL) {

																// not declared

																vector<Parameter> parameters;
																SymbolInfo symbolInfo;
																symbolInfo.setName(name);
																symbolInfo.setParams(parameters);
																symbolInfo.setType(type);
																symbolInfo.setDefined(false);
																symbolInfo.setFunc(true);

																// enter and exit scope
																table->enterScope();
																table->exitScope();

																table->insert(symbolInfo);

															}
															else 
															{
																// enter and exit scope
																table->enterScope();
																table->exitScope();
																
																// previously declared as function or otherwise
																errorCount++;
																logError(logFile, errorFile, yylineno, "Previous declaration");
															}

															str = $1; str += " "; str += ($2->name); str += "();";
															$$ = new char [str.size() + 1];
															std::strcpy($$, str.c_str());
															logData(logFile, yylineno, "func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON", $$);
														}
		| type_specifier ID LPAREN RPAREN error SEMICOLON {
															string type = $1, name = $2->name;
															SymbolInfo *current = table->lookUp(name);
															
															if (current == NULL) {

																// not declared

																vector<Parameter> parameters;
																SymbolInfo symbolInfo;
																symbolInfo.setName(name);
																symbolInfo.setParams(parameters);
																symbolInfo.setType(type);
																symbolInfo.setDefined(false);
																symbolInfo.setFunc(true);

																// enter and exit scope
																table->enterScope();
																table->exitScope();

																table->insert(symbolInfo);

															}
															else 
															{
																// enter and exit scope
																table->enterScope();
																table->exitScope();
																
																// previously declared as function or otherwise
																errorCount++;
																logError(logFile, errorFile, yylineno, "Previous declaration");
															}

															str = $1; str += " "; str += ($2->name); str += "();";
															$$ = new char [str.size() + 1];
															std::strcpy($$, str.c_str());
															logData(logFile, yylineno, "func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON", $$);
														}
		;
		 
func_definition : type_specifier ID LPAREN parameter_list RPAREN 
														{
															currentFunction = $2;
															string type = $1;
															string name = $2->name;
															returnType = "";
															string ASMText = name + " PROC";
															printToASM(ASMText, codeFile);
															printToASM("PUSH BP", codeFile);
															printToASM("MOV BP, SP", codeFile);
															vector<Parameter> paramList = getParamList($4);
													
															SymbolInfo *current = table->lookUp(name);
															if (current == NULL)
															{
																// does not exist
																SymbolInfo functionInfo;
																functionInfo.setName(name);
																functionInfo.setType(type);
																functionInfo.setDefined(true);
																functionInfo.setFunc(true);
																functionInfo.setParams(paramList);
																table->insert(functionInfo);

																table->enterScope();

																for (int i = 0; i < paramList.size(); i++)
																{
																	funcParameterCount++;
																	if (paramList[i].name == " ")
																	{
																		errorCount++;
																		string errorStr = to_string(i+1) + "th parameter's name not given in function definition of " + name;
																		logError(logFile, errorFile, yylineno, errorStr);
																	}
																	else
																	{
																		SymbolInfo parameterInfo;
																		parameterInfo.setName(paramList[i].name);
																		parameterInfo.setType(paramList[i].type);
																		parameterInfo.setOffset(2*(funcParameterCount+1));
																		if (!(table->insert(parameterInfo)))
																		{
																			errorCount++;
																			logError(logFile, errorFile, yylineno, "Multiple declaration of " + paramList[i].name + " in parameter");
																		}
																	}
																	
																}
															}
															else
															{
																bool isConsistent = true;
																// declared, check for function or not
																if (!current->isFunc() || current->isDefined())
																{
																	errorCount++;
																	logError(logFile, errorFile, yylineno, "Multiple declaration of " + name);
																	isConsistent = false;
																}

																// function declared, not defined
																// time to check whether declaration consistent with definition 
																// check return types

																string declaredRetType = current->getType();
																if (type != declaredRetType && isConsistent)
																{
																	isConsistent = false;
																	errorCount++;
																	logError(logFile, errorFile, yylineno, "Return type mismatch with function declaration in function " + name);
																}

																// if declaration parameter number and definition number do not match, show error

																int declaredParameterNumber = current->getParamList().size();
																int definedParameterNumber = paramList.size();

																if (declaredParameterNumber != definedParameterNumber && isConsistent)
																{
																	isConsistent = false;
																	errorCount++;
																	logError(logFile, errorFile, yylineno, "Total number of arguments mismatch with declaration in function " + name);
																}
																else
																{
																	// parameter numbers match at this point
																	// check for parameter sequencing: if parameter numbers match and they are not 0
																	vector<Parameter> declaredParamList = current->getParamList();
																	if (declaredParameterNumber != 0)
																	{
																		for (int i = 0; i < declaredParameterNumber; i++)
																		{
																			string declaredType = declaredParamList[i].type;
																			string definedType = paramList[i].type;
																			if (declaredType != definedType)
																			{
																				isConsistent = false;
																				errorCount++;
																				logError(logFile, errorFile, yylineno, "Parameter sequence incorrect");
																			}
																		}
																	}
																}

																// table->printAllScopeTables(logFile);
																table->remove(name);
																SymbolInfo newSymbolInfo;
																newSymbolInfo.setName(name);
																newSymbolInfo.setType(type);
																newSymbolInfo.setParams(paramList);
																newSymbolInfo.setDefined(true);
																newSymbolInfo.setFunc(true);

																table->insert(newSymbolInfo);

																// now open a new scope and insert the parameters individually
																table->enterScope();

																for (int i = 0; i < paramList.size(); i++)
																{
																	if(!(table->insert(paramList[i].name, paramList[i].type)))
																	{
																		errorCount++;
																		logError(logFile, errorFile, yylineno, "Redeclaration of parameter");
																	}
																}																		
															}
														}
														compound_statement 			{
																						// check for return type
																						string compoundStatement = $7;
																						if ($1 == "void")
																						{
																							if (returnType != "")
																							{
																								errorCount++;
																								logError(logFile, errorFile, returnLineNo, "Void function returns something");
																							}
																						}

																						else
																						{
																							if (returnType != $1)
																							{
																								if (returnType == "")
																								{
																									errorCount++;
																									
																									string errorStr = "Function of type "; errorStr += $1; errorStr += " does not return a value";
																									logError(logFile, errorFile, yylineno, errorStr);
																								}
																								else
																								{
			
																									if (!($1 == "float" && returnType == "int"))
																									{
																										errorCount++;
																										logError(logFile, errorFile, returnLineNo, "Return type in body mismatched with definition");
																									}
																								}
																							}
																						}
																						if (funcVariableCount > 0)
																						{
																							// add stack pointer by 2*funcVariableCount (DW)
																							string temp = "ADD SP, ";
																							temp += to_string(2*funcVariableCount);
																							printToASM(temp, codeFile);
																						}
																						writeFunctionExitLabel($2->name, codeFile);
																						printToASM("POP BP", codeFile);
																						char ASMCode[10];
																						sprintf(ASMCode, "RET %d", 2*funcParameterCount);
																						printToASM(ASMCode, codeFile);
																						string ASMText = $2->name + " ENDP";
																						printToASM(ASMText, codeFile);
																						str = $1; str += " "; str += $2->name; str += "(";
																						str += $4; str += ")"; str += $7;
																						$$ = new char [str.size() + 1];
																						std::strcpy($$, str.c_str());
																						logData(logFile, yylineno, "func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement", $$);
																						funcVariableCount = 0;
																						funcParameterCount = 0;
																					}
		| type_specifier ID LPAREN RPAREN 
																					{
																						currentFunction = $2;
																						string type = $1;
																						string name = $2->name;	
																						returnType = "";
																						string ASMText = name + " PROC";
																						printToASM(ASMText, codeFile);
																						printToASM("PUSH BP", codeFile);
																						printToASM("MOV BP, SP", codeFile);
																						SymbolInfo *current = table->lookUp(name);

																						if (name == "main")
																						{
																							printToASM("MOV AX, @DATA", codeFile);
																							printToASM("MOV DS, AX", codeFile);
																						}

																						if (current == NULL)
																						{
																							// does not exist at all
																							SymbolInfo symbolInfo;
																							symbolInfo.setFunc(true);
																							symbolInfo.setDefined(true);
																							symbolInfo.setName(name);
																							symbolInfo.setType(type);
																							
																							table->insert(symbolInfo);
																						}
																						else
																						{
																							// has been declared at least	
																							// check whether it is a function
																							if (current->isFunc())
																							{
																								// check whether it has been previously defined
																								if (current->isDefined())
																								{
																									errorCount++;
																									string errorStr = current->name + " has previously been defined";
																									logError(logFile, errorFile, yylineno, errorStr);
																								}
																								else
																								{
																									// function has been declared but not defined
																									// this is good
																									// now to check whether function definition is consistent with declaration

																									bool isConsistent = true;

																									// check whether parameter number is not zero

																									int declaredParamNumber = current->getParamList().size();
																									if (declaredParamNumber != 0)
																									{
																										isConsistent = false;
																										errorCount++;
																										logError(logFile, errorFile, yylineno, "Inconsistent number of parameters with declaration");
																									}

																									// check whether function return types match

																									string declaredRetType = current->getType();
																									if (declaredRetType != type)
																									{
																										isConsistent = false;
																										errorCount++;
																										logError(logFile, errorFile, yylineno, "Inconsistent return types");

																									}

																									// since no parameters, sequence checking is not needed

																									if (isConsistent)
																									{
																										// remove the original declaration and now add the definition
																										table->remove(name);

																										vector<Parameter> params;

																										SymbolInfo symbolInfo;
																										symbolInfo.setFunc(true);
																										symbolInfo.setDefined(true);
																										symbolInfo.setName(name);
																										symbolInfo.setType(type);
																										symbolInfo.setParams(params);

																										table->insert(symbolInfo);
																									}
																								}
																							}
																							else
																							{
																								// not a function, so log the error
																								string errorStr = current->name;
																								errorStr += " is not a function";
																								errorCount++;
																								logError(logFile, errorFile, yylineno, errorStr);
																							}
																						
																						}
																						table->enterScope();										
																					}
											compound_statement						{
																						if ($1 == "void")
																						{
																							if (returnType != "")
																							{
																								errorCount++;
																								logError(logFile, errorFile, returnLineNo, "Void function returns something");
																							}
																						}

																						else
																						{
																							if (returnType != $1)
																							{
																								if (returnType == "")
																								{
																									errorCount++;
																									string errorStr = "Function of type "; errorStr += $1; errorStr += " does not return a value";
																									logError(logFile, errorFile, yylineno, errorStr);
																								}
																								else
																								{
																									if (!($1 == "float" && returnType == "int"))
																									{
																										errorCount++;
																										logError(logFile, errorFile, returnLineNo, "Return type in body mismatched with definition");
																									}
																								}
																							}		
																						}

																						str = $1; str += " "; str += $2->name; str+="()";
																						str += $6;
																						if (funcVariableCount > 0)
																						{
																							// add stack pointer by 2*funcVariableCount (DW)
																							string temp = "ADD SP, ";
																							temp += to_string(2*funcVariableCount);
																							printToASM(temp, codeFile);
																						}
																						writeFunctionExitLabel($2->name, codeFile);
																						printToASM("POP BP", codeFile);
																						if ($2->name == "main")
																						{
																							printToASM("MOV AH, 4CH", codeFile);
																							printToASM("INT 21H", codeFile);
																						}
																						printToASM("RET 0", codeFile);
																						string ASMText = $2->name + " ENDP";
																						printToASM(ASMText, codeFile);
																						$$ = new char [str.size() + 1];
																						std::strcpy($$, str.c_str());
																						logData(logFile, yylineno, "func_definition : type_specifier ID LPAREN RPAREN compound_statement", $$);
																						funcVariableCount = 0;
																						funcParameterCount = 0;
																					}
 		;				


parameter_list  : parameter_list COMMA type_specifier ID	{
																str = $1; str += ","; str += $3; str += " "; str += $4->name;
																$$ = new char [str.size() + 1];
																std::strcpy($$, str.c_str());
																logData(logFile, yylineno, "parameter_list : parameter_list COMMA type_specifier ID", $$);
															}
		| parameter_list COMMA type_specifier				{
																str = $1; str += ","; str += $3;
																$$ = new char [str.size() + 1];
																std::strcpy($$, str.c_str());
																logData(logFile, yylineno, "parameter_list : parameter_list COMMA type_specifier", $$);
															}
 		| type_specifier ID									{
																str = $1; str += " "; str += $2->name;
																$$ = new char [str.size() + 1];
																std::strcpy($$, str.c_str());
																logData(logFile, yylineno, "parameter_list : type_specifier ID", $$);
															}
		| type_specifier									{
																str = $1;
																$$ = new char[str.size() + 1];
																std::strcpy($$, str.c_str());
																logData(logFile, yylineno, "parameter_list : type_specifier", $$);
															}
		| type_specifier error								{
																yyclearin;
																yyerrok;
																str = $1;
																$$ = new char[str.size() + 1];
																std::strcpy($$, str.c_str());
																logData(logFile, yylineno, "parameter_list : type_specifier", $$);
															}									
 		;

 		
compound_statement : LCURL statements RCURL					{
																str = "{\n"; str += $2; str += "\n}";
																$$ = new char [str.size() + 1];
																std::strcpy($$, str.c_str());
																logData(logFile, yylineno, "compound_statement : LCURL statements RCURL", $$);
																table->printAllScopeTables(logFile);
																table->exitScope();
															}
			| LCURL func_definition 						{
																errorCount++;
																logError(logFile, errorFile, yylineno, "Invalid scoping of function");
			}	RCURL										{
																str = "{\n"; str += "\n}";
																$$ = new char [str.size() + 1];
																std::strcpy($$, str.c_str());
																logData(logFile, yylineno, "compound_statement : LCURL RCURL", $$);
																table->printAllScopeTables(logFile);
																table->exitScope();
															}
			| LCURL func_definition 						{
																errorCount++;
																logError(logFile, errorFile, yylineno, "Invalid scoping of function");
			} statements RCURL								{
																str = "{\n"; str += $4; str += "\n}";
																$$ = new char [str.size() + 1];
																std::strcpy($$, str.c_str());
																logData(logFile, yylineno, "compound_statement : LCURL statements RCURL", $$);
																table->printAllScopeTables(logFile);
																table->exitScope();
															}			
 		    | LCURL RCURL									{
				 												$$ = "{}";
																logData(logFile, yylineno, "compound_statement : LCURL RCURL", $$);
																table->printAllScopeTables(logFile);
																table->exitScope();
			 												}
 		    ;
 		    
var_declaration : type_specifier declaration_list SEMICOLON			{	 	
																		string varType = $1;
																		string varName = $2;
																		// check for void variable type

																		if (varType == "void")
																		{
																			errorCount++;
																			logError(logFile, errorFile, yylineno, "Variable type cannot be void");
																		}
																		else
																		{
																			vector<string> strings = split(varName, ',');
																			for (string s: strings) {
																				SymbolInfo symbolInfo;
																				
																				if (isArray(s)) {
																					int size = getArraySize(s);
																					string name = getArrayName(s);
																					symbolInfo.setAsArray(name, (varType + "*"), size);
																					funcVariableCount += size;
																					symbolInfo.setOffset(funcVariableCount*-2);
																					
																					char ASMCode[15];
																					sprintf(ASMCode, "SUB SP, %d", size*2);
																					printToASM(ASMCode, codeFile);
																					
																				}
																				else {
																					symbolInfo.setName(s);
																					symbolInfo.setType(varType);
																					
																					// if the variable is in global scope, add to global variables
																					if (regex_match(table->getScopeID(), regex("\\d+"))) {
																						addGlobalVariable((char*) s.c_str(), codeFile);
																						symbolInfo.setGlobal(true);
																					}
																					else {
																						// add as local variable
																						funcVariableCount++;
																						symbolInfo.setOffset(funcVariableCount*-2);
																						// printf("C %d", symbolInfo.getOffset());
																						printToASM("SUB SP, 2", codeFile);
																					}
																				}

																				if (!table->insert(symbolInfo))
																				{
																					// multiple declaration
																					errorCount++;
																					string errorStr = "Multiple declaration of " + symbolInfo.getName();
																					logError(logFile, errorFile, yylineno, errorStr);
																				}
																			}
																		}
																		string str2 = $2;
																		str = $1; str += " "; str = str + str2; str+= ";";
																		$$ = new char [str.size() + 1];
																		std::strcpy($$, str.c_str());
																		logData(logFile, yylineno, "var_declaration : type_specifier declaration_list SEMICOLON", $$);
																	}
			| type_specifier declaration_list error SEMICOLON		{	 	
																		string varType = $1;
																		string varName = $2;
																		// check for void variable type

																		if (varType == "void")
																		{
																			errorCount++;
																			logError(logFile, errorFile, yylineno, "Variable type cannot be void");
																		}
																		else
																		{
																			vector<string> strings = split(varName, ',');
																			for (string s: strings) {
																				SymbolInfo symbolInfo;
																				if (isArray(s)) {
																					int size = getArraySize(s);
																					string name = getArrayName(s);
																					symbolInfo.setAsArray(name, (varType + "*"), size);
																				}
																				else {
																					symbolInfo.setName(s);
																					symbolInfo.setType(varType);
																				}

																				if (!table->insert(symbolInfo))
																				{
																					// multiple declaration
																					errorCount++;
																					string errorStr = "Multiple declaration of " + symbolInfo.getName();
																					logError(logFile, errorFile, yylineno, errorStr);
																				}
																			}
																		}
																		string str2 = $2;
																		str = $1; str += " "; str = str + str2; str+= ";";
																		$$ = new char [str.size() + 1];
																		std::strcpy($$, str.c_str());
																		logData(logFile, yylineno, "var_declaration : type_specifier declaration_list SEMICOLON", $$);
																	}
 		 ;
 		 
type_specifier	: INT				{ $$ = (char *)"int"; logData(logFile, yylineno, "type_specifier : INT", $$); }
 		| FLOAT						{ $$ = (char *)"float"; logData(logFile, yylineno, "type_specifier : FLOAT", $$); }
 		| VOID						{ $$ = (char *)"void"; logData(logFile, yylineno, "type_specifier : VOID", $$); }
 		;
 		
declaration_list : declaration_list COMMA ID					{ 
																	str = $1; str += ","; str += $3->name;
																	$$ = new char [str.size() + 1];
																	std::strcpy($$, str.c_str());
																	logData(logFile, yylineno, "declaration_list : declaration_list COMMA ID", $$);
																}
		  | declaration_list error COMMA ID						{ 
																	str = $1; str += ","; str += $4->name;
																	$$ = new char [str.size() + 1];
																	std::strcpy($$, str.c_str());
																	logData(logFile, yylineno, "declaration_list : declaration_list COMMA ID", $$);
																}
 		  | declaration_list COMMA ID LTHIRD CONST_INT RTHIRD	{
			   														str = $1; str += ","; str += $3->name; str += "["; str += $5->name; str += "]";
																	$$ = new char [str.size() + 1];
																	std::strcpy($$, str.c_str());
																	logData(logFile, yylineno, "declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD", $$);
		   														}
 		  | ID													{
			   														$$ = new char[$1->name.size() + 1];
																	std::strcpy($$, $1->name.c_str());
																	logData(logFile, yylineno, "declaration_list : ID", $$);
																}										
 		  | ID LTHIRD CONST_INT RTHIRD							{ 
			   														str = $1->name; str += "["; str += $3->name; str += "]";
																	$$ = new char[str.size() + 1];
																	std::strcpy($$, str.c_str());
																	logData(logFile, yylineno, "declaration_list : ID LTHIRD CONST_INT RTHIRD", $$);
		   														}										
 		  ;
 		  
statements : statement											{
																	str = $1; 
																	$$ = new char[str.size() + 1];
																	std::strcpy($$, str.c_str());
																	logData(logFile, yylineno, "statements : statement", $$);
																}																
	   | statements statement									{
		   															str = $1;
																	str += "\n"; str += $2; 
																	$$ = new char[str.size() + 1];
																	std::strcpy($$, str.c_str());
																	logData(logFile, yylineno, "statements : statements statement", $$);
	   															}
	   ;
	   
statement : var_declaration										{ 
																	str = $1;
																	$$ = new char[str.size() + 1];
																	std::strcpy($$, str.c_str());
																	logData(logFile, yylineno, "statement : var_declaration", $$);
 																}
	  | expression_statement									{ 
		  															$$ = $1;
																	logData(logFile, yylineno, "statement : expression_statement", $$);
	   															}
| { table->enterScope(); } compound_statement					{
																	str = $2;
																	$$ = new char[str.size() + 1];
																	std::strcpy($$, str.c_str());
																	logData(logFile, yylineno, "statement : compound_statement", $$);
																}
	  | FOR LPAREN expression_statement 
	  															{
																	forLabel1 = newLabel();
																	forLabelStack.push(forLabel1);
																	printToASM(forLabel1 + ":", codeFile);
																} 
	  expression_statement 										{
																	forLabel2 = newLabel();
																	forLabelStack2.push(forLabel2);
																	printToASM("JCXZ " + forLabel2, codeFile);
																	// place a marker
																	// printToASM("expr_marker", codeFile);
																	inForLoopThird = true;
	  															}
	  expression 												{
		  															forThirdStack.push(forThirdStr);
		  															forThirdStr = "";
		  															inForLoopThird = false;
		  															// collect everything from expr_marker into a string
																	// forExprStmt = collectExprStmt(codeFile);
	  															}
	  RPAREN statement	
	  															{
																	str = "for("; str += $3; str += $5; str += $7->name; str += ")"; str += $10;
																	$$ = new char[str.size() + 1];
																	std::strcpy($$, str.c_str());
																	logData(logFile, yylineno, "statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement", $$);
																	
																	printToASM(forThirdStack.top(), codeFile);
																	forThirdStack.pop();
																	printToASM("JMP " + forLabelStack.top(), codeFile);
																	forLabelStack.pop();
																	printToASM(forLabelStack2.top() + ":", codeFile);
																	forLabelStack2.pop();
																}
	  | IF LPAREN expression RPAREN dummy statement	%prec LOWER_THAN_ELSE
	  															{ 
																	str = "if ("; str += $3->name; str += ")"; str += $6;
																	$$ = new char[str.size() + 1];
																	std::strcpy($$, str.c_str());
																	logData(logFile, yylineno, "statement : IF LPAREN expression RPAREN statement", str);
																	string label = newLabel();
																	printToASM("JMP " + label, codeFile);
																	printToASM(ifLabel1 + ":", codeFile);
																	printToASM(label + ":", codeFile);
	   															}
	  | IF LPAREN expression RPAREN dummy statement ELSE 
	  															{
																	ifLabel2 = newLabel();
																	ifElseLabelStack.push(ifLabel2);
																	printToASM("JMP " + ifLabel2, codeFile);
																	printToASM(ifLabel1 + ":", codeFile);
																} 
	  statement	{
		  															str = "if ("; str += $3->name; str += ")"; str += $6; str += "\nelse\n"; str += $9;
																	$$ = new char[str.size() + 1];
																	std::strcpy($$, str.c_str());
																	logData(logFile, yylineno, "statement : IF LPAREN expression RPAREN statement ELSE statement", str);

																	printToASM(ifElseLabelStack.top() + ":", codeFile);
																	ifElseLabelStack.pop();
	  															}
	  | WHILE LPAREN											{
		  															whileLabel1 = newLabel();
																	whileLabelStack.push(whileLabel1);
																	printToASM(whileLabel1 + ":", codeFile);
	  															}
	    expression RPAREN 										{
																	whileLabel2 = newLabel();
																	whileLabelStack2.push(whileLabel2);
																	printToASM("JCXZ " + whileLabel2, codeFile);
																
																}
		statement												{
		  															str = "while ("; str += $4->name; str += ")"; str += $7;
																	$$ = new char[str.size() + 1];
																	std::strcpy($$, str.c_str());
																	logData(logFile, yylineno, "statement : WHILE LPAREN expression RPAREN statement", str);

																	printToASM("JMP " + whileLabelStack.top(), codeFile);
																	whileLabelStack.pop();
																	printToASM(whileLabelStack2.top() + ":", codeFile);
																	whileLabelStack2.pop();
	  															}
	  | PRINTLN LPAREN ID RPAREN SEMICOLON						{
		  															str = "println("; str += $3->name; str +=");";
																	$$ = new char[str.size() + 1];
																	std::strcpy($$, str.c_str());
																	SymbolInfo* current = table->lookUp($3->name);
																	if (current == NULL)
																	{
																		errorCount++;
																		logError(logFile, errorFile, yylineno, "Undeclared variable " + $3->name);
																	}
																	else
																	{
																		char ASMCode[20];
																		if (current->isGlobal()) {
																			sprintf(ASMCode, "MOV CX, %s", current->getName().c_str());	
																		}
																		else
																			sprintf(ASMCode, "MOV CX, %d[BP]", current->getOffset());
																		printToASM(ASMCode, codeFile);
																		printToASM("PUSH CX", codeFile);
																		printToASM("MOV AX, CX", codeFile);
																		if (current->getType() == "int")
																		{
																			printToASM("CALL println_int", codeFile);
																		}

																		else if (current->getType() == "float")
																		{
																			printToASM("CALL println_float", codeFile);
																		}
																	}
																	logData(logFile, yylineno, "statement : PRINTLN LPAREN ID RPAREN SEMICOLON", str);
	  															}
	| PRINTLN LPAREN ID RPAREN error SEMICOLON					{
		  															str = "printf("; str += $3->name; str +=");";
																	$$ = new char[str.size() + 1];
																	std::strcpy($$, str.c_str());
																	SymbolInfo* current = table->lookUp($3->name);
																	if (current == NULL)
																	{
																		errorCount++;
																		logError(logFile, errorFile, yylineno, "Undeclared variable " + $3->name);
																	}
																	logData(logFile, yylineno, "statement : PRINTLN LPAREN ID RPAREN SEMICOLON", str);
	  															}
	  | RETURN expression SEMICOLON								{
		  															returnType = $2->type;
																	returnLineNo = yylineno;
		  															str = $2->name; str = "return " + str; str += ";";
																	$$ = new char [str.size() + 1];
																	std::strcpy($$, str.c_str());
																	logData(logFile, yylineno, "statement : RETURN expression SEMICOLON", $$);
																	char ASMCode[20];
																	sprintf(ASMCode, "SUB SP, %d", -2*funcVariableCount);
																	printToASM(ASMCode, codeFile);
																	sprintf(ASMCode, "JMP %s_exit", (char*) currentFunction->getName().c_str());
																	printToASM(ASMCode, codeFile);
																	
	  															}
	| RETURN expression error SEMICOLON							{
		  															returnType = $2->type;
		  															str = $2->name; str = "return " + str; str += ";";
																	$$ = new char [str.size() + 1];
																	std::strcpy($$, str.c_str());
																	logData(logFile, yylineno, "statement : RETURN expression SEMICOLON", $$);
	  															}
	  ;

dummy: 															{
																	ifLabel1 = newLabel();
																	printToASM("JCXZ " + ifLabel1, codeFile);
																}
	  
expression_statement 	: SEMICOLON								{
																	$$ = ";";
																	logData(logFile, yylineno, "expression_statement : SEMICOLON", $$);
 																}
			| expression SEMICOLON 								{
																	str = $1->name; str += ";";
																	$$ = new char[str.size() + 1];
																	std::strcpy($$, str.c_str());
																	logData(logFile, yylineno, "expression_statement : expression SEMICOLON", $$);
																}
			| error expression SEMICOLON						{
																	str = $2->name; str += ";";
																	$$ = new char[str.size() + 1];
																	std::strcpy($$, str.c_str());
																	logData(logFile, yylineno, "expression_statement : expression SEMICOLON", $$);
																}
			| expression error SEMICOLON						{

																	str = $1->name; str += ";";
																	$$ = new char[str.size() + 1];
																	std::strcpy($$, str.c_str());
																	logData(logFile, yylineno, "expression_statement : expression SEMICOLON", $$);
																}
			;
	  
variable : ID 													{
																	// check whether variable has been declared
																	SymbolInfo *current = table->lookUp($1->name);
																	// cout << current->name << ": " << current->getType() << endl;
																	if (current == NULL)
																	{
																		// undeclared
																		errorCount++;
																		logError(logFile, errorFile, yylineno, "Undeclared variable " + $1->name);
																		$$ = new SymbolInfo($1->name, "ERROR");
																	}
																	else
																	{
																		$$ = new SymbolInfo(current->name, current->getType());
																		$$->setInTable(true);
																	} 
																	logData(logFile, yylineno, "variable : ID", $$->name);
																}
	 | ID LTHIRD expression RTHIRD 								{
		 															// check whether variable has been declared or not
																	SymbolInfo *current = table->lookUp($1->name);
																	if (current == NULL)
																	{
																		errorCount++;
																		string errorStr = "Undeclared variable " + $1->name;
																		logError(logFile, errorFile, yylineno, errorStr);
																		$$ = new SymbolInfo($1->name + "[" + $3->name + "]", "ERROR");
																	}
																	else
																	{
																		// variable has been declared, check whether expression is in correct format
																		// since this is supposed to be an array, must check whether it is array or not
																		if (!current->isArray())
																		{
																			errorCount++;
																			string errorStr = $1->name + " not an array";
																			logError(logFile, errorFile, yylineno, errorStr);
																			$$ = new SymbolInfo($1->name + "[" + $3->name + "]", "ERROR");
																		}
																		else
																		{
																			// it is an array, now check whether expression is an integer or not
																			if ($3->getType() != "int")
																			{
																				errorCount++;
																				logError(logFile, errorFile, yylineno, "Expression inside third brackets not an integer");
																			}
																			string name = $1->name + "[" + $3->name + "]";
																			$$ = new SymbolInfo(name, $3->getType());																		
																		}
																	}
																	logData(logFile, yylineno, "variable : ID LTHIRD expression RTHIRD", $$->name);
	  															}
	 ;
	 
 expression : logic_expression									{
																	$$ = $1;
																	logData(logFile, yylineno, "expression : logic_expression", $$->name);
																}
	   | variable ASSIGNOP 
	   {
		   															SymbolInfo *current = table->lookUp(getArrayName($1->name));
																	if (current->isArray())
																	{
																		printToASM("PUSH CX", codeFile);
																	}
	   }
	   logic_expression											{
		   															// check for type mismatch
																	// float = int is okay, int = float is not
																	// both sides same = ok

																	string leftType = $1->getType();
																	string rightType = $4->getType();

																	if (leftType == "void" || rightType == "void")
																	{
																		errorCount++;
																		logError(logFile, errorFile, yylineno, "Void function used in expression");
																	}

																	if (leftType != rightType)
																	{
																		if (leftType == "int" && (rightType == "float" || rightType == "CONST_FLOAT"))
																		{
																			// int is being assigned to float, type mismatch
																			errorCount++;
																			logError(logFile, errorFile, yylineno, "Type Mismatch");
																		}
																		// check for array mismatches
																		else if (leftType == "int*" || leftType == "float*")
																		{
																			errorCount++;
																			logError(logFile, errorFile, yylineno, "Type mismatch, " + $1->name + " is an array");
																		}
																		else if (rightType == "int*" || rightType == "float*")
																		{
																			errorCount++;
																			logError(logFile, errorFile, yylineno, "Type mismatch, " + $4->name + " is an array");
																		}
																	}

																	char ASMCode[10];
																	SymbolInfo *originalSymbolInfo = table->lookUp(getArrayName($1->getName()));
																	if (originalSymbolInfo->isArray())
																	{
																		printToASM("POP AX", codeFile);
																		printToASM("XCHG AX, CX", codeFile);
																		char ASMCode[10];
																		int index = getArraySize($1->name);
																		printToASM("PUSH BP", codeFile);
																		printToASM("SAL CX, 1", codeFile);
																		sprintf(ASMCode, "ADD CX, %d", originalSymbolInfo->getOffset());
																		printToASM(ASMCode, codeFile);
																		printToASM("ADD BP, CX", codeFile);
																		printToASM("MOV PTR WORD [BP], AX", codeFile);
																		printToASM("MOV CX, AX", codeFile);
																		printToASM("POP BP", codeFile);

																	}
																	else
																	{
																		// assuming CX holds the required result:
																		if (originalSymbolInfo->isGlobal()) {	
																			sprintf(ASMCode, "MOV %s, CX", originalSymbolInfo->getName().c_str());
																		}
																		else {
																			sprintf(ASMCode, "MOV %d[BP], CX", originalSymbolInfo->getOffset());
																		}
																		printToASM(ASMCode, codeFile);
																	}

		   															str = $1->name; str += "="; str += $4->name;
																	string retType = "expression";
																	$$ = new SymbolInfo(str, retType);
																	logData(logFile, yylineno, "expression : variable ASSIGNOP logic_expression", $$->name);
	   															}	
	   ;
			
logic_expression : rel_expression 								{
																	$$ = $1;
																	logData(logFile, yylineno, "logic_expression : rel_expression", $$->name);
																}
		 | rel_expression LOGICOP 
		 														{
																	string logicOp = $2->name;
																	logicOpLabel1 = newLabel();
																	if (logicOp == "&&")
																	{
																		printToASM("JCXZ " + logicOpLabel1, codeFile);
																	}
																	else
																	{
																		printToASM("CMP CX, 0", codeFile);
																		printToASM("JNZ " + logicOpLabel1, codeFile);
																	}
																}
		 rel_expression 										{
			 														str = $1->name; str += $2->name; str += $4->name;
																	$$ = new SymbolInfo(str, "int");
																	logData(logFile, yylineno, "logic_expression : rel_expression LOGICOP rel_expression", $$->name);

																	// ASM Code
																	printToASM(logicOpLabel1 + ":", codeFile);
		 														}
		 ;
			
rel_expression	: simple_expression 							{
																	$$ = $1;
																	logData(logFile, yylineno, "rel_expression : simple_expression", $$->name);
																}
		| simple_expression RELOP 
																{
																	printToASM("PUSH CX", codeFile);
																}
		simple_expression										{
																	str = $1->name; str += $2->name; str += $4->name;
																	$$ = new SymbolInfo(str, "int");
																	logData(logFile, yylineno, "rel_expression : simple_expression RELOP simple_expression", $$->name);

																	string label1 = newLabel();
																	string label2 = newLabel();
																	
																	// ASM Code
																	printToASM("POP AX", codeFile);
																	printToASM("CMP AX, CX", codeFile);

																	string relOp = $2->name;

																	if (relOp == "<")
																		printToASM("JL " + label1, codeFile);
																	else if (relOp == ">")
																		printToASM("JG " + label1, codeFile);
																	else if (relOp == "==")
																		printToASM("JE " + label1, codeFile);
																	else if (relOp == ">=")
																		printToASM("JGE " + label1, codeFile);
																	else if (relOp == "<=")
																		printToASM("JLE " + label1, codeFile);
																	else if (relOp == "!=")
																		printToASM("JNE " + label1, codeFile);

																	printToASM("MOV CX, 0", codeFile);
																	printToASM("JMP " + label2, codeFile);
																	printToASM(label1 + ":", codeFile);
																	printToASM("MOV CX, 1", codeFile);
																	printToASM(label2 + ":", codeFile);
																	

																}
		;
				
simple_expression : term 										{
																	$$ = $1;
																	logData(logFile, yylineno, "simple_expression : term", $$->name);
																}
		  | simple_expression ADDOP
		  {
			  if (!inFactorArgList)
			  {
				if (inForLoopThird)
				{
					forThirdStr += "PUSH CX\n";
				}
				else
				{
					// push current CX up
					printToASM("PUSH CX", codeFile);
				}
			  }
			  else
			  {
				  simpleExpStr += "PUSH CX\n";
			  }
			  
		  } term						{

			  														if ($2->name == "+")
																	// keep track that we are going to add
																		addOrSub = 1;
																	else
																		addOrSub = 0;
			  														// ASM code
																	if (!inFactorArgList)
																	{
																		if (inForLoopThird)
																		{
																			forThirdStr += "POP AX\n";
																			if (addOrSub)
																				forThirdStr += "ADD AX, CX\n";
																			else
																				forThirdStr += "SUB AX, CX\n";
																			forThirdStr += "MOV CX, AX\n";
																		}
																		else
																		{
																			printToASM("POP AX", codeFile);
																			if (addOrSub)
																				printToASM("ADD AX, CX", codeFile);
																			else
																				printToASM("SUB AX, CX", codeFile);
																			printToASM("MOV CX, AX", codeFile);
																		}
																	}
																	else
																	{
																		simpleExpStr += "POP AX\n";
																		if (addOrSub)
																			simpleExpStr += "ADD AX, CX\n";
																		else
																			simpleExpStr += "SUB AX, CX\n";
																		simpleExpStr += "MOV CX, AX\n";
																		//functionArgumentASMStack.push(simpleExpStr);
																		//simpleExpStr = "";
																	}
																	
			  														string retType;
																	// if any of them is a float, change final term to float
																	if ($1->getType() == "float" || $4->getType() == "float")
																	{
																		retType = "float";
																	}
																	else
																	{
																		retType = "int";
																	}
			  														str = $1->name; str += ($2->name); str += $4->name;
																	$$ = new SymbolInfo(str, retType);
																	logData(logFile, yylineno, "simple_expression : simple_expression ADDOP term", $$->name);
																	// simpleExpStr = "";
		  														} 
		  ;
					
term :	unary_expression										{
																	if ($1->isInTable())
																	{
																		// char ASMCode[10];
																		
																		// SymbolInfo *originalSymbolInfo = table->lookUp($1->getName());
																		// sprintf(ASMCode, "MOV CX, %d[BP]", originalSymbolInfo->getOffset());
																		// printToASM(ASMCode, codeFile);
																	}
																	$$ = $1;
																	logData(logFile, yylineno, "term : unary_expression", $$->name);
																}
     |  term MULOP {
		 if (!inFactorArgList)
		 {
			if (inForLoopThird)
				forThirdStr += "PUSH CX\n";
			else
				printToASM("PUSH CX", codeFile);
		 }
		else
			simpleExpStr += "PUSH CX\n";
		 } unary_expression {
		 															// check modulus integer type
																	string leftType = $1->getType();
																	string rightType = $4->getType();
																	string symbol = $2->getName();
																	string retType;
																	if (symbol == "%")
																	{
																		// check zero modulus
																		if ($4->name == "0")
																		{
																			errorCount++;
																			logError(logFile, errorFile, yylineno, "Modulus by Zero");
																		}
																		// check whether both sides of modulus integer or not
																		else if (leftType == "float" || leftType == "CONST_FLOAT" || rightType == "float" || rightType == "CONST_FLOAT" )
																		{
																			errorCount++;
																			logError(logFile, errorFile, yylineno, "Non-Integer operand on modulus operator");
																			retType = "ERROR";
																		}
																		else
																		{
																			retType = "int";
																		}
																	}
																	else
																	{
																		// if lval or rval float, ret type is float
																		if ($1->getType() == "float" || $4->getType() == "float")
																		{
																			retType = "float";
																		}
																		else
																		{
																			retType = "int";
																		}
																	}

																	// check if function, and then function type
																	if (leftType == "void" || rightType == "void")
																	{
																		errorCount++;
																		logError(logFile, errorFile, yylineno, "Void function used in expression");
																	}
		 															str = $1->name; str += $2->name; str += $4->name;
																	$$ = new SymbolInfo(str, retType);
																	logData(logFile, yylineno, "term : term MULOP unary_expression", $$->name);
																	
																	string mulOp = $2->name;
																	if (!inFactorArgList)
																	{
																		if (inForLoopThird)
																		{
																			forThirdStr += "POP AX\n";
																			if (mulOp == "*")
																			{
																				forThirdStr += "IMUL CX\n";
																				forThirdStr += "MOV CX, AX\n";
																			}
																				
																			else
																			{
																				forThirdStr += "CWD\n";
																				forThirdStr += "IDIV CX\n";
																				if (mulOp == "%")
																					forThirdStr += "MOV CX, DX\n";
																				else
																					forThirdStr += "MOV CX, AX\n";
																			}
																		}
																		else
																		{
																			printToASM("POP AX", codeFile);
																			if (mulOp == "*")
																			{
																				printToASM("IMUL CX", codeFile);
																				printToASM("MOV CX, AX", codeFile);
																			}
																				
																			else
																			{
																				printToASM("CWD", codeFile);
																				printToASM("IDIV CX", codeFile);
																				if (mulOp == "%")
																					printToASM("MOV CX, DX", codeFile);
																				else
																					printToASM("MOV CX, AX", codeFile);
																			}
																		}
																	}
																	else
																	{
																		simpleExpStr += "POP AX\n";
																		if (mulOp == "*")
																		{
																			simpleExpStr += "IMUL CX\n";
																			simpleExpStr += "MOV CX, AX\n";
																		}
																			
																		else
																		{
																			simpleExpStr += "CWD\n";
																			simpleExpStr += "IDIV CX\n";
																			if (mulOp == "%")
																				simpleExpStr += "MOV CX, DX\n";
																			else
																				simpleExpStr += "MOV CX, AX\n";
																		}
																	}
	 															}
     ;

unary_expression : ADDOP unary_expression						{ 	
																	str = $1->name + $2->name; 
																	$$ = new SymbolInfo(str, $2->getType());
																	logData(logFile, yylineno, "unary_expression : ADDOP unary_expression", $$->name);

																	// ASM Code
																	if (!inFactorArgList)
																	{
																		if (inForLoopThird)
																		{
																			forThirdStr += "NEG CX\n";
																		}
																		else
																		{
																			if($1->name == "-")
																			printToASM("NEG CX", codeFile);
																		}
																	}
																	else
																	{
																		if($1->name == "-")
																			simpleExpStr += "NEG CX\n";
																	}
												
																}  
		 | NOT unary_expression									{
			 														str = "!"; str += $2->name;
																	$$ = new SymbolInfo(str, $2->getType());
																	logData(logFile, yylineno, "unary_expression : NOT unary_expression", $$->name);

																	// ASM Code
																	if (!inFactorArgList)
																	{
																		if (inForLoopThird)
																		{
																			string label = newLabel();
																			forThirdStr += "JCXZ " + label + "\n";
																			//printToASM("JCXZ " + label, codeFile);
																			forThirdStr += "MOV CX, 0\n";
																			//printToASM("MOV CX, 0", codeFile);
																			string label2 = newLabel();
																			// printToASM("JMP " + label2, codeFile);
																			forThirdStr += "JMP " + label2 + "\n";
																			//printToASM(label + ":", codeFile);
																			forThirdStr += label + ":\n";
																			//printToASM("MOV CX, 1", codeFile);
																			forThirdStr += "MOV CX, 1\n";
																			//printToASM(label2 + ":", codeFile);
																			forThirdStr += label2 + ":\n";
																		}
																		else
																		{
																			string label = newLabel();
																			printToASM("JCXZ " + label, codeFile);
																			printToASM("MOV CX, 0", codeFile);
																			string label2 = newLabel();
																			printToASM("JMP " + label2, codeFile);
																			printToASM(label + ":", codeFile);
																			printToASM("MOV CX, 1", codeFile);
																			printToASM(label2 + ":", codeFile);
																		}	
																	}
																	else
																	{
																		string label = newLabel();
																		simpleExpStr += "JCXZ " + label + "\n";
																		//printToASM("JCXZ " + label, codeFile);
																		simpleExpStr += "MOV CX, 0\n";
																		//printToASM("MOV CX, 0", codeFile);
																		string label2 = newLabel();
																		// printToASM("JMP " + label2, codeFile);
																		simpleExpStr += "JMP " + label2 + "\n";
																		//printToASM(label + ":", codeFile);
																		simpleExpStr += label + ":\n";
																		//printToASM("MOV CX, 1", codeFile);
																		simpleExpStr += "MOV CX, 1\n";
																		//printToASM(label2 + ":", codeFile);
																		simpleExpStr += label2 + ":\n";
																	}
																	
		 														} 
		 | factor 												{
																	$$ = $1;
																	logData(logFile, yylineno, "unary_expression : factor", $$->name);
																}
		 ;
	
factor	: variable												{
																	$$ = new SymbolInfo($1->name, $1->type);
																	$$->setInTable(true);
																	// cout << getArrayName($1->name) << endl;
																	logData(logFile, yylineno, "factor : variable", $$->name);

																	if (!inFactorArgList)
																	{
																		if (inForLoopThird)
																		{
																			char ASMCode[20];	
																			SymbolInfo *current = table->lookUp(getArrayName($1->name));
																			if (!current->isArray())
																			{
																				sprintf(ASMCode, "MOV CX, %d[BP]\n", current->getOffset());
																				forThirdStr += ASMCode;
																				//functionArgumentASMStack.push(ASMCode);
																			}
																			else
																			{
																				// extract index;
																				char ASMCode[10];
																				string str;
																				int index = getArraySize($1->name);
																				// printToASM("PUSH BP", codeFile);
																				forThirdStr += "PUSH BP\n";
																				// printToASM("SAL CX, 1", codeFile);
																				forThirdStr += "SAL CX, 1\n";
																				sprintf(ASMCode, "ADD CX, %d\n", current->getOffset());
																				forThirdStr += ASMCode;
																				// printToASM(ASMCode, codeFile);
																				// printToASM("ADD BP, CX", codeFile);
																				forThirdStr += "ADD BP, CX\n";
																				//printToASM("MOV CX , PTR WORD [BP]", codeFile);
																				forThirdStr += "MOV CX, PTR WORD [BP]\n";
																				// printToASM("POP BP", codeFile);
																				forThirdStr += "POP BP\n";
																				//functionArgumentASMStack.push(str);
																			}
																		}
																		else
																		{
																			char ASMCode[10];	
																			SymbolInfo *current = table->lookUp(getArrayName($1->name));
																			if (!current->isArray())
																			{
																				sprintf(ASMCode, "MOV CX, %d[BP]", current->getOffset());
																				printToASM(ASMCode, codeFile);
																			}
																			else
																			{
																				// extract index;
																				char ASMCode[10];
																				
																				int index = getArraySize($1->name);
																				printToASM("PUSH BP", codeFile);
																				printToASM("SAL CX, 1", codeFile);
																				sprintf(ASMCode, "ADD CX, %d", current->getOffset());
																				printToASM(ASMCode, codeFile);
																				printToASM("ADD BP, CX", codeFile);
																				printToASM("MOV CX , PTR WORD [BP]", codeFile);
																				printToASM("POP BP", codeFile);
																			}
																		}	
																	}

																	else
																	{
																		char ASMCode[20];	
																		SymbolInfo *current = table->lookUp(getArrayName($1->name));
																		if (!current->isArray())
																		{
																			sprintf(ASMCode, "MOV CX, %d[BP]\n", current->getOffset());
																			simpleExpStr += ASMCode;
																			//functionArgumentASMStack.push(ASMCode);
																		}
																		else
																		{
																			// extract index;
																			char ASMCode[10];
																			string str;
																			int index = getArraySize($1->name);
																			// printToASM("PUSH BP", codeFile);
																			simpleExpStr += "PUSH BP\n";
																			// printToASM("SAL CX, 1", codeFile);
																			simpleExpStr += "SAL CX, 1\n";
																			sprintf(ASMCode, "ADD CX, %d\n", current->getOffset());
																			simpleExpStr += ASMCode;
																			// printToASM(ASMCode, codeFile);
																			// printToASM("ADD BP, CX", codeFile);
																			simpleExpStr += "ADD BP, CX\n";
																			//printToASM("MOV CX , PTR WORD [BP]", codeFile);
																			simpleExpStr += "MOV CX, PTR WORD [BP]\n";
																			// printToASM("POP BP", codeFile);
																			simpleExpStr += "POP BP\n";
																			//functionArgumentASMStack.push(str);
																		}
																	}
																}
	| ID LPAREN { inFactorArgList = true; } 
	argument_list RPAREN										{
																	// this is a function
																	// so the type of the symbolInfo should be the return type of the function.
																	SymbolInfo *symbolInfo = table->lookUp($1->name);
																	string retType = "none";
																	// if this does not exist, show error
																	if (symbolInfo == NULL)
																	{
																		errorCount++;
																		logError(logFile, errorFile, yylineno, "Undeclared function " + $1->name);
																	}
																	else
																	{
																		// check whether ID is function or not
																		if (!symbolInfo->isFunc())
																		{
																			errorCount++;
																			logError(logFile, errorFile, yylineno, "Not a function");
																		}
																		else
																		{
																			
																			// check args
																			vector<string> argNames = split($4->name, ',');
																			vector<string> argTypes = split($4->type, ',');
																			vector<Parameter> paramList = symbolInfo->getParamList();
																			// check the number of args with declared no. of args
																			if (argNames.size() != paramList.size())
																			{
																				errorCount++;
																				logError(logFile, errorFile, yylineno, "Total number of arguments mismatch in function " + symbolInfo->name);
																			}
																			else
																			{
																				// number same, check for types
																				for (int i = 0; i < argNames.size(); i++)
																				{
																					// get the argument type
																					string declaredType = paramList[i].type;
																					if (declaredType != argTypes[i])
																					{
																						errorCount++;
																						string incorrectType = argTypes[i];
																						if (incorrectType == "int*" || incorrectType == "float*")
																							incorrectType = "array";
																						logError(logFile, errorFile, yylineno, "Type mismatch, " + argNames[i] + " is a " + incorrectType);
																					}																					
																				}

																				// for (int i = argNames.size() - 1; i >= 0; i--)
																				// {
																				// 	// check whether it is a variable or a constant
																				// 	SymbolInfo *current = table->lookUp(argNames[i]);	
																				// 	if (current == NULL)
																				// 	{
																				// 		// is a const, so move const to CX
																				// 		char ASMCode[10];
																				// 		// sprintf(ASMCode, "MOV CX, %s", argNames[i].c_str());
																				// 		// printToASM(ASMCode, codeFile);
																				// 		printToASM("PUSH CX", codeFile);
																				// 	}
																				// 	else
																				// 	{
																				// 		// is a variable, move from required offset to CX
																				// 		char ASMCode[10];
																				// 		if (current->isGlobal())
																				// 		{
																				// 			sprintf(ASMCode, "MOV CX, %s", current->getName().c_str());
																				// 		}
																				// 		else
																				// 		{
																				// 			sprintf(ASMCode, "MOV CX, %d[BP]", current->getOffset());
																				// 		}
																				// 		printToASM(ASMCode, codeFile);
																				// 		printToASM("PUSH CX", codeFile);
																				// 	}																			
																				// }

																				while (!functionArgumentASMStack.empty())
																				{
																					string str = functionArgumentASMStack.top();
																					functionArgumentASMStack.pop();
																					printToASM(str, codeFile);
																					printToASM("PUSH CX", codeFile);
																				}
																				
																			}
																			// set return type equal to return type of function
																			retType = symbolInfo->getType();
																			string ASMCode = "CALL " + $1->name;
																			printToASM(ASMCode, codeFile);
																		}
																	}
																	str = $1->name; str += "("; str += $4->name; str += ")";
																	$$ = new SymbolInfo(str, retType);
																	logData(logFile, yylineno, "factor : ID LPAREN argument_list RPAREN", $$->name);
																	inFactorArgList = false;
		 														}
	| LPAREN expression RPAREN									{ 
																	str = "("; str += $2->name; str += ")";
																	$$ = new SymbolInfo(str, $2->type);
																	logData(logFile, yylineno, "factor : LPAREN expression RPAREN", $$->name);
																}
	| CONST_INT 												{
																	$$ = new SymbolInfo($1->name, "int");
																	if (!inFactorArgList)
																	{
																		if (inForLoopThird)
																		{
																			string ASMCode = "MOV CX, " + $1->name + "\n";
																			forThirdStr += ASMCode;
																		}
																		else
																		{
																			string ASMCode = "MOV CX, " + $1->name;
																			printToASM(ASMCode, codeFile);
																		}
																	}
																	else
																	{
																		string ASMCode = "MOV CX, " + $1->name + "\n";
																		simpleExpStr += ASMCode;
																	}
																	logData(logFile, yylineno, "factor : CONST_INT", $$->name);
	 															}
	| CONST_FLOAT												{ 
																	$$ = new SymbolInfo($1->name, "float");
																	logData(logFile, yylineno, "factor : CONST_FLOAT", $$->name);
	 															}
	| variable INCOP 											{
																	str = $1->name; str += "++";
																	$$ = new SymbolInfo(str, $1->getType());
																	logData(logFile, yylineno, "factor : variable INCOP", $$->name);

																	// ASM Code
																	// increase value of variable and save it again
																	SymbolInfo *current = table->lookUp(getArrayName($1->name));
																	if (!inFactorArgList)
																	{
																		if (inForLoopThird)
																		{
																			if (current->isArray())
																			{
																				char ASMCode[20];
																				
																				forThirdStr += "PUSH BP\nSAL CX, 1\n";
																				sprintf(ASMCode, "ADD CX, %d\n", current->getOffset());
																				forThirdStr += ASMCode;
																				forThirdStr += "ADD BP, CX\nMOV CX, PTR WORD [BP]\n";
																				forThirdStr += "MOV AX, CX\nADD AX, 1\nMOVE PTR WORD [BP], AX\nPOP BP\n";
																			}
																			else
																			{
																				// bring to CX, add 1, send it back
																				char ASMCode[20];
																				sprintf(ASMCode, "MOV CX, %d[BP]\n", current->getOffset());
																				forThirdStr += ASMCode;
																				forThirdStr += "MOV AX, CX\nADD AX, 1\n";
																				sprintf(ASMCode, "MOV %d[BP], AX\n", current->getOffset());
																				forThirdStr += ASMCode;
																			}
																		}
																		else
																		{
																			if (current->isArray())
																			{
																				char ASMCode[20];
																				
																				int index = getArraySize($1->name);
																				printToASM("PUSH BP", codeFile);
																				printToASM("SAL CX, 1", codeFile);
																				sprintf(ASMCode, "ADD CX, %d", current->getOffset());
																				printToASM(ASMCode, codeFile);
																				printToASM("ADD BP, CX", codeFile);
																				printToASM("MOV CX , PTR WORD [BP]", codeFile);
																				printToASM("MOV AX, CX", codeFile);
																				printToASM("ADD AX, 1", codeFile);
																				printToASM("MOV PTR WORD [BP], AX", codeFile);
																				printToASM("POP BP", codeFile);
																			}
																			else
																			{
																				// bring to CX, add 1, send it back
																				char ASMCode[20];
																				sprintf(ASMCode, "MOV CX, %d[BP]", current->getOffset());
																				printToASM(ASMCode, codeFile);
																				printToASM("MOV AX, CX", codeFile);
																				printToASM("ADD AX, 1", codeFile);
																				sprintf(ASMCode, "MOV %d[BP], AX", current->getOffset());
																				printToASM(ASMCode, codeFile);
																			}
																		}	
																	}
																	else
																	{
																		if (current->isArray())
																		{
																			char ASMCode[20];
																			
																			simpleExpStr += "PUSH BP\nSAL CX, 1\n";
																			sprintf(ASMCode, "ADD CX, %d\n", current->getOffset());
																			simpleExpStr += ASMCode;
																			simpleExpStr += "ADD BP, CX\nMOV CX, PTR WORD [BP]\n";
																			simpleExpStr += "MOV AX, CX\nADD AX, 1\nMOVE PTR WORD [BP], AX\nPOP BP\n";
																		}
																		else
																		{
																			// bring to CX, add 1, send it back
																			char ASMCode[20];
																			sprintf(ASMCode, "MOV CX, %d[BP]\n", current->getOffset());
																			simpleExpStr += ASMCode;
																			simpleExpStr += "MOV AX, CX\nADD AX, 1\n";
																			sprintf(ASMCode, "MOV %d[BP], AX\n", current->getOffset());
																			simpleExpStr += ASMCode;
																		}
																	}																	
																}
	| variable DECOP											{
																	str = $1->name; str += "--";
																	$$ = new SymbolInfo(str, $1->getType());
																	logData(logFile, yylineno, "factor : variable DECOP", $$->name);

																	SymbolInfo *current = table->lookUp(getArrayName($1->name));
																	if (!inFactorArgList)
																	{
																		if (inForLoopThird)
																		{
																			if (current->isArray())
																			{
																				char ASMCode[20];
																				
																				forThirdStr += "PUSH BP\nSAL CX, 1\n";
																				sprintf(ASMCode, "ADD CX, %d\n", current->getOffset());
																				forThirdStr += ASMCode;
																				forThirdStr += "ADD BP, CX\nMOV CX, PTR WORD [BP]\n";
																				forThirdStr += "MOV AX, CX\SUB AX, 1\nMOVE PTR WORD [BP], AX\nPOP BP\n";
																			}
																			else
																			{
																				char ASMCode[20];
																				sprintf(ASMCode, "MOV CX, %d[BP]\n", current->getOffset());
																				forThirdStr += ASMCode;
																				forThirdStr += "MOV AX, CX\nSUB AX, 1\n";
																				sprintf(ASMCode, "MOV %d[BP], AX\n", current->getOffset());
																				forThirdStr += ASMCode;
																			}
																		}
																		else
																		{
																			if (current->isArray())
																			{
																				char ASMCode[10];
																				
																				int index = getArraySize($1->name);
																				printToASM("PUSH BP", codeFile);
																				printToASM("SAL CX, 1", codeFile);
																				sprintf(ASMCode, "ADD CX, %d", current->getOffset());
																				printToASM(ASMCode, codeFile);
																				printToASM("ADD BP, CX", codeFile);
																				printToASM("MOV CX , PTR WORD [BP]", codeFile);
																				printToASM("MOV AX, CX", codeFile);
																				printToASM("SUB AX, 1", codeFile);
																				printToASM("MOV PTR WORD [BP], AX", codeFile);
																				printToASM("POP BP", codeFile);
																			}
																			else
																			{
																				// bring to CX, add 1, send it back
																				char ASMCode[10];
																				sprintf(ASMCode, "MOV CX, %d[BP]", current->getOffset());
																				printToASM(ASMCode, codeFile);
																				printToASM("MOV AX, CX", codeFile);
																				printToASM("SUB AX, 1", codeFile);
																				sprintf(ASMCode, "MOV %d[BP], AX", current->getOffset());
																				printToASM(ASMCode, codeFile);
																			}
																		}
																		
																	}
																	else
																	{
																		if (current->isArray())
																		{
																			char ASMCode[20];
																			
																			simpleExpStr += "PUSH BP\nSAL CX, 1\n";
																			sprintf(ASMCode, "ADD CX, %d\n", current->getOffset());
																			simpleExpStr += ASMCode;
																			simpleExpStr += "ADD BP, CX\nMOV CX, PTR WORD [BP]\n";
																			simpleExpStr += "MOV AX, CX\SUB AX, 1\nMOVE PTR WORD [BP], AX\nPOP BP\n";
																		}
																		else
																		{
																			char ASMCode[20];
																			sprintf(ASMCode, "MOV CX, %d[BP]\n", current->getOffset());
																			simpleExpStr += ASMCode;
																			simpleExpStr += "MOV AX, CX\nSUB AX, 1\n";
																			sprintf(ASMCode, "MOV %d[BP], AX\n", current->getOffset());
																			simpleExpStr += ASMCode;
																		}
																	}
																	
																}
	;
	
argument_list : arguments										{
																	$$ = $1;
																	logData(logFile, yylineno, "argument_list : arguments", $$->name);
																}
			  |													{
																	$$ = new SymbolInfo("", "none");
																	logData(logFile, yylineno, "argument_list : ", $$->name);
			  													}
			  ;
	
arguments : arguments COMMA logic_expression					{
																	str = $1->name; str += ","; str += $3->name;
																	string argTypes = $1->type + "," + $3->type;
																	$$ = new SymbolInfo(str, argTypes);
																	logData(logFile, yylineno, "arguments : arguments COMMA logic_expression", $$->name);
																	functionArgumentASMStack.push(simpleExpStr);
																	simpleExpStr = "";
																}
	      | logic_expression									{
			  														$$ = $1;
																	logData(logFile, yylineno, "arguments : logic_expression", $$->name);
																	functionArgumentASMStack.push(simpleExpStr);
																	simpleExpStr = "";
		  														}
	      ;
 

%%
int main(int argc,char *argv[])
{
	table = new SymbolTable(30);
	inputFile = fopen("input.txt", "r");
	codeFile = fopen("mycode.asm", "w");
	logFile = fopen("log.txt", "w");
	errorFile = fopen("error.txt", "w");
	// optimizedFile = fopen("myoptimizedfile.asm", "w");
	yyin = inputFile;
	yyparse();
	table->printAllScopeTables(logFile);
	fprintf(logFile, "Total Lines: %d\n", yylineno);
	fprintf(logFile, "Total Errors: %d\n", errorCount);

	// Time for optimization
	fclose(codeFile);
	ifstream initialCode("mycode.asm");
	string line;
	vector<string> lines;
	while(getline(initialCode, line)) {
		lines.push_back(line);
	}
	int i;
	string mark = ".CODE";
	bool write[lines.size()];
	for (i = 0; i < lines.size(); i++)
		write[i] = true;

	for (i = 0; i < lines.size(); i++) {
		if (lines[i] == mark)
			break;
	}
	i++;
	for(; i < lines.size() - 1; i++) {
		// optimization happens here
		if (lines[i].find(" ") != string::npos && lines[i+1].find(" ") != string::npos)
		{
			string operation1 = split(lines[i], ' ')[0];
			string operation2 = split(lines[i+1], ' ')[0];
			if (operation1 == "MOV" && operation2 == "MOV")
			{
				string reg11 = split(lines[i], ' ')[1].substr(0, split(lines[i], ' ')[1].find(","));
				string reg12 = split(lines[i], ' ')[2];
				string reg21 = split(lines[i+1], ' ')[1].substr(0, split(lines[i], ' ')[1].find(","));
				string reg22 = split(lines[i+1], ' ')[2];
				if (reg11 == reg22 && reg12 == reg21)
				{
					write[i+1] = false;
				}
			} else if (operation1 == "PUSH" && operation2 == "POP")
			{
				string reg1 = split(lines[i], ' ')[1];
				string reg2 = split(lines[i+1], ' ')[1];
				if(reg1 == reg2)
				{
					write[i] = false;
					write[i+1] = false;
				}
			}
		}
	}

	// now write true lines to optimized file
	ofstream optimized("myoptimizedfile.asm");
	for(int i = 0; i < lines.size(); i++)
	{
		if (write[i])
			optimized << lines[i] << endl;
	}
	return 0;
}

