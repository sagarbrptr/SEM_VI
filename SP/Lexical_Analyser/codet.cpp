#include<bits/stdc++.h>
#define pb push_back
using namespace std;

struct LITTAB
{
 	string literal;
};

struct UST
{
	string token;
	string type;
	int index;
};

struct IDENTIFIER
{
	string identifier;
};

vector<UST> ust;
vector<LITTAB> lit_tab;
vector<string> ter_list;
vector<IDENTIFIER> idn_tab;
int LC;
struct TERMINAL
{
	string terminal;
};
vector<TERMINAL> ter_tab;
void terminal_read()
{
	ifstream source ("terminal");
	
	if(source.is_open())
    	{    	
    		string line; 
    		while(getline( source, line ))
    		{
    			TERMINAL t;
    			t.terminal=line;
			ter_list.pb(line);
		}
	}
	source.close();
}

int insert_lit(string s)
{
	if(s[0]==' '||s=="\t"||s=="\n")	return -1;
	LITTAB l;
	l.literal=s;
	int ct=0;
	for(auto i:lit_tab)
	{	
		if(i.literal==s)
			return ct;
		ct++;
	}
	lit_tab.pb(l);
	return ct;
}
int insert_idn(string s)
{
	if(s[0]==' '||s=="\t"||s=="\n")	return -1;
	IDENTIFIER I;
	I.identifier=s;
	int ct=0;
	for(auto i:idn_tab)
	{	
		if(i.identifier==s)
			return ct;
		ct++;
	}
	idn_tab.pb(I);
	return ct;
} 
int ister(string s)
{
	int ct=0;
	for(auto i:ter_list)
	{
		if(i==s)
			return ct;
		ct++;
	}
	return -1;
}
bool isidn(string s)
{
	if(s=="")
		return false;
	if(s[0]>='0' && s[0]<='9')
		return false;
	return true;
}
void insert_ust(string s,int ln,string type)
{
	if(s[0]==' '||s=="\t"||s=="\n")	return;
	UST temp;
	temp.token=s;
	temp.type=type;
	temp.index=ln;
	ust.pb(temp);
}
void print_ust()
{
	for(auto i:ust)
		cout<<i.token<<" "<<i.type<<" "<<i.index<<"\n";
}
void print_ter()
{
	int cnt=0;
	for(auto i:ter_list)
		cout<<cnt++<<" "<<i<<"\n";
}
void print_idn()
{
	int cnt=0;
	for(auto i:idn_tab)
		cout<<cnt++<<" "<<i.identifier<<"\n";
}
void print_lit()
{
	int cnt=0;
	for(auto i:lit_tab)
		cout<<cnt++<<" "<<i.literal<<"\n";
}
int main()
{	
	terminal_read();
	//print_ter();
	string line,s="";
	ifstream source ("source_code");
    bool multiline_comment=0,is_string_literal=0;
    string string_literal="";

    	if(source.is_open())
    	{    	
    		string line; 
    		while(getline( source, line ))
    		{
				cout<<line<<"\n";
			
				for(int i=0;i<line.size();i++)
				{
					if(multiline_comment)
					{
						while(i<line.size()-1)
						{
							if(line[i]=='*' && line[i+1]=='/')
							{
								multiline_comment=0;
								i++;
								break;
							}
							i++;
						}
						if(i==line.size()-1)
							break;
					}
					if(is_string_literal)
					{
						while(i<line.size())
						{
							if(line[i]=='"' || line[i]=='\'')
							{
								is_string_literal=0; // "Hey codeforce " 'H'
								int ind=insert_lit(string_literal);	//insert literal to LITTAB
								insert_ust(string_literal,ind,"LIT");
								ind=ister("\"");
								insert_ust("\"",ind,"TRM");
								i++;
								break;	
							}
							string_literal+=line[i++];
						}
						if(i==line.size())
							break;
					}
					string temp="";
					temp+=line[i];
					int trm_ind=ister(temp);
					if(trm_ind!=-1)
					{
						//terminated 
						if(s!="")
						{
							int key=ister(s);//keyword int,float
							if(key!=-1)
							{
								insert_ust(s,key,"TRM");
							}
							else if(isidn(s))
							{
								int ind=insert_idn(s);
								insert_ust(s,ind,"IDT");
							}
							else
							{
								int ind=insert_lit(s);
								insert_ust(s,ind,"LIT");	
							}
						}
						if(i+1<line.size() )
						{
							string temp2=temp;
							temp2+=line[i+1];
							if(temp2=="//")//comment neglect the line
								break;
							else if(temp2=="/*")
							{	
								multiline_comment=1;
								i++;
								continue;
							}
							int ind=ister(temp2);	//++
							if(ind!=-1)
							{
								insert_ust(temp2,ind,"TRM");
								i++;
							}
							else
							{
								insert_ust(temp,trm_ind,"TRM");	
								if(temp=="\"" || temp=="'")
								{
									is_string_literal=1; // "Hey codeforce " 'H'
									string_literal="";	//initialize literal to NULL	
								}
							}
						}
						else
						{
							insert_ust(temp,trm_ind,"TRM");
							if(temp=="\"" || temp=="'")
							{
								is_string_literal=1; // "Hey codeforce " 'H'
								string_literal="";	//initialize literal to NULL	
							}
						}
						s="";
					}
					else	s+=line[i];
				}
				if(s!="")
				{
					int key=ister(s);//keyword int,float
					if(key!=-1)
					{
						insert_ust(s,key,"TRM");
					}
					else if(isidn(s))
					{
						int ind=insert_idn(s);
						insert_ust(s,ind,"IDT");
					}
					else
					{
						int ind=insert_lit(s);
						insert_ust(s,ind,"LIT");	
					}
				}
			}
		}
		source.close();
		cout<<"\nUST TABLE\n";
		print_ust();
		cout<<"\nIDENTIFIER TABLE\n";
		print_idn();
		cout<<"\nLITERAL TABLE\n";
		print_lit();						
}
