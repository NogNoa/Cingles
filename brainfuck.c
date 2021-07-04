#include <stdio.h>
#include <string.h>
#define mem_size 0x8000

int brain(char mem[], char prg[]);
int fucker(char* name,char prg[]);

int main(int argc, char* argv[])
{	
	char mem[mem_size]={0}; //2^15≈32,000

	char prg[mem_size]={1,6,1,1,2,2,-1,5,0};
	
	//fucker(filename,prg)

	brain(mem,prg);
	fucker(argv[1],prg);
	//printf("%d",prg[2]);
	return 0;

}

#define stack_size 0x2000

int fucker(char* name,char prg[])
{	//FILE[plaintext]-->prg[numbers]
	//use strchr to get number from string index
	
	FILE* scroll;
	char* instruct = "><+-.,[]";
	char c;
	int PC=0;

	if (strcmp(name,"stdin"))
		scroll = stdin;
	else
		scroll = fopen(name,"r");

	while ((c=fgetc(scroll)) != EOF)
	{	c = (char) (strchr(instruct,c) - instruct);
		prg[PC++]=c;
	}
	prg[PC]=0;
	return 0;
}



#define NOP -1

int brain(char mem[], char prg[])
{
	/*
   -1		NOP		do nothing
	0		HLT		end of input
	1	>	DPF		Data Point  Forward
	2	<	DPB		Data Point Backward
	3	+	INC 	INCrement    value
	4	-	DCR		DeCRement    value
	5	.	GIV		GIVe  output value
	6	,	ACP		ACcePt input value
	7	[	LOP		enter LOoP
	8	]	EXT		EXit  loop
	
	*/
	
	enum instrct{HLT, DPF, DPB, INC, DCR, GIV, ACP, LOP, EXT};
	
	int DP=0, PC=0, SP=0;
	_Bool keep_going=1, save=0;
	char val=0, stack[stack_size];


	for (;keep_going;++PC)
	{	val=mem[DP];
		switch (prg[PC]) {
			case NOP: 			    save=0;break;
			case DPF: ++DP		   ;save=0;break;
			case DPB: --DP		   ;save=0;break;
			case INC: ++val		   ;save=1;break;
			case DCR: --val		   ;save=1;break;
			case GIV: putchar(val) ;save=0;break;
			case ACP: val=getchar();save=1;break;
			
			case LOP:
			{ 	if(!val)
				{	for (;prg[PC] != EXT;++PC)
						;
				++PC;
				}
				else
					stack[SP++]=PC;
			} save=0;break;

			case EXT:
			{	if(val)
					PC=stack[SP];
				else
					--SP;
			} save=0;break;

			default: keep_going=0;break; //intentional HLT has to be 0;
		}
		if(save)
			mem[DP]=val;	
	}
	putchar('\n');
	if (prg[PC])
	{	printf("!Unlawful halt!\n");
		return 1;
	}

	return 0;
}


