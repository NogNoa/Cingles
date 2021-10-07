#include <stdio.h>

int main(){

	int x, y;
		
	printf("Enter a value: ");
	scanf("%d", &x);
	y = ((((3 * x + 2) * x + 5) * x - 1) * x + 7) * x - 6;
	printf("%d\n", y);
	return y;
}

