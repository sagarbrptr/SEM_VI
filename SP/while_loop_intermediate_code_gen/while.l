%{
 #include "y.tab.h"
 #include<math.h>
%}

ALPHA [a-zA-z]
DIGIT [0-9]

%%

while {return WHILE; }
{ALPHA}({ALPHA}|{DIGIT})* {	return ID; }

{DIGIT}*	{ yylval=atoi(yytext);	return NUM; }

[\n] {return 0;}
. {return yytext[0]; }

%%
