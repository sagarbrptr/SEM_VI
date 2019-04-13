#include <bits/stdc++.h>
#define pb push_back
using namespace std;

int LC = 0,PTP=0,LTP=0;            // location counter

struct MOT
{
	char mnemonic[10];
	char opcode[10];
	char type[10];
	char length[10];
	MOT()
	{
		mnemonic[0]='\0';
		opcode[0]='\0';
		type[0]='\0';
		length[0]=0;
	}
};
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
struct POOLTAB
{
	int ptr;
	int n_literals;
	POOLTAB()
	{
		ptr=n_literals=0;
	}
};
vector<SYMTAB> symtab;
vector<MOT> mot;
POOLTAB pooltab[1000];
LITTAB littab[1000];
int find_symtab(char label[])
{
	for(int i=0;i<symtab.size();i++)
	{
		if(!strcasecmp(symtab[i].symbol,label))
			return i;
	}
	return -1;
}
int insert_symtab(char label[],int add,int sz)
{
	int j=find_symtab(label);
	if(j!=-1)	return j;
	SYMTAB temp;
	strcpy(temp.symbol,label);
	temp.address=add;
	temp.length=sz;
	symtab.pb(temp);
	return symtab.size()-1;
}
MOT get_mnemonic(char mnemonic[])
{
	for(int i=0;i<mot.size();i++)
	{
		if(!strcasecmp(mot[i].mnemonic,mnemonic))
			return mot[i];
	}
	MOT null_mot;
	return null_mot;
}
int process_origin(char OP2[])
{

    if(OP2[0]>='0' && OP2[0]<='9') // if direct integer address is given
    {
        return atoi(OP2);
    }

    else
    {
        char op2[20];
        int adding_constant = 0;

        int i;
        for(i=0;i<strlen(OP2); i++)
        {
            if(OP2[i] == '+')           // loop+6
            {
                adding_constant = OP2[i+1] - '0';
                break;
            }

            else
                op2[i] = OP2[i];
        }
        op2[i] = '\0';

	for(auto i:symtab)
	{
		if ( !strcmp(op2,i.symbol))
            	{
                	return i.address + adding_constant;
		}
	}        

    }
}
void process_equ(char label[],char op2[])
{
	int ptr_label=find_symtab(label);
	
	if(isdigit(op2[0]))	//constant
	{
		int temp=atoi(op2);
		symtab[ptr_label].address=temp;
	}
	else	
	{
		int adding_constant = 0;
    		char op2_symbol[20];
		int i;
   		for(i=0;i<strlen(op2); i++)
		{
			if(op2[i] == '+')           // loop+6
			{
			    adding_constant = op2[i+1] - '0';
			    break;
			}	
			else
			    op2_symbol[i] = op2[i];
		}
		op2_symbol[i] = '\0';
		int ptr_op2=find_symtab(op2_symbol);
		
		symtab[ptr_label].address = symtab[ptr_op2].address + adding_constant;
	}
}

int insert_LITTAB(char literal[])
{
	for(int i=pooltab[PTP].ptr,j=0; j<pooltab[PTP].n_literals; j++,i++)
	{
		if(!strcmp(littab[i].value,literal))
			return i;
	}
	
	pooltab[PTP].n_literals++;
	strcpy(littab[LTP].value,literal);
	LTP++;
	return LTP-1;
	
}

