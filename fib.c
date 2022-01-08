#include <stdlib.h>
#include <stdio.h>

int fib(int a)
{	
	if (a < 0)
		return 0;
	else if (a < 2)
		return 1;
	else
		return fib(a-1)+fib(a-2);
}

int main(int argc, char** argv)
{
	int call, back;
	if (argc>1)
		call=atoi(argv[1]);
	else
		call=0;
	back = fib(call);
	printf("%d\n",back);
}
