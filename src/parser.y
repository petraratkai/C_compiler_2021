%code requires{
	#include "ast.hpp"
	#include <cassert>
	#include <string>
	#include <vector>

	extern Program* g_root;
	extern FILE *yyin;

	int yylex(void);
	void yyerror(const char *);
}

%union{
	Program* prog;
	Expression* expr;
	Statement* st;
	CompoundStmt* cst;
	Function* fn;
	VarType vtype;
	std::vector<Statement*>* vst;
	std::string* string;
}

%token T_AUTO T_BREAK T_CASE T_CHAR T_CONST T_CONTINUE T_DEFAULT T_DO T_DOUBLE T_ELSE T_ENUM T_EXTERN T_FLOAT T_FOR T_GOTO T_IF T_INT T_LONG T_REGISTER T_RETURN T_SHORT T_SIGNED T_SIZEOF T_STATIC T_STRUCT T_SWITCH T_TYPEDEF T_UNION T_UNSIGNED T_VOID T_VOLATILE T_WHILE
%token T_PLUS T_MINUS T_MULT T_DIVIDE T_MODULO T_INCREMENT T_DECREMENT
%token T_EQUAL T_UNEQUAL T_GREATER T_LESSER T_GREATEREQ T_LESSEREQ
%token T_AND T_OR T_NOT
%token T_BITAND T_BITOR T_BITXOR T_BITCOMP T_BITLSHFT T_BITRSHFT
%token T_ASSIGN T_PLUSASSIGN T_MINUSASSIGN T_MULTASSIGN T_DIVIDEASSIGN T_MODULOASSIGN T_LSHFTASSIGN T_RSHFTASSIGN T_ANDASSIGN T_XORASSIGN T_ORASSIGN
%token T_LCURLBRACKET T_RCURLBRACKET T_LSQUAREBRACKET T_RSQUAREBRACKET T_LBRACKET T_RBRACKET T_ELLIPSIS
%token T_ACCESS T_POINTERACCESS
%token T_SEMICOLON T_QUESTIONMARK T_COLON T_COMMA
%token IDENTIFIER INT_CONST FLOAT_CONST CHAR_CONST STRING_CONST

%type <string> T_AUTO T_BREAK T_CASE T_CHAR T_CONST T_CONTINUE T_DEFAULT T_DO T_DOUBLE T_ELSE T_ENUM T_EXTERN T_FLOAT T_FOR T_GOTO T_IF T_INT T_LONG T_REGISTER T_RETURN T_SHORT T_SIGNED T_SIZEOF T_STATIC T_STRUCT T_SWITCH T_TYPEDEF T_UNION T_UNSIGNED T_VOID T_VOLATILE T_WHILE T_PLUS T_MINUS T_MULT T_DIVIDE T_MODULO T_INCREMENT T_DECREMENT T_EQUAL T_UNEQUAL T_GREATER T_LESSER T_GREATEREQ T_LESSEREQ T_AND T_OR T_NOT T_BITAND T_BITOR T_BITXOR T_BITCOMP T_BITLSHFT T_BITRSHFT T_ASSIGN T_PLUSASSIGN T_MINUSASSIGN T_MULTASSIGN T_DIVIDEASSIGN T_MODULOASSIGN T_LSHFTASSIGN T_RSHFTASSIGN T_ANDASSIGN T_XORASSIGN T_ORASSIGN T_LCURLBRACKET T_RCURLBRACKET T_LSQUAREBRACKET T_RSQUAREBRACKET T_LBRACKET T_RBRACKET T_ACCESS T_POINTERACCESS T_SEMICOLON T_QUESTIONMARK T_COLON T_COMMA IDENTIFIER INT_CONST FLOAT_CONST CHAR_CONST STRING_CONST

