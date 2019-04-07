#include<bits/stdc++.h>
#define pb push_back
using namespace std;

struct IDENTIFIER
{
	char identifier[50];
};
struct TERMINAL
{
	string terminal;
	int delimiter;
};

struct LITTAB
{
 	string literal;
};

struct UST
{
	string token;
	string type;
	int index;
	int line_number;
};

int LN=0;
vector<UST> ust;
vector<LITTAB> lit_list;
vector<TERMINAL> ter_list;
vector<IDENTIFIER> iden_list;

int ter_find(string f)
{
	for(int i=0;i<ter_list.size();i++)
		if(ter_list[i].terminal==f)
			return i;
	return -1;
}
vector<string> parse(string line)
{
	vector<string> ans;
	string word = ""; 
   	for (auto x : line) 
   	{ 
		if (x == ' ') 
        { 
           ans.pb(word); 
           word = ""; 
       	} 
       	else
       	{ 
           word = word + x; 
       	} 
   }  
   if(word!="")	ans.pb(word);
   return ans;
} 
int isop(string temp)
{
	string a[]={"+","-","=","++"};
	for(int i=0;i<3;i++)
	{
		if(a[i]==temp)	return i;
	}
	return -1;
}
void insert_UST(string temp_token,string temp_type,int ind)
{
	UST temp;
	temp.token=temp_token;
	temp.type=temp_type;
	temp.index=ind;
	temp.line_number=LN;
	ust.pb(temp);
}
/*
void insert_UST(char l[],int ln)
{
	UST temp;
	strcpy(temp.lexim,l);
	temp.line_number=ln;
	for(auto i:key_list)
	{
		if(!strcmp(i.keyword,l))
		{
			strcpy(temp.type,i.token);
			ust.pb(temp);
			return;
		}
	}	
	for(auto i:symtab)
	{
		if(!strcmp(i.symbol,l))
		{
			strcpy(temp.type,"ST");
			ust.pb(temp);
			return;
		}
	}
	SYMTAB t;
	strcpy(t.symbol,l);
	symtab.pb(t);
	strcpy(temp.type,"ST");
	ust.pb(temp);
}
void read_ter()
{
	FILE *fp=fopen("terminal","r");
	
	while(!feof(fp))
	{
		char buffer[200];
		fgets(buffer,300,fp);

		TERMINAL t;

		sscanf(buffer, "%s %s", t.terminal,t.delimiter);
		
		ter_list.pb(t);
	}
	fclose(fp);
	
	fp=fopen("keyword","r");
	
	while(!feof(fp))
	{
		char buffer[200];
		fgets(buffer,300,fp);

		KEYWORD k;

		sscanf(buffer, "%s %s", k.keyword,k.token);
		
		key_list.pb(k);
	}
	fclose(fp);
}
char* to_arr(char c)
{
	char* temp=(char*)malloc(sizeof(char)*2);
	temp[0]=c;
	temp[1]='\0';
	return temp;
}
void print_ust()
{
	for(auto i:ust)
		cout<<i.lexim<<" "<<i.type<<" "<<i.line_number<<"\n";
}*/
int main()
{
   // FILE *source, *destin;
    ifstream source ("source_code");
    //read_ter();
    if(source.is_open())
    {    	
    	string line; 
    	while(getline( source, line ))
    	{
			cout<<line;
			int i=0;
			vector<string> buffer=parse(line);
			for(int i=0;i<buffer.size();i++)
			{
				string s=buffer[i];
				
				int ind=isop(s);	//one length
				
				if(ind!=-1)
				{
					if(i+1<buffer.size())
					{
						string d=s+buffer[i+1];
						int ind2=isop(d);
						if(ind2!=-1)
						{
							insert_UST(d,"OP",ind2);
							continue;
						}	
					}
					insert_UST(s,"OP",ind);
					continue;
				}
				
				
				
				
			/*while(i<strlen(buffer))
			{
				char temp[50];
				int temp_ptr=0;
				
				while(i<strlen(buffer) &&( buffer[i]!=' ' || !ter_find(to_arr(buffer[i]))))
				{
					temp[temp_ptr++]=buffer[i];
					i++;
				}
				temp[temp_ptr]='\0';
				insert_UST(temp,LN);
				i++;
			}*/
			LN++;
		}
	}
	source.close();
	//print_ust();
}
			
