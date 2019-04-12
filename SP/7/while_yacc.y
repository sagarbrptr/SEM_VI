/*
 * ASSIGNMENT 7 : LEX FILE to generate Intermediate code using LEX &YACC for Control Flow statement for 'WHILE' loop
   Roll no : 3019
   Name : Ashutosh Danwe
   Batch : k-10
   Department : TE-IT
*/


%{

	#include <ctype.h>
	#include <stdio.h>
	#include <string.h>
	
	char st [100][10];
	int top = 0;
	char i_[2] = "0";
	char temp[2] = "t";

	int lnum = 1;
	int start = 1;

	int yylex ();

	void push ();
	void codegen ();
	void codegen_umin ();
	void codegen_assign ();
	void lab1 ();
	void lab2 ();
	void lab3 ();

	int yyerror ();

	extern char* yytext;

%}


%token ID NUM WHILE

%right '='
%left '+' '-'
%left '*' '/'

%left UMINUS



%%

S	:	WHILE { lab1 (); } '(' E ')' { lab2 (); } E ';'  { lab3 (); }
	;
	

E	:	V '=' { push(); } E{ codegen_assign(); }
 	| 	E '+' { push(); } E{ codegen(); }
	|	E '-' { push(); } E{ codegen(); }
	|	E '*' { push(); } E{ codegen(); }
	|	E '/' { push(); } E{ codegen(); }
	|	'(' E ')'
	|	'-' {push();} E{ codegen_umin(); } %prec UMINUS
	|	V
	|	NUM { push (); }
	;


V	:	ID { push (); }
  	;


%%


void main() {

	printf("Enter the expression : ");
	yyparse ();
}

void push () {

	strcpy(st[++top],yytext);
}


void codegen () {

	strcpy(temp,"t");
	strcat(temp,i_);
	printf("%s = %s %s %s\n",temp,st[top-2],st[top-1],st[top]);
	top-=2;
	strcpy(st[top],temp);
	i_[0]++;
}

void codegen_umin () {

	strcpy(temp,"t");
	strcat(temp,i_);
	printf("%s = -%s\n",temp,st[top]);
	top--;
	strcpy(st[top],temp);
	i_[0]++;
}

void codegen_assign () {

	printf("%s = %s\n",st[top-2],st[top]);
 	top-=2;
}


void lab1 () {
	
	printf("L%d: \n",lnum++);
}


void lab2 () {

	strcpy(temp,"t");
	strcat(temp,i_);
	printf("%s = not %s\n",temp,st[top]);
	printf("if %s goto L%d\n",temp,lnum);
	i_[0]++;
}

void lab3 () {

	printf("goto L%d \n",start);
	printf("L%d: \n",lnum);
}

/*

Enter the expression : while(k=c/s)k=k*c+d;
L1: 
t0 = c / s
k = t0
t1 = not k
if t1 goto L0
t2 = k * c
t3 = t2 + d
k = t3
goto L1 
L0: 


*/


int yyerror() { }

int yywrap () { return 1; }