%type <prog> translation_unit
%type <expr> storage_class_specifier  struct_or_union_specifier struct_or_union struct_declaration_list struct_declaration struct_declarator_list struct_declarator enum_specifier enumerator_list enumerator type_qualifier pointer type_qualifier_list parameter_type_list parameter_list parameter_declaration  abstract_declarator direct_abstract_declarator initializer initializer_list labeled_statement expression_statement  constant_expression expression assignment_expression conditional_expression logical_or_expression logical_and_expression inclusive_or_expression exclusive_or_expression and_expression equality_expression relational_expression shift_expression additive_expression multiplicative_expression cast_expression unary_expression postfix_expression primary_expression argument_expression_list
%type <string> unary_operator assignment_operator identifier_list declarator direct_declarator init_declarator init_declarator_list
%type <st> jump_statement iteration_statement statement selection_statement declaration_or_statement declaration
%type <vst> declaration_or_statement_list
%type <vtype> type_specifier specifier_qualifier_list type_name declaration_specifiers
%type <fn> function_definition external_declaration
%type <cst> compound_statement
%start translation_unit

%%

translation_unit:
		external_declaration 																	{g_root->push($1), $$ = g_root;}
	|	translation_unit external_declaration													{g_root->push($2), $$ = g_root;}
;

external_declaration:
		function_definition 																	{$$ = $1;}
	|	declaration 																			//{$$ = $1;}
;

function_definition:
		declaration_specifiers declarator declaration_or_statement_list compound_statement		{$$ = new Function(*$2, $4, $3, $1);} //Check it again
	|	declaration_specifiers declarator compound_statement 									{$$ = new Function(*$2, $3, NULL, $1);} //Check it again
	|	declarator declaration_or_statement_list compound_statement 							{$$ = new Function(*$1, $3, $2, VoidType);} //Check it again
	|	declarator compound_statement 															{$$ = new Function(*$1, $2, NULL, VoidType);} //Check it again
;


declaration:
		declaration_specifiers T_SEMICOLON						//{$$ = $1;} //FIX THIS
	|	declaration_specifiers init_declarator_list T_SEMICOLON {$$ = new Declaration(new Variable(*$2, $1), NULL);} 
;

declaration_specifiers:
		storage_class_specifier 								//{$$ = $1;} //FIX THIS
	|	storage_class_specifier declaration_specifiers 			//{$$ = $1;} //FIX THIS
	|	type_specifier 											{$$ = $1;} //FIX THIS
	|	type_specifier declaration_specifiers 					//{$$ = $1;} //FIX THIS
	|	type_qualifier	 										//{$$ = $1;} //FIX THIS
	|	type_qualifier declaration_specifiers					//{$$ = $1;} //FIX THIS	
;

init_declarator_list:
		init_declarator 										{$$ = $1;} //FIX THIS
	|	init_declarator_list T_COMMA init_declarator 			//{$$ = $1;} //FIX THIS
;

init_declarator:
		declarator 												{$$ = $1;} //FIX THIS
	|	declarator T_ASSIGN initializer 						{$$ = $1;} //FIX THIS
;

storage_class_specifier:
		T_TYPEDEF 												//{$$ = $1;} //check
	|	T_EXTERN 												//{$$ = $1;} //check
	|	T_STATIC 												//{$$ = $1;} //check
	|	T_AUTO 													//{$$ = $1;} //check
	|	T_REGISTER 												//{$$ = $1;} //check
;

type_specifier:
		T_INT  													{$$ = IntType;}
	|	T_DOUBLE        										{$$ = DoubleType;}
	|	T_VOID       											{$$ = VoidType;}
	|	T_CHAR 													{$$ = CharType;}
	|	T_SHORT 												{$$ = ShortType;}
	|	T_FLOAT													{$$ = FloatType;} 
	|	T_LONG 													{$$ = LongType;} 
	|	T_SIGNED 												{$$ = SignedType;} 
	|	T_UNSIGNED 												{$$ = UnsignedType;} 
	|	struct_or_union_specifier 								//{$$ = $1;} //check
	|	enum_specifier 											//{$$ = $1;} //check
	|	type_name 												//{$$ = $1;} //check
;

struct_or_union_specifier:
		struct_or_union IDENTIFIER T_LCURLBRACKET struct_declaration_list T_RCURLBRACKET 		//{$$ = $1;} //SORU not yet supported
	|	struct_or_union T_LCURLBRACKET struct_declaration_list T_RCURLBRACKET 					//{$$ = $1;} //SORU not yet supported
	|	struct_or_union IDENTIFIER 																//{$$ = $1;} //SORU not yet supported
