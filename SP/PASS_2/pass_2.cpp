#include <bits/stdc++.h>
#define pb push_back
using namespace std;

struct SYMTAB
{
	char symbol[200];
	int address;
	int length;
	SYMTAB()
	{
		symbol[0]='\0';
		address=0;
		length=0;
	}
};
struct LITTAB
{
 	char value[20];
	int address;
	LITTAB()
	{
		value[0]='\0';
		address=0;
	}
};

vector<SYMTAB>symtab;
vector<LITTAB>littab;

void init_tables()
{
	
	FILE *fp=fopen("symtab","r");
	while(!feof(fp))
	{
		char buffer[200];
		fgets(buffer,300,fp);
		
		SYMTAB m;

		sscanf(buffer, "%s %d %d", m.symbol,&m.address,&m.length);
		
		symtab.pb(m);
	}
	fclose(fp);
	if(symtab.size()>0)
		symtab.pop_back();
	//for(auto i:symtab)	cout<<i.symbol<<" "<<i.address<<" "<<i.length<<"\n";	
	fp=fopen("littab","r");
	while(!feof(fp))
	{
		char buffer[200];
		fgets(buffer,300,fp);
		
		LITTAB m;

		sscanf(buffer, "%s %d", m.value,&m.address);
		
		littab.pb(m);
	}
	if(littab.size()>0)
		littab.pop_back();
	//for(auto i:littab)	cout<<i.value<<" "<<i.address<<"\n";	
	fclose(fp);
}

int main()
{
	init_tables();
	FILE *source,*destin;
	source = fopen("intermediate_code", "r");
    	destin = fopen("pass2_op", "w");
    	
    	while(!feof(source))
    	{    	
    		char buffer[200];
		fgets(buffer,300,source);

		char LC[20],type[20],reg[20],L_S[20];

		sscanf(buffer, "%s %s %s %s", LC, type, reg, L_S);   // for now give -
		
		if(type[1]=='A')	//AD
			continue;
		
		if(type[1]=='I')	//IS
		{
			if(reg[0]=='-')	//STOP (IS,00)	- -
			{
				fprintf(destin,"%s 00 0 0\n",LC);
				continue;
			}
			int ptr=0,add;
			char temp[20];
			int j=3,k=0;		//extract ptr
			while(L_S[j]!=')')
			{
				temp[k++]=L_S[j++];
			}
			temp[k]='\0';
			
			ptr=atoi(temp);
			
			if(L_S[1]=='L')	//literal
			{
				add=littab[ptr].address;
			}
			else		//symbol
			{
				add=symtab[ptr].address;
			}
			char opcode[20];	j=4;k=0;
			while(type[j]!=')')
			{
				opcode[k++]=type[j++];
			}
			opcode[k]='\0';
			
			fprintf(destin,"%s %s %c %d\n",LC,opcode,reg[3],add);
		}
		if(type[1]=='D')	//DL class
		{
			char opcode[20];	int j=4,k=0;
			while(type[j]!=')')
			{
				opcode[k++]=type[j++];
			}
			int int_opcode=atoi(opcode);
			
			if(int_opcode==2)	//DS
			{
				fprintf(destin,"0 0 0 0\n");
			}
			else		//DC print value
			{
				j=3;k=0;
				char value[20];
				while(reg[j]!=')')
				{
					value[k++]=reg[j++];
				}
				value[k]='\0';
				fprintf(destin,"0 0 0 %s\n",value);
			}
		}
	}
	fclose(source);
	fclose(destin);
}
