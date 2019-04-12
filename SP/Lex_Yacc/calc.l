%{
#include<math.h>
#include"y.tab.h"
int yylex(void);
%}
%%
[0-9]+|[0-9]*\.[0-9]+ {	//Takes input as integer or float
				yylval.p = atof(yytext); 
				return NUM; 	//return Non-terminal
				}
sin	{return SIN; }
cos	{return COS; }	
tan	{return TAN; }	
log	{return LOG; }	
sqrt	{return SQRT; }				
cube	{return CUBE; }	//Return token CUBE to YACC
square	{return SQUARE; }	//Return token SQUARE to YACC
[\t]  ;
\n  return 0;
.  return yytext[0];
%%