;

struct_or_union:
		T_STRUCT																				//{$$ = $1;} //CHECK BACK
	|	T_UNION 																				//{$$ = $1;} //CHECK BACK
;

struct_declaration_list:
		struct_declaration 																		//{$$ = $1;} //FIX THIS
	|	struct_declaration_list struct_declaration 												//{$$ = $1;} //FIX THIS
;

struct_declaration:
		specifier_qualifier_list struct_declarator_list T_SEMICOLON 							//{$$ = $1;} //FIX THIS
;

specifier_qualifier_list:
		type_specifier specifier_qualifier_list 												//{$$ = $1;} //FIX THIS
	|	type_specifier 																			{$$ = $1;} //FIX THIS
	|	type_qualifier specifier_qualifier_list 												//{$$ = $1;} //FIX THIS
	|	type_qualifier 																			//{$$ = $1;} //FIX THIS
;

struct_declarator_list:
		struct_declarator 																		//{$$ = $1} //FIX THIS
	|	struct_declarator_list T_COMMA struct_declarator 										//{$$ = $3} //FIX THIS
;

struct_declarator:
		declarator 																				//{$$ = $1;}
	|	T_COLON constant_expression 															//{$$ = $2;}
	|	declarator T_COLON constant_expression 													//{$$ = $3;} //NO IDEA
;

enum_specifier:
		T_ENUM T_LCURLBRACKET enumerator_list T_RCURLBRACKET                                 	//{$$ = $3;} //FIX THIS
	|	T_ENUM IDENTIFIER T_LCURLBRACKET enumerator_list T_RCURLBRACKET 						//{$$ = $4;} //FIX THIS
	|	T_ENUM IDENTIFIER 																		//{$$ = $2;} //FIX THIS
;

enumerator_list:
		enumerator 																				//{$$ = $1;} //FIX THIS
	|	enumerator_list T_COMMA enumerator 														//{$$ = $3;} //FIX THIS
;

enumerator:
		IDENTIFIER 																				//{$$ = $1;} //FIX THIS
	|	IDENTIFIER	T_ASSIGN constant_expression 												//{$$ = $1;} //FIX THIS
;

type_qualifier:
		T_CONST 																				//{$$ = $1;} //Don't need to support const
	|	T_VOLATILE  																			//{$$ = $1;} //Check back idk maybe
;

declarator:
		pointer direct_declarator 																//{$$ = $2;} //No pointer support currently
	|	direct_declarator 																		{$$ = $1;}
;

direct_declarator:
		IDENTIFIER 																				{$$ = $1;}
	|	T_LBRACKET declarator T_RBRACKET 														{$$ = $2;}
	|	direct_declarator T_LSQUAREBRACKET constant_expression T_RSQUAREBRACKET  				//{$$ = $1;} //FIX THIS
	|	direct_declarator T_LSQUAREBRACKET T_RSQUAREBRACKET 									//{$$ = $1;}
	|	direct_declarator T_LBRACKET parameter_type_list T_RBRACKET 							//{$$ = $1;} //FIX THIS
	|	direct_declarator T_LBRACKET identifier_list T_RBRACKET 								//{$$ = $1;} //FIX THIS
	|	direct_declarator T_LBRACKET T_RBRACKET 												//{$$ = $1;} //FIX THIS 
;

pointer:
		T_MULT 																					//{$$ = NULL;} //Pointers not implemented
	|	T_MULT type_qualifier_list 																//{$$ = NULL;} //Pointers not implemented
	|	T_MULT pointer 																			//{$$ = NULL;} //Pointers not implemented
		|	T_MULT type_qualifier_list pointer  												//{$$ = NULL;} //Pointers not implemented
	;

type_qualifier_list:
		type_qualifier 																			//{$$ = $1;} //FIX THIS
	|	type_qualifier_list type_qualifier 														//{$$ = $1;} //FIX THIS
;

parameter_type_list:
		parameter_list 																			//{$$ = $1;} //FIX THIS
	|	parameter_list T_COMMA T_ELLIPSIS 														//{$$ = $1;} //FIX THIS
