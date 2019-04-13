%{
 #include<math.h>
 #include<stdio.h>
 #include<stdlib.h>
 
 void yyerror(char *);
 int yylex();
 int fact(int);
%}
%union { double p; }
%token<p>NUM VAR
%left '+' '-'
%left '*' '/'
%right '^'
%left '!'
%nonassoc UMINUS
%type<p>E

%%
S	: E {printf("\nResult %g",$1); }
E	: NUM { $$=$1; }
	| E '+' E {$$=$1 + $3;}
	| E '-' E {$$=$1 - $3;}
	| '-' E {$$=-$2;} %prec UMINUS
	| E '!' {$$= fact($1); }
	;
%%

int main()
{
	do
	{
		yyparse();
	}while(1);
}

void yyerror(char *str)
{
	fprintf(stderr,"%s",str);
}
int fact(int f)
{
	if(f<=0)
		return 1;
	return f*fact(f-1);
}
