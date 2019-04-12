/*
 * ASSIGNMENT 67: LEX FILE to generate Intermediate code using LEX &YACC for Control Flow statement for 'WHILE' loop
   Roll no : 3019
   Name : Ashutosh Danwe
   Batch : k-10
   Department : TE-IT
*/


	// DECLARATIONS

%{

	#include <stdio.h>
	#include "y.tab.h"

%}


ALPHA [a-zA-Z]
DIGIT [0-9]


	// DEFINATIONS

%%

while				return WHILE;

{ALPHA}({ALPHA}|{DIGIT})*	return ID;

{DIGIT}+			{ yylval = atoi ( yytext ); return NUM; }

[ \t]				;

\n				yyterminate ();

.				return yytext[0];

%%
