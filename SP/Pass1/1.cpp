#include<bits/stdc++.h>
using namespace std;
#define f first
#define se second
struct SYMTAB
{
	int address;
	int index;
	int length;
};

struct MOT
{
	string mneumonic;
	int opcode;
	string type;
	int length;
};

struct POOLTAB
{
	int no_literals;
	int ptr;
};

struct LITTAB
{
	string value;
	int address;
};

map<string,SYMTAB> symtab;
map<string,MOT> mot;
vector<LITTAB> littab(100);
vector<POOLTAB> pooltab(100);

void read_mot()
{
	FILE* fp;
	fp=fopen("MOT","r");
	while(!feof(fp))
	{
		char mn[20],code[20],ty[20],len[20];
		fscanf(fp,"%s %s %s %s",mn,code,ty,len);
		string mnn(mn),typ(ty);
		MOT m;
		m.mneumonic=mnn;
		m.type=typ;
		m.opcode=atoi(code);
		m.length=atoi(len);
		mot[m.mneumonic]=m;
	}
	//for(auto i:mot)
	//	cout<<i.first<<" "<<i.second.mneumonic<<" "<<i.second.type<<" "<<i.second.opcode<<" "<<i.second.length<<"\n";
}
int LOC=0,symtab_index=0,PTP=0,LTP=0;
void insert_symtab(string sym,int add,int size)
{
	if(symtab.find(sym)!=symtab.end())
	{
		symtab[sym].address=add;
	}
	else 
	{
		symtab[sym].address=add;
		symtab[sym].length=size;
		symtab[sym].index=symtab_index++;
	}
}
int check_origin(string s)
{
	if(s[0]>='0' && s[0]<='9')
		return stoi(s);
	string temp="";
	int i=0;
	while(i<s.size() && s[i]!='+' && s[i]!='-')
		temp+=s[i++];
	//cout<<"\t "<<temp;
	int res=symtab[temp].address;
	temp="";
	char ch=s[i];
	i++;
	while(i<s.size())
	{
		temp+=s[i++];
	}
	//cout<<"\t"<<temp;
	if(ch=='+')
		res+=stoi(temp);
	else	res-=stoi(temp);
	return res;
}
int insert_literal(string l)
{
	for(int i=pooltab[PTP].ptr,j=0;j<pooltab[PTP].no_literals;j++,i++)
	{
		if(littab[i].value==l)
			return i;
	}
	littab[LTP].value=l;
	pooltab[PTP].no_literals++;
	return LTP++;
}
int main()
{
	read_mot();
	FILE *src;
	src=fopen("source_code","r");
	pooltab[PTP].no_literals=0;
	pooltab[PTP].ptr=0;
	while(!feof(src))
	{
		char mn[20],code[20],ty[20],len[20];
		fscanf(src,"%s %s %s %s",mn,code,ty,len);
		//fprintf(stderr, "%s %s %s %s\n",mn,code,ty,len);
		string label(mn),mneumonic(code),op1(ty),op2(len);


		if(label!="-")
		{
			insert_symtab(label,LOC,1);
		}
		if(mneumonic=="START")
		{
			if(op2!="-")
			{
				LOC=stoi(op2);
			}
			cout<<"0 (AD,01) (C,"<<LOC<<") -\n";
		}
		else if(mneumonic=="ORIGIN")
		{
			cout<<LOC<<" (AD,04) (C,";
			LOC=check_origin(op2);
			cout<<LOC<<") -\n";
		}
		else if(mneumonic=="EQU")	//doubt do we need to print anything
		{
			int add = symtab[op2].address;
			insert_symtab(label,add,1);
			cout<<LOC<<" (AD,05) -\n";
		}
		else if(mneumonic=="LTORG")
		{
			for(int i=0,j=pooltab[PTP].ptr;i<pooltab[PTP].no_literals;i++,j++)
			{
				cout<<LOC<<" (AD,03) (C,"<<littab[j].value<<") -\n";
				littab[j].address = LOC++;
			}
			PTP++;
			pooltab[PTP].ptr=LTP;
			pooltab[PTP].no_literals=0;
		}
		else if(mneumonic=="END")
		{
			cout<<LOC<<" (AD,02) - -\n";
			for(int i=0,j=pooltab[PTP].ptr;i<pooltab[PTP].no_literals;i++,j++)
			{
				cout<<LOC<<" (AD,03) (C,"<<littab[j].value<<") -\n";
				littab[j].address = LOC++;
			}
			PTP++;
			pooltab[PTP].ptr=LTP;
			pooltab[PTP].no_literals=0;	
			break;
		}
		else if(mneumonic=="DC")
		{
			cout<<LOC<<" (DL,01) (C,"<<op2<<") -\n";
			insert_symtab(label,LOC,1);
			LOC++;
		}
		else if(mneumonic=="DS")
		{
			cout<<LOC<<" (DL,02) (C,"<<op2<<") -\n";
			int sz=stoi(op2);
			insert_symtab(label,LOC,sz);
			LOC+=sz;
		}
		else if(mneumonic=="STOP")
		{
			cout<<LOC<<" (IS,00) - -\n";
			LOC+=mot["IS"].length;
		}
		else
		{
			int reg_value = 0;
			MOT itr=mot[mneumonic];
			cout<<LOC<<" ("<<itr.type<<","<<itr.opcode<<") ";
			if(op1=="AREG")
				reg_value=1;
			else if(op1=="BREG")
				reg_value=2;
			else	reg_value=3;
			cout<<"(R,"<<reg_value<<") ";
			if(op2[0]=='=')
			{
				string val="";
				for(int i=2;i<op2.size()-1;i++)
					val+=op2[i];
				
				int ind=insert_literal(val);
				cout<<" (L,"<<ind<<")\n";
			}
			else
			{
				if(symtab.find(op2)!=symtab.end())
				{
					symtab[op2].address=LOC;
				}
				else
				{
					symtab[op2].index=symtab_index++;
					symtab[op2].address=LOC;
					symtab[op2].length=1;
				}
				cout<<" (S,"<<symtab[op2].index<<")\n";
			}
			LOC+=itr.length;

		}

	}
	fclose(src);
	cout<<"\n\n";
	for(auto i:symtab)
		cout<<i.f<<" "<<i.se.address<<" "<<i.se.index<<" "<<i.se.length<<"\n";
	cout<<"\n\n";
	for(int i=0;i<LTP;i++)
		cout<<littab[i].value<<" "<<littab[i].address<<"\n";
	cout<<"\n\n";
	for(int i=0;i<PTP;i++)
		cout<<pooltab[i].ptr<<" "<<pooltab[i].no_literals<<"\n";
	cout<<"\n\n";
}
