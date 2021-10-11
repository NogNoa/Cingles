#include "tabbin.h"

/* tab-stops of 4-spaces each. */

int entab(int strt, int gap, int *stops, int len)
{
	int i=0, spc=0;
	char c;
	
	while ((c = getchar()) != EOF){
		if (c == ' '){
			++spc;
			int nxtstp = fndstp(strt, gap, stops , 0, i);
			int rmn = (nxtstp - i);
			if (spc > rmn)
			{	putchar('\t');
				i   += rmn;
				spc -= rmn;
			}
		}
		else
		{	i += spc;
			if (i >= MXLIN)
			{	putchar('\n');
				i=spc=0;
			}
			else for (;spc>0;--spc)
				putchar(' ');
			putchar(c);
			++i;
		}
		if (c == '\n')
			i = 0;
	}
	return i;
}

#include <ctype.h>

int detab(int start, int gap, int *stops, int len)
{
	int i=0;
	char c;
	
	while ((c = getchar()) != EOF)
	{	if (isspace(c) && i >= MXLIN)
			{	putchar('\n');
				i=0;
			}
		else if (c == '\t')
		{	int nxtstp = fndstp(start, gap, stops, len, i); //nxtstp
			for(;i < nxtstp;i++) 
				putchar(' ');
			if (i>=MXLIN)
			{	putchar('\n');
				i = 0;
			}
		}
		else if (c == '\n')
		{	putchar(c);
			i = 0;
		}
		else
		{	putchar(c);
			++i;
		}
	}
	return i;
}

#include <string.h>

int main(int argc, char *argv[])
{
	int back;
	struct tabbin taby;
	
	sint (*funtab)(int,int,int*,int) = *entab;

	if(strstr(argv[0],"entab.elf"))
		funtab=*entab;
	else if(strstr(argv[0],"detab.elf"))
		funtab=*detab;

	stdin = fopen("entab.c","r");

	if (argc < 2)
	{	/* tab-stops of 4-spaces each. */
		int stops[2] = {0,MXLIN};
		back = funtab(0, 4, stops, 2);
	}
	else
	{	taby = arg_prcs(argc, argv);
		back = funtab(taby.m, taby.n, taby.stops, argc+1);
	}
	return back;
}