;

parameter_list:
		parameter_declaration 																	//{$$ = $1;}//FIX THIS
	|	parameter_list T_COMMA parameter_declaration 											//{$$ = $3;}//FIX THIS

parameter_declaration:
		declaration_specifiers declarator     													//{$$ = $1;} //FIX THIS
	|	declaration_specifiers abstract_declarator 												//{$$ = $1;} //FIX THIS
	|	declaration_specifiers																	//{$$ = $1;}
;

identifier_list:
		IDENTIFIER 																				{$$ = $1;}//FIX THIS							
	|	identifier_list T_COMMA IDENTIFIER														//{$$ = $1;}//FIX THIS			
;

type_name:
		specifier_qualifier_list																{$$ = $1;}//FIX THIS
	|	specifier_qualifier_list abstract_declarator 											//{$$ = $1;}//FIX THIS
;

abstract_declarator:
		pointer 																				//{$$ = $1;}//FIX THIS
	|	direct_abstract_declarator																//{$$ = $1;}//FIX THIS
	|	pointer direct_abstract_declarator														//{$$ = $1;}//FIX THIS
;

direct_abstract_declarator:
		T_LBRACKET abstract_declarator T_RBRACKET 												//{$$ = $2;}
	|	T_LSQUAREBRACKET T_RSQUAREBRACKET 														//{$$ = NULL;}
	|	T_LSQUAREBRACKET constant_expression T_RSQUAREBRACKET									//{$$ = $2;}
	|	direct_abstract_declarator T_LSQUAREBRACKET T_RSQUAREBRACKET 							//{$$ = $1;} //FIX THIS
	|	direct_abstract_declarator T_LSQUAREBRACKET constant_expression T_RSQUAREBRACKET 		//{$$ = $1;} //FIX THIS
	|	T_LBRACKET T_RBRACKET 																	//{$$ = NULL;}
	|	T_LBRACKET parameter_type_list T_RBRACKET 												//{$$ = $2;} // FIX THIS
	|	direct_abstract_declarator T_LBRACKET T_RBRACKET 										//{$$ = $1;} // FIX THIS
	|	direct_abstract_declarator T_LBRACKET parameter_type_list T_RBRACKET               		//{$$ = $1;} // FIX THIS
;

initializer:
		assignment_expression									{$$ = $1;}
	|	T_LCURLBRACKET initializer_list T_RCURLBRACKET 			//{$$ = $2;}
	|	T_LCURLBRACKET initializer_list T_COMMA T_RCURLBRACKET	//{$$ = $2;}
;

initializer_list:
		initializer 											//{$$ = $1;} // IDK YET LOL
	|	initializer_list T_COMMA initializer 					//{$$ = $3;} // IDK YET LOL
;

statement:
		labeled_statement										{$$ = $1;}
	|	compound_statement										{$$ = $1;}
	|	expression_statement									{$$ = $1;}
	|	selection_statement										{$$ = $1;}
	|	iteration_statement										{$$ = $1;}
	|	jump_statement											{$$ = $1;}
;

labeled_statement:
		IDENTIFIER T_COMMA statement 							//{$$ = $3;}  // Don't need to support this, as related to GOTO
	|	T_CASE constant_expression T_COMMA statement     		//{$$ = $4;} // Don't need to support this, as related to GOTO
	|	T_DEFAULT T_COMMA statement 							//{$$ = $3;} // Don't need to support this, as realted to GOTO 
;


compound_statement:
		T_LCURLBRACKET T_RCURLBRACKET 						{$$ = new CompoundStmt(NULL);}
	|	T_LCURLBRACKET declaration_or_statement_list T_RCURLBRACKET {$$ = new CompoundStmt($2);}
;


declaration_or_statement_list:
		declaration_or_statement 								{std::vector<Statement*>* Statements = new std::vector<Statement*>; Statements->push_back($1); $$ = Statements;}
	|	declaration_or_statement_list declaration_or_statement 	{$1->push_back($2); $$ = $1;}
;

declaration_or_statement:
		statement 					{$$ = $1;}
	|	declaration 				{$$ = $1;}
