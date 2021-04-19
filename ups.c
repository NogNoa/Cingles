#include <stdio.h>

int main()
{
	int tot;
	for (tot=9;tot<20;++tot){
		printf("%d\t%d\n", 9 - (tot -1) % 10, 10 - tot % 10);
	}
	return 0;
}