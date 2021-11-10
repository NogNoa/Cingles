#include <stdio.h>

int change(int *amnt, int deno)
{
	int bills;
	
	bills = *amnt / deno;
	*amnt -= deno * bills;
	return bills;
}

int main(){

	int amnt, bills;
	int * pa;
	
		
	printf("Enter an amount: $");
	scanf("%d", &amnt);
	pa = &amnt;
	bills = change( pa, 20);
	printf("$20 bills: %d\n", bills);
	bills = change( pa, 10);
	printf("$10 bills: %d\n", bills);
	bills = change( pa, 5);
	printf("$5 bills: %d\n", bills);
	bills = change( pa, 1);
	printf("$1 bills: %d\n", bills);
	return 0;
}