;

expression_statement:
		T_SEMICOLON					{$$ = NULL;}
	|	expression T_SEMICOLON 		{$$ = $1;}
;

selection_statement:
		T_IF T_LBRACKET expression T_RBRACKET statement  													{$$ = new IfElse($3, $5, NULL);} 
	|	T_IF T_LBRACKET expression T_RBRACKET statement T_ELSE statement 									{$$ = new IfElse($3, $5, $7);} 
	|	T_SWITCH T_LBRACKET expression T_RBRACKET statement       											{$$ = $3;} //Currently don't support
;

iteration_statement:
		T_WHILE T_LBRACKET expression T_RBRACKET statement     												{$$ = new While($3, $5);} 
	|	T_DO statement T_WHILE T_LBRACKET expression T_RBRACKET 											{$$ = $5;} //Currently don't support
	|	T_FOR T_LBRACKET expression_statement expression_statement T_RBRACKET statement 					{$$ = $3;} //Currently don't support
	|	T_FOR T_LBRACKET expression_statement expression_statement expression T_RBRACKET statement 			{$$ = $4;} //Currently don't support
;


jump_statement:
		T_RETURN T_SEMICOLON 									{$$ = new ReturnStmt(NULL);}
	|	T_RETURN expression T_SEMICOLON 						{$$ = new ReturnStmt($2);}
	|	T_BREAK T_SEMICOLON										//{$$ = new ReturnStmt(NULL);}		//Currently don't support
	|	T_CONTINUE T_SEMICOLON									//{$$ = new ReturnStmt(NULL);}		//Currently don't support
	|	T_GOTO IDENTIFIER T_SEMICOLON							//{$$ = $2;}  // Don't need to support GOTO
;

constant_expression:
		conditional_expression									{$$ = $1;}
;

expression:
		assignment_expression 									{$$ = $1;}
	|	expression T_COMMA assignment_expression				{$$ = $3;}   // Don't need to support comma
;

assignment_expression:
		conditional_expression									{$$ = $1;}
	|	unary_expression assignment_operator assignment_expression	{$$ = new AssignmentExpr($1, $3, *$2);}   
;

assignment_operator:
		T_ASSIGN 												{$$ = $1;}
	|	T_MULTASSIGN											{$$ = $1;}
	|	T_DIVIDEASSIGN											{$$ = $1;}
	|	T_MODULOASSIGN 											{$$ = $1;}
	|	T_PLUSASSIGN											{$$ = $1;}
	|	T_MINUSASSIGN											{$$ = $1;}
	|	T_ORASSIGN												{$$ = $1;}
	|	T_ANDASSIGN												{$$ = $1;}
	|	T_XORASSIGN												{$$ = $1;}
	|	T_LSHFTASSIGN											{$$ = $1;}
	|	T_RSHFTASSIGN											{$$ = $1;}
;

conditional_expression:
		logical_or_expression																	{$$ = $1;}
	|	logical_or_expression T_QUESTIONMARK expression T_COLON conditional_expression 			{$$ = new CondOperator($1, $3, $5);}
;
 
logical_or_expression:
		logical_and_expression											{$$ = $1;}
	|	logical_or_expression T_OR logical_and_expression 				{$$ = new Operator($1, $3, *$2);}
;

logical_and_expression:
		inclusive_or_expression											{$$ = $1;}
	|	logical_and_expression T_AND inclusive_or_expression 			{$$ = new Operator($1, $3, *$2);}
;

inclusive_or_expression:
		exclusive_or_expression											{$$ = $1;}
	|	inclusive_or_expression T_BITOR exclusive_or_expression 		{$$ = new Operator($1, $3, *$2);}
;

exclusive_or_expression:
		and_expression													{$$ = $1;}
	|	exclusive_or_expression T_BITXOR and_expression 				{$$ = new Operator($1, $3, *$2);}
;

and_expression:
		equality_expression												{$$ = $1;}
	|	and_expression T_BITAND equality_expression 					{$$ = new Operator($1, $3, *$2);}
;

