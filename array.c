#include <stdio.h>

int main(int argc, char const *argv[])
{
	_Bool l[8];

	for (int i=0;i<8;++i)
		l[i]=1;

	_Bool * pl = &l[0];

	for(int i=-8;i<8;++i)
		printf("%d\n",*(pl+i));
	return 0;
}