int get_regvalue(char op1[])
{
	if( !strcmp(op1,"AREG") || !strcmp(op1,"areg"))
               	return 1;

        else if( !strcmp(op1,"BREG") || !strcmp(op1,"breg"))
              	return 2;
	else
		return 3;
}
void init_mot()
{
	FILE *fp=fopen("MOT","r");
	
	while(!feof(fp))
	{
		char buffer[200];
		fgets(buffer,300,fp);

		MOT m;

		sscanf(buffer, "%s %s %s %s", m.mnemonic,m.opcode,m.type,m.length);
		
		mot.pb(m);
	}
}
void print_symtab();	void print_littab();	void print_pooltab();				
int main()
{
	init_mot();
	FILE *source,*destin;
	source = fopen("source_code", "r");
    	destin = fopen("intermediate_code", "w");
	
	while(!feof(source))
    	{    	
    		char buffer[200];
		fgets(buffer,300,source);

		char mnemonic[20],label[20],op1[20],op2[20];

		sscanf(buffer, "%s %s %s %s", label, mnemonic, op1, op2);   // for now give -

		if(label[0]!='-')
		{
			//make an entry in symbol table
			
			insert_symtab(label,LC,1);	//if present don't
		}
		if(!strcasecmp(mnemonic,"LTORG"))
		{
			MOT m=get_mnemonic(mnemonic);
			fprintf(destin,"%d (%s,%s) - -\n",LC,m.type,m.opcode);
			if(pooltab[PTP].n_literals>0)
			{
				for(int i=pooltab[PTP].ptr,j=0; j<pooltab[PTP].n_literals; i++,j++)
				{
					littab[i].address=LC;
					
				}
			}
			PTP++;
			pooltab[PTP].ptr=LTP;
			
		}
		if(!strcasecmp(mnemonic,"START") )
		{
			if(op2[0]!='-')
			{
				int new_lc=atoi(op2);
				LC=new_lc;
			}
			MOT m=get_mnemonic(mnemonic); 
			fprintf(destin,"0 (%s,%s) (C,%s) -\n",m.type, m.opcode, op2);
		}
		if(!strcasecmp(mnemonic,"ORIGIN"))
		{
			int new_lc = process_origin(op2);

            		fprintf(destin,"%d (AD,04) (c,%d) -\n",LC,new_lc);
			LC = new_lc;
		}
		if(!strcasecmp(mnemonic,"EQU"))
		{
			process_equ(label,op2);
		}
		if( !strcasecmp (mnemonic, "DC") || !strcasecmp (mnemonic, "DS") ) 
		{		
			MOT m=get_mnemonic(mnemonic);
			int cur_LC=LC;
			
			int ptr_label=insert_symtab(label,LC,1);
			
			if(ptr_label!=-1)
			{
				symtab[ptr_label].address=LC;
				
				if(!strcasecmp(m.mnemonic, "DS")) //if class is DS
				{
					symtab[ptr_label].length = atoi (op2);
					LC += atoi (op2); //update location counter
				}
				else 	//if class is DC
				{	
					symtab[ptr_label].length = 1;
					LC++; //update location counter
				}
			}
				
			
			fprintf(destin,"%d (%s,%s) (C,%s) -\n", cur_LC, m.type, m.opcode, op2);
		}
		
		MOT m = get_mnemonic (mnemonic); //get mnemonic opcode
		
		if(!strcasecmp(mnemonic, "stop"))
		{
		    fprintf(destin, "%d (IS,00) - -\n",LC );
		    LC += atoi(m.length);
		}
		
		else if (!strcasecmp (m.type, "IS")) 
		{
			int cur_LC=LC;
			
			int reg=get_regvalue(op1);
			
			LC += atoi ( m.length ); //update location counter

			if ( op2 [0] == '=' ) 	//if operand is  literal
			{ 			
				char temp_op2[10];
				temp_op2[0]=op2[2];
				temp_op2[1]='\0';
				int add=insert_LITTAB(temp_op2);
				fprintf (destin,"%d (%s,%s) (R,%d) (%c,%d)\n", cur_LC, m.type, m.opcode, reg, 'L', add);

			}			
			else	//operand is symbol
			{ 
				int ptr_symbol = insert_symtab(op2,LC,1); //search for symbol

				fprintf (destin,"%d (%s,%s) (R,%d) (%c,%d)\n", cur_LC, m.type, m.opcode, reg, 'S', ptr_symbol);

			}



		}
		if(!strcasecmp(mnemonic,"END"))
		{
			if(pooltab[PTP].n_literals>0)
			{
				for(int i=pooltab[PTP].ptr,j=0; j<pooltab[PTP].n_literals; i++,j++)
				{
					littab[i].address=LC;
					
				}
			}
			PTP++;
			pooltab[PTP].ptr=LTP;
			MOT m=get_mnemonic(mnemonic);
			
			fprintf(destin,"%d (%s,%s) - -\n",LC,m.type,m.opcode);
			break;
		}
	}
	fclose(source);
	fclose(destin);
	print_symtab();	print_littab();	print_pooltab();
}

void print_symtab () 
{
	FILE *fp=fopen("symtab","w");
	for (int i=0 ; i< symtab.size() ; i++) 
		fprintf (fp, "%s %d %d\n", symtab [i].symbol, symtab [i].address, symtab [i].length);

	fclose(fp);
}

void print_littab () 
{
	FILE *fp=fopen("littab","w");
	int i=0;
	for (i=0 ; i< LTP ; i++) 
		fprintf (fp, "%s %d\n", littab [i].value, littab [i].address);

	fclose(fp);
}

void print_pooltab() {

	FILE *fp=fopen("pooltab","w");
	int i=0;
	for (i=0 ; i< PTP ; i++) 
		fprintf (fp, "%d %d\n",  pooltab [i].ptr,pooltab [i].n_literals);

	fclose(fp);

}