equality_expression:
		relational_expression											{$$ = $1;}
	|	equality_expression T_EQUAL relational_expression 				{$$ = new Operator($1, $3, *$2);}
	|	equality_expression T_UNEQUAL relational_expression 			{$$ = new Operator($1, $3, *$2);}
;

relational_expression:
		shift_expression												{$$ = $1;}
	|	relational_expression T_GREATER shift_expression 				{$$ = new Operator($1, $3, *$2);}
	|	relational_expression T_GREATEREQ shift_expression				{$$ = new Operator($1, $3, *$2);}
	|	relational_expression T_LESSER shift_expression 				{$$ = new Operator($1, $3, *$2);}
	|	relational_expression T_LESSEREQ shift_expression 				{$$ = new Operator($1, $3, *$2);}
;

shift_expression:
		additive_expression												{$$ = $1;}
	|	shift_expression T_BITLSHFT additive_expression				{$$ = new Operator($1, $3, *$2);}
	|	shift_expression T_BITRSHFT additive_expression 				{$$ = new Operator($1, $3, *$2);}
;

additive_expression:
		multiplicative_expression										{$$ = $1;}
	|	additive_expression T_PLUS multiplicative_expression 	 		{$$ = new Operator($1, $3, *$2);}
	|	additive_expression T_MINUS multiplicative_expression			{$$ = new Operator($1, $3, *$2);}
;

multiplicative_expression:
		cast_expression											{$$ = $1;}
	|	multiplicative_expression T_MULT cast_expression 		{$$ = new Operator($1, $3, *$2);}
	|	multiplicative_expression T_DIVIDE cast_expression 		{$$ = new Operator($1, $3, *$2);}
	|	multiplicative_expression T_MODULO cast_expression 		{$$ = new Operator($1, $3, *$2);}
;

cast_expression:
		unary_expression 										{$$ = $1;}
	|	T_LBRACKET type_name T_RBRACKET cast_expression 		{$$ = $4;}
;

unary_expression:
		postfix_expression										{$$ = $1;}
	|	T_INCREMENT unary_expression							{$$ = new Unary($2, *$1);}
	|	T_DECREMENT unary_expression 							{$$ = new Unary($2, *$1);}
	|	unary_operator cast_expression 							{$$ = new Unary($2, *$1);} 
	|	T_SIZEOF unary_expression 								{$$ = new Unary($2, *$1);}
	|	T_SIZEOF T_LBRACKET type_name T_RBRACKET 				//{$$ = new Unary($2, *$1);}
;

unary_operator:
		T_BITAND 												{$$ = $1;}
	|	T_MULT 													{$$ = $1;}
	|	T_PLUS 													{$$ = $1;}
	|	T_MINUS 												{$$ = $1;}
	|	T_BITCOMP 												{$$ = $1;}
	|	T_NOT 													{$$ = $1;}
;

postfix_expression:
		primary_expression													{$$ = $1;}
	|	postfix_expression T_LSQUAREBRACKET expression T_RSQUAREBRACKET		{$$ = $1;} //Fix this
	|	postfix_expression T_LBRACKET T_RBRACKET 							{$$ = $1;} //Fix this
	|	postfix_expression T_LBRACKET argument_expression_list T_RBRACKET 	{$$ = $1;} //Fix this
	|	postfix_expression T_ACCESS IDENTIFIER 								{$$ = $1;} //Fix this
	|	postfix_expression T_POINTERACCESS IDENTIFIER 						{$$ = $1;} //Fix this
	|	postfix_expression T_INCREMENT									{$$ = $1;} //Fix this
	|	postfix_expression T_DECREMENT 										{$$ = $1;} //Fix this
;

argument_expression_list:
		assignment_expression 												
		argument_expression_list T_COMMA assignment_expression 				{$$ = $3;} //Fix this

primary_expression:
		IDENTIFIER												{$$ = new FakeVariable(*$1);}
	|	INT_CONST												{$$ = new Number(stoi(*$1));}
	|	FLOAT_CONST    											//{$$ = new Constant{$1, FloatType};}
	|	CHAR_CONST   											//{$$ = new Constant{$1, CharType };}
	|	STRING_CONST											//{$$ = new Constant{$1, StringType};}
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
