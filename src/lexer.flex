%option noyywrap

%{
	#include "parser.tab.hpp"
	extern "C" int fileno(FILE *stream);

%}

LETTER			[a-zA-Z]
NONDIGIT		[a-zA-Z_]
DIGIT 			[0-9]
HEXDIGIT		[0-9a-fA-F]
OCTDIGIT		[0-7]
INTEGER_SUFFIX	([lL]?[uU])|([lL][uU]?)
DECCONSTANT		([0])|([1-9][0-9]*)
HEXCONSTANT		[0][xX][0-9a-fA-F]*
OCTCONSTANT		[0][0-7]+
SIMPLE_ESCAPE	[\'\"\?\\\a\b\f\n\r\t\v]
OCT_ESCAPE		[\\{OCTDIGIT}{3}]
HEX_ESCAPE		[\\x{HEXDIGIT}+]
ESCAPE_SEQ		[{SIMPLE_ESCAPE}|{OCT_ESCAPE}|{HEX_ESCAPE}]
CHAR_SEQ		[[^(\'\\\N)]|ESCAPE_SEQ]+
SCHAR_SEQ		[ESCAPE_SEQ]|[^(\"\\\N)]+
IDENTIFIER 		[a-zA-Z][a-zA-Z0-9_]*

WHITESPACE		[ ]
TAB 			[\t]
NEWLINE			[\n\r]
EVERYTHING_ELSE	[.]

%%

auto			{yylval.string = new std::string(yytext); return T_AUTO;}
break			{yylval.string = new std::string(yytext); return T_BREAK;}
case			{yylval.string = new std::string(yytext); return T_CASE;}
char			{yylval.string = new std::string(yytext); return T_CHAR;}
const			{yylval.string = new std::string(yytext); return T_CONST;}
continue		{yylval.string = new std::string(yytext); return T_CONTINUE;}
default			{yylval.string = new std::string(yytext); return T_DEFAULT;}
do				{yylval.string = new std::string(yytext); return T_DO;}
double			{yylval.string = new std::string(yytext); return T_DOUBLE;}
else			{yylval.string = new std::string(yytext); return T_ELSE;}
enum			{yylval.string = new std::string(yytext); return T_ENUM;}
extern			{yylval.string = new std::string(yytext); return T_EXTERN;}
float			{yylval.string = new std::string(yytext); return T_FLOAT;}
for				{yylval.string = new std::string(yytext); return T_FOR;}
goto			{yylval.string = new std::string(yytext); return T_GOTO;}
if				{yylval.string = new std::string(yytext); return T_IF;}
int 			{yylval.string = new std::string(yytext); return T_INT;}
long			{yylval.string = new std::string(yytext); return T_LONG;}
register		{yylval.string = new std::string(yytext); return T_REGISTER;}
return			{yylval.string = new std::string(yytext); return T_RETURN;}
short			{yylval.string = new std::string(yytext); return T_SHORT;}
signed			{yylval.string = new std::string(yytext); return T_SIGNED;}
sizeof			{yylval.string = new std::string(yytext); return T_SIZEOF;}
static			{yylval.string = new std::string(yytext); return T_STATIC;}
struct			{yylval.string = new std::string(yytext); return T_STRUCT;}
switch			{yylval.string = new std::string(yytext); return T_SWITCH;}
typedef			{yylval.string = new std::string(yytext); return T_TYPEDEF;}
union			{yylval.string = new std::string(yytext); return T_UNION;}
unsigned		{yylval.string = new std::string(yytext); return T_UNSIGNED;}
void			{yylval.string = new std::string(yytext); return T_VOID;}
volatile		{yylval.string = new std::string(yytext); return T_VOLATILE;}
while			{yylval.string = new std::string(yytext); return T_WHILE;}



\+ 				{yylval.string = new std::string(yytext); return T_PLUS;}
\- 				{yylval.string = new std::string(yytext); return T_MINUS;}
\* 				{yylval.string = new std::string(yytext); return T_MULT;}
\/ 				{yylval.string = new std::string(yytext); return T_DIVIDE;}
\% 				{yylval.string = new std::string(yytext); return T_MODULO;}
\++ 			{yylval.string = new std::string(yytext); return T_INCREMENT;}
\-- 			{yylval.string = new std::string(yytext); return T_DECREMENT;}

\=\=				{yylval.string = new std::string(yytext); return T_EQUAL;}
\!\= 			{yylval.string = new std::string(yytext); return T_UNEQUAL;}
\> 				{yylval.string = new std::string(yytext); return T_GREATER;}
\< 				{yylval.string = new std::string(yytext); return T_LESSER;}
\>\= 			{yylval.string = new std::string(yytext); return T_GREATEREQ;}
\<\= 			{yylval.string = new std::string(yytext); return T_LESSEREQ;}


\&\& 			{yylval.string = new std::string(yytext); return T_AND;}
\|\| 			{yylval.string = new std::string(yytext); return T_OR;}
\!				{yylval.string = new std::string(yytext); return T_NOT;}

\& 				{yylval.string = new std::string(yytext); return T_BITAND;}
\| 				{yylval.string = new std::string(yytext); return T_BITOR;}
\^ 				{yylval.string = new std::string(yytext); return T_BITXOR;}
\~ 				{yylval.string = new std::string(yytext); return T_BITCOMP;}
\<\<				{yylval.string = new std::string(yytext); return T_BITLSHFT;}
\>\>				{yylval.string = new std::string(yytext); return T_BITRSHFT;}

\= 				{yylval.string = new std::string(yytext); return T_ASSIGN;}
\+\= 			{yylval.string = new std::string(yytext); return T_PLUSASSIGN;}
\-\=				{yylval.string = new std::string(yytext); return T_MINUSASSIGN;}
\*\= 			{yylval.string = new std::string(yytext); return T_MULTASSIGN;}
\/\= 			{yylval.string = new std::string(yytext); return T_DIVIDEASSIGN;}
\%\= 			{yylval.string = new std::string(yytext); return T_MODULOASSIGN;}
\<\<\= 			{yylval.string = new std::string(yytext); return T_LSHFTASSIGN;}
\>\>\= 			{yylval.string = new std::string(yytext); return T_RSHFTASSIGN;}
\&\= 			{yylval.string = new std::string(yytext); return T_ANDASSIGN;}
\^\= 			{yylval.string = new std::string(yytext); return T_XORASSIGN;}
\|\= 			{yylval.string = new std::string(yytext); return T_ORASSIGN;}

\{				{yylval.string = new std::string(yytext); return T_LCURLBRACKET;}
\}				{yylval.string = new std::string(yytext); return T_RCURLBRACKET;}
\[				{yylval.string = new std::string(yytext); return T_LSQUAREBRACKET;}
\]				{yylval.string = new std::string(yytext); return T_RSQUAREBRACKET;}
\(				{yylval.string = new std::string(yytext); return T_LBRACKET;}
\)				{yylval.string = new std::string(yytext); return T_RBRACKET;}

\.				{yylval.string = new std::string(yytext); return T_ACCESS;}
\-\>			{yylval.string = new std::string(yytext); return T_POINTERACCESS;}

\;				{yylval.string = new std::string(yytext); return T_SEMICOLON;}
\:				{yylval.string = new std::string(yytext); return T_COLON;}
\?				{yylval.string = new std::string(yytext); return T_QUESTIONMARK;}
\,				{yylval.string = new std::string(yytext); return T_COMMA;}
\.\.\.			{yylval.string = new std::string(yytext); return T_ELLIPSIS;}

{IDENTIFIER}	{yylval.string = new std::string(yytext); return IDENTIFIER;}


{DECCONSTANT}{INTEGER_SUFFIX}?		{yylval.string = new std::string(yytext); return INT_CONST;}
{HEXCONSTANT}{INTEGER_SUFFIX}?		{yylval.string = new std::string(yytext); return INT_CONST;}
{OCTCONSTANT}{INTEGER_SUFFIX}?		{yylval.string = new std::string(yytext); return INT_CONST;}
{DIGIT}+[eE][+-]?{DIGIT}*[FLfl]?	{yylval.string = new std::string(yytext); return FLOAT_CONST;}
{DIGIT}+[.]{DIGIT}*[eE][+-]?{DIGIT}*]?[FLfl]?					{yylval.string = new std::string(yytext); return FLOAT_CONST;}
{DIGIT}+[.]{DIGIT}[FLfl]?					{yylval.string = new std::string(yytext); return FLOAT_CONST;}
[L]?['][^(\'\\\n)|ESCAPE_SEQ]+[']				{yylval.string = new std::string(yytext); return CHAR_CONST;}
L?\"(\\.|[^\\"])*\"			{yylval.string = new std::string(yytext); return STRING_CONST;}
[ \t\r\n]+		{;}
.				{fprintf(stderr, yytext); fprintf(stderr, "Not in lexer \n"); exit(1);}

%%

void yyerror (char const *s)
{
  fprintf (stderr, "Flex Error: %s\n", s);
  exit(1);
}
