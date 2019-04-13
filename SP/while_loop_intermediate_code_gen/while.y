%{
 #include<stdio.h>
 #include<math.h>
 #include<stdlib.h>
 #include<string.h>
 
	int yylex();
	void push();
	void codegen();
	void codegen_assign();
	void codegen_uminus();
	void f1(),f2(),f3();
	int start=1,lnum=1,top=0;
	char st[100][10];	//stack
	char i_[2]="0";
	char temp[2]="t";
	char * yytext;
	void yyerror();
%}
%token ID NUM WHILE
%right '='
%left '+' '-'
%left '*' '/'
%left UMINUS
%%

S	:	WHILE { f1(); } '(' E ')' { f2(); } E ';' { f3(); }
	;
E	:	V '=' { push(); } E { codegen_assign(); }
	|	E '+' { push(); } E { codegen(); }
	|	E '-' { push(); } E { codegen(); }
	|	E '*' { push(); } E { codegen(); }
	|	E '/' { push(); } E { codegen(); }
	|	'(' E ')'	
	|	'-' { push(); } E { codegen_uminus(); } %prec UMINUS
	|	V
	|	NUM { push(); }
	;

V	:	ID { push(); }
	;
	
%%

void push()
{
	strcpy(st[++top],yytext);
}

void codegen()
{
	strcpy(temp,"t");
	strcat(temp,i_);
	printf("\n%s = %s %s %s ",temp,st[top-2],st[top-1],st[top]);
	top-=2;
	strcpy(st[top],temp);
	i_[0]++;
}

void codegen_assign()
{
	printf("\n%s = %s",st[top-2],st[top]);
	top-=2;
}
void codegen_uminus()
{
	strcpy(temp,"t");
	strcat(temp,i_);
	printf("\n%s = - %s",temp,st[top]);
	top--;
	strcpy(st[top],temp);
	i_[0]++;
}

void f1()
{
	printf("\nL%d :",lnum++);
}
void f2()
{
	strcpy(temp,"t");
	strcat(temp,i_);
	printf("\n%s = not %s",temp,st[top]);
	printf("\n if %s goto L%d",temp,lnum);
	i_[0]++;
}
void f3()
{
	printf("\n goto L%d",start);
	printf("\n L%d",lnum);
}

int main()
{
	yyparse();
}
void yyerror()
{
}

/* lex while.l 
yacc -d while.y 
gcc lex.yy.c y.tab.c -ll -lm
*/
