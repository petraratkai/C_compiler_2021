%code requires{
	#include "ast.hpp"
	#include <cassert>
	#include <string>

	extern Program* g_root;
	extern FILE *yyin

	int yylex(void);
	void yyerror(const char *);
}

%union{
	Program* expr;
	std::string* string;
}

%token T_AUTO T_BREAK T_CASE T_CHAR T_CONST T_CONTINUE T_DEFAULT T_DO T_DOUBLE T_ELSE T_ENUM T_EXTERN T_FLOAT T_FOR T_GOTO T_IF T_INT T_LONG T_REGISTER T_RETURN T_SHORT T_SIGNED T_SIZEOF T_STATIC T_STRUCT T_SWITCH T_TYPEDEF T_UNION T_UNSIGNED T_VOID T_VOLATILE T_WHILE
%token T_PLUS T_MINUS T_MULT T_DIVIDE T_MODULO T_INCREMENENT T_DECREMENT
%token T_EQUAL T_UNEQUAL T_GREATER T_LESSER T_GREATEREQ T_LESSEREQ
%token T_AND T_OR T_NOT
%token T_BITAND T_BITOR T_BITXOR T_BITCOMP T_BITLSHIFT T_BITRSHIFT
%token T_ASSIGN T_PLUSASSIGN T_MINUSASSIGN T_MULTASSIGN T_DIVIDEASSIGN T_MODULOASSIGN T_LSHFTASSIGN T_RSHFTASSIGN T_ANDASSIGN T_XORASSIGN T_ORASSIGN
%token T_LCURLBRACKET T_RCURLBRACKET T_LSQUAREBRACKET T_RSQUAREBRACKET T_LBRACKET T_RBRACKET
%token T_ACCESS T_POINTERACCESS
%token T_SEMICOLON T_QUESTIONMARK T_COLON T_COMMA
%token IDENTIFIER INT_CONST FLOAT_CONST CHAR_CONST STRING_CONST

%type <string> T_AUTO T_BREAK T_CASE T_CHAR T_CONST T_CONTINUE T_DEFAULT T_DO T_DOUBLE T_ELSE T_ENUM T_EXTERN T_FLOAT T_FOR T_GOTO T_IF T_INT T_LONG T_REGISTER T_RETURN T_SHORT T_SIGNED T_SIZEOF T_STATIC T_STRUCT T_SWITCH T_TYPEDEF T_UNION T_UNSIGNED T_VOID T_VOLATILE T_WHILE T_PLUS T_MINUS T_MULT T_DIVIDE T_MODULO T_INCREMENENT T_DECREMENT T_EQUAL T_UNEQUAL T_GREATER T_LESSER T_GREATEREQ T_LESSEREQ T_AND T_OR T_NOT T_BITAND T_BITOR T_BITXOR T_BITCOMP T_BITLSHIFT T_BITRSHIFT T_ASSIGN T_PLUSASSIGN T_MINUSASSIGN T_MULTASSIGN T_DIVIDEASSIGN T_MODULOASSIGN T_LSHFTASSIGN T_RSHFTASSIGN T_ANDASSIGN T_XORASSIGN T_ORASSIGN T_LCURLBRACKET T_RCURLBRACKET T_LSQUAREBRACKET T_RSQUAREBRACKET T_LBRACKET T_RBRACKET T_ACCESS T_POINTERACCESS T_SEMICOLON T_QUESTIONMARK T_COLON T_COMMA IDENTIFIER INT_CONST FLOAT_CONST CHAR_CONST STRING_CONST

%type <expr> 	program_top function_definition declaration declaration_specifiers type_specifier declarator compound_statement statement jump_statement expression assignment_expression unary_expression assignment_operator constant_expr conditional_expression primary_expression

%start program_top

%%

program_top:
	function_definition 										{$$ = $1;}
;


function_definition:
	declaration_specifiers declarator compound_statement declaration		{$$ = new Function($2, $3, $4, $1;}
;

declaration:
	declaration_specifiers declarator 							{$$ = new Declaration($1, $2, NULL);}
;

declaration_specifiers:
	type_specifier												{$$ = $1;}
;

type_specifier:
		T_INT  													{$$ = IntType;}
	|	T_DOUBLE        										{$$ = DoubleType;}
	|	T_VOID       											{$$ = VoidType;}
	|	T_CHAR 													{$$ = CharType;}
;

declarator:
		IDENTIFIER												{$$ = $1;}
;

compound_statement:
		statement 												{vector<Statement*>* Statements = new vector<Statement*>*; Statements->push_back($1); $$ = Statements;}

;

statement:
		jump_statement											{$$ = $1;}
;

jump_statement:
		T_RETURN T_SEMICOLON 									{$$ = new ReturnStmt(NULL);}
	|	T_RETURN expression T_SEMICOLON 						{$$ = new ReturnStmt($2);}
;

expression:
		assignment_expression 									{$$ = $1;}
;

assignment_expression:
		conditional_expression									{$$ = $1;}
;

unary_expression:
		primary_expression										{$$ = $1;}
;

assignment_operator:
		T_ASSIGN 												{$$ = $1;}
;

constant_expr:
		conditional_expression									{$$ = $1;}
;

conditional_expression:
		primary_expression										{$$ = $1;}
;

primary_expression:
		IDENTIFIER												{$$ = new Variable{$1};}
	|	INT_CONST												{$$ = new Number{$1};}
	|	FLOAT_CONST    											{$$ = new Variable{$1};}
	|	CHAR_CONST   											{$$ = new Variable{$1};}
	|	STRING_CONST											{$$ = new Variable{$1};}
	|	T_LBRACKET expression T_RBRACKET 						{$$ = $2;}
;

%%

Program* g_root;
Program* parseAST(std::string file){
	yyin = fopen(file.c_str(), "r");
	if(yyin){
	g_root = new Program();
	yyparse();
	}
	return g_root;
}
