//c using pointers

#include <stdlib.h>

int fib(int av)
{	
	int *a=&av;
	if (*a < 0)
		return 0;
	else if (*a < 2)
		return 1;
	else
		return fib(*a-1)+fib(*a-2);
}

int main(int argc, char** argv)
{
	if (argc>1)
		fib(atoi(argv[1]));
}