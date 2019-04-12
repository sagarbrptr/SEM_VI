%{
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
	int yylex();
	int yyerror();
	int factorial(int);
%}
%union	//TO define possible symbol types
{ double p; }
%token<p>NUM
%token SIN COS TAN LOG SQUARE SQRT CUBE
//Defining precedence and Associativity
%left '+' '-'	//Lowest precedence and left associativity
%left '*' '/'
%left '!'
%nonassoc UMINUS	//No associativity
%type<p>exp		//Sets the type for non-terminals
%%
S	:	exp	{printf("Result is=%g\n",$1); }	//For printing Result
exp	:	exp '+' exp {$$ = $1 + $3; }
	|	exp '-' exp {$$ = $1 - $3; }
	|	exp '*' exp {$$ = $1 * $3; }
	|	exp '/' exp {if($3==0)
			     {
			     printf("\n-----Divide by Zero error-----");
			     exit(0);
			     }
			     else $$ = $1 / $3; 
			    }
	|	'-' exp {$$ = -$2; }
	|	'(' exp ')' {$$ = $2; }
	|	SIN '(' exp ')' {$$ = sin($3); }
	|	COS '(' exp ')' {$$ = cos($3); }
	|	TAN '(' exp ')' {$$ = tan($3); }
	|	LOG '(' exp ')' {$$ = log($3); }
	|	SQRT '(' exp ')' {$$ = sqrt($3); }
	|	SQUARE '(' exp ')' {$$ = $3 * $3; }
	|	CUBE '(' exp ')' {$$ = $3 * $3 * $3; }
	|	NUM {$$ = $1; }
	| 	exp '!' {$$ = factorial($1);}
%%
int main()
{
	do
	{
		printf("\nEnter the Expression:->");
		yyparse();
	}while(1);
}
int factorial(int num)
{
if(num>1)
	return num*factorial(num-1);
else
	return 1;
}
int yyerror()
{
}
int yywrap()
{
return 1;
}
